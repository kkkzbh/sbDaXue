#include "core/gfx_dispatch.h"

#include <QtCore/QProcess>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <algorithm>
#include <cstdint>
#include <expected>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace {

using namespace std::string_view_literals;
static constexpr auto default_cli_timeout_ms = 1200;

auto cli_timeout_ms() -> int {
  auto ok = false;
  auto const configured = qEnvironmentVariableIntValue("KONTROL_CLI_TIMEOUT_MS", &ok);
  if (ok && configured > 0) {
    return configured;
  }

  return default_cli_timeout_ms;
}

auto run_command(QStringList const& args) -> std::expected<QString, kontrol::GfxError> {
  auto process = QProcess {};
  process.start(QStringLiteral("supergfxctl"), args);

  if (!process.waitForFinished(cli_timeout_ms())) {
    return std::unexpected(kontrol::GfxError {
      .code = kontrol::GfxError::Code::Timeout,
      .message = "supergfxctl command timed out",
      .remediation = "Retry after confirming supergfxd is responsive",
    });
  }

  if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
    auto const stderr_text = process.readAllStandardError().trimmed().toStdString();
    auto const code = stderr_text.find("Permission") != std::string::npos
      ? kontrol::GfxError::Code::PermissionDenied
      : kontrol::GfxError::Code::BackendRejected;

    return std::unexpected(kontrol::GfxError {
      .code = code,
      .message = stderr_text.empty() ? "supergfxctl failed" : stderr_text,
      .remediation = "Check command permissions and supergfxd service state",
    });
  }

  return process.readAllStandardOutput();
}

auto run_asus_info() -> QString {
  auto process = QProcess {};
  process.start(QStringLiteral("asusctl"), {QStringLiteral("info")});
  if (!process.waitForFinished(1500)) {
    return {};
  }

  if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
    return {};
  }

  return process.readAllStandardOutput();
}

auto parse_mode(std::string_view raw) -> std::optional<std::uint32_t> {
  auto const trimmed = kontrol::trim_copy(raw);
  return kontrol::mode_from_cli_name(trimmed);
}

auto parse_pending_action(std::string_view raw) -> std::uint32_t {
  auto const normalized = kontrol::lowercase_copy(kontrol::trim_copy(raw));
  if (normalized.empty() || normalized == "unknown") {
    return kontrol::pending_action::unknown;
  }

  if (normalized.find("no action") != std::string::npos) {
    return kontrol::pending_action::nothing;
  }

  if (normalized.find("switchtointegrated") != std::string::npos
      || (normalized.find("switch") != std::string::npos && normalized.find("integrated") != std::string::npos)) {
    return kontrol::pending_action::switch_to_integrated;
  }

  if (normalized.find("asusegpudisable") != std::string::npos
      || (normalized.find("egpu") != std::string::npos
          && (normalized.find("disable") != std::string::npos || normalized.find("disabled") != std::string::npos))) {
    return kontrol::pending_action::asus_egpu_disable;
  }

  if (normalized.find("logout") != std::string::npos) {
    return kontrol::pending_action::logout;
  }

  if (normalized.find("reboot") != std::string::npos || normalized.find("restart") != std::string::npos) {
    return kontrol::pending_action::reboot;
  }

  return kontrol::pending_action::unknown;
}

auto parse_power_status(std::string_view raw) -> std::uint32_t {
  auto const normalized = kontrol::lowercase_copy(kontrol::trim_copy(raw));
  if (normalized.empty() || normalized == "unknown") {
    return kontrol::power_status::unknown;
  }

  if (normalized.find("active") != std::string::npos) {
    return kontrol::power_status::active;
  }

  if (normalized.find("dgpu_disabled") != std::string::npos || normalized.find("disabled") != std::string::npos) {
    return kontrol::power_status::asus_disabled;
  }

  if (normalized.find("asus_mux") != std::string::npos || normalized.find("mux") != std::string::npos) {
    return kontrol::power_status::asus_mux_dgpu;
  }

  if (normalized.find("off") != std::string::npos) {
    return kontrol::power_status::off;
  }

  if (normalized.find("suspend") != std::string::npos) {
    return kontrol::power_status::suspended;
  }

  return kontrol::power_status::unknown;
}

auto parse_supported_modes(std::string_view raw) -> std::vector<std::uint32_t> {
  auto sanitized = kontrol::trim_copy(raw);
  sanitized.erase(std::remove(sanitized.begin(), sanitized.end(), '['), sanitized.end());
  sanitized.erase(std::remove(sanitized.begin(), sanitized.end(), ']'), sanitized.end());

  auto const as_qstring = QString::fromStdString(sanitized);
  auto const entries = as_qstring.split(QLatin1Char(','), Qt::SkipEmptyParts);

  auto mapped = entries
    | std::views::transform([](auto const& entry) {
        return parse_mode(entry.trimmed().toStdString());
      })
    | std::views::filter([](auto const& value) { return value.has_value(); })
    | std::views::transform([](auto const& value) { return *value; })
    | std::ranges::to<std::vector>();

  if (!mapped.empty()) {
    return mapped;
  }

  auto const fallback_single = parse_mode(sanitized);
  if (fallback_single) {
    return std::vector {*fallback_single};
  }

  return {};
}

auto parse_asus_info(kontrol::SystemSnapshot& snapshot) -> void {
  auto const output = run_asus_info();
  if (output.isEmpty()) {
    return;
  }

  auto const lines = output.split(QLatin1Char('\n'), Qt::SkipEmptyParts);
  for (auto const& raw_line : lines) {
    auto const line = raw_line.trimmed();

    if (line.startsWith(QStringLiteral("Product family:"))) {
      snapshot.product_family = line.section(QLatin1Char(':'), 1).trimmed().toStdString();
    }

    if (line.startsWith(QStringLiteral("Board name:"))) {
      snapshot.board_name = line.section(QLatin1Char(':'), 1).trimmed().toStdString();
    }
  }
}

} // namespace

namespace kontrol {

auto CliBackend::snapshot() -> SnapshotResult {
  auto const supported = run_command({QStringLiteral("--supported")});
  if (!supported) {
    return std::unexpected(supported.error());
  }

  auto const current = run_command({QStringLiteral("--get")});
  if (!current) {
    return std::unexpected(current.error());
  }

  auto const status = run_command({QStringLiteral("--status")});
  if (!status) {
    return std::unexpected(status.error());
  }

  auto const pending_action = run_command({QStringLiteral("--pend-action")});
  if (!pending_action) {
    return std::unexpected(pending_action.error());
  }

  auto const pending_mode = run_command({QStringLiteral("--pend-mode")});
  if (!pending_mode) {
    return std::unexpected(pending_mode.error());
  }

  auto const vendor = run_command({QStringLiteral("--vendor")});

  auto const supported_modes = parse_supported_modes(supported->toStdString());

  auto const parsed_current = parse_mode(current->toStdString());
  if (!parsed_current) {
    return std::unexpected(GfxError {
      .code = GfxError::Code::ParseFailed,
      .message = "Unable to parse current mode",
      .remediation = "Check supergfxctl --get output",
    });
  }

  auto snapshot = SystemSnapshot {};
  snapshot.current_mode = *parsed_current;
  snapshot.power_status = parse_power_status(status->toStdString());
  snapshot.pending_action = parse_pending_action(pending_action->toStdString());

  auto const parsed_pending = parse_mode(pending_mode->toStdString());
  snapshot.pending_mode = parsed_pending.value_or(mode::unknown);

  snapshot.supported_modes = supported_modes
    | std::views::transform([](auto const raw_mode) {
        return mode_to_option(raw_mode, true);
      })
    | std::ranges::to<std::vector>();
  ensure_preferred_modes(snapshot.supported_modes);

  snapshot.dgpu_vendor = vendor ? trim_copy(vendor->toStdString()) : std::string {"Unknown"};
  snapshot.product_family = "Unknown";
  snapshot.board_name = "Unknown";
  parse_asus_info(snapshot);

  if (snapshot.product_family.empty()) {
    snapshot.product_family = "Unknown";
  }

  if (snapshot.board_name.empty()) {
    snapshot.board_name = "Unknown";
  }

  return snapshot;
}

auto CliBackend::switch_mode(std::uint32_t raw_mode) -> SnapshotResult {
  auto const mode_name = mode_cli_name(raw_mode);
  if (mode_name.rfind("unknown_", 0) == 0) {
    return std::unexpected(GfxError {
      .code = GfxError::Code::UnsupportedMode,
      .message = "Cannot switch unknown mode via CLI",
      .remediation = "Select a supported mode from the list",
    });
  }

  auto const set_mode = run_command({QStringLiteral("--mode"), QString::fromStdString(mode_name)});
  if (!set_mode) {
    return std::unexpected(set_mode.error());
  }

  return snapshot();
}

} // namespace kontrol
