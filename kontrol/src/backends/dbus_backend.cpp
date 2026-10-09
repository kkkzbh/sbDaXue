#include "core/gfx_dispatch.h"

#include <QtCore/QProcess>
#include <QtCore/QStringList>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusError>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusPendingCall>
#include <QtDBus/QDBusReply>

#include <algorithm>
#include <cstdint>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace {

using namespace std::string_view_literals;

static constexpr auto dbus_service = "org.supergfxctl.Daemon"sv;
static constexpr auto dbus_path = "/org/supergfxctl/Gfx"sv;
static constexpr auto dbus_interface = "org.supergfxctl.Daemon"sv;
static constexpr auto default_dbus_timeout_ms = 1200;

auto dbus_timeout_ms() -> int {
  auto ok = false;
  auto const configured = qEnvironmentVariableIntValue("KONTROL_DBUS_TIMEOUT_MS", &ok);
  if (ok && configured > 0) {
    return configured;
  }

  return default_dbus_timeout_ms;
}

auto with_dbus_detail(QString const& method, QDBusError const& error) -> kontrol::GfxError {
  auto message = "D-Bus call failed: " + method.toStdString();
  auto const detail = error.message().trimmed().toStdString();
  if (!detail.empty()) {
    message += " (" + detail + ")";
  }

  return kontrol::GfxError {
    .code = kontrol::GfxError::Code::BackendRejected,
    .message = std::move(message),
    .remediation = "Check permissions and supergfxd state",
  };
}

auto command_stdout(QStringList const& args) -> std::optional<QString> {
  auto process = QProcess {};
  process.start(QStringLiteral("asusctl"), args);
  if (!process.waitForFinished(1500)) {
    return std::nullopt;
  }

  if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
    return std::nullopt;
  }

  return process.readAllStandardOutput();
}

auto parse_asus_info(kontrol::SystemSnapshot& snapshot) -> void {
  auto const output = command_stdout({QStringLiteral("info")});
  if (!output) {
    return;
  }

  auto const lines = output->split(QLatin1Char('\n'), Qt::SkipEmptyParts);
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

auto dbus_error(std::string message) -> kontrol::SnapshotResult {
  return std::unexpected(kontrol::GfxError {
    .code = kontrol::GfxError::Code::DbusUnavailable,
    .message = std::move(message),
    .remediation = "Verify supergfxd service and D-Bus availability",
  });
}

auto make_interface() -> QDBusInterface {
  return QDBusInterface(
    QString::fromUtf8(dbus_service.data(), static_cast<qsizetype>(dbus_service.size())),
    QString::fromUtf8(dbus_path.data(), static_cast<qsizetype>(dbus_path.size())),
    QString::fromUtf8(dbus_interface.data(), static_cast<qsizetype>(dbus_interface.size())),
    QDBusConnection::systemBus());
}

auto reply_u(QDBusInterface& interface, QString const& method) -> std::expected<std::uint32_t, kontrol::GfxError> {
  auto const reply = QDBusReply<std::uint32_t> {interface.call(method)};
  if (!reply.isValid()) {
    return std::unexpected(with_dbus_detail(method, reply.error()));
  }

  return reply.value();
}

auto reply_string(QDBusInterface& interface, QString const& method) -> std::expected<std::string, kontrol::GfxError> {
  auto const reply = QDBusReply<QString> {interface.call(method)};
  if (!reply.isValid()) {
    return std::unexpected(with_dbus_detail(method, reply.error()));
  }

  return reply.value().trimmed().toStdString();
}

auto reply_supported_modes(QDBusInterface& interface) -> std::expected<std::vector<std::uint32_t>, kontrol::GfxError> {
  auto const reply = QDBusReply<QList<std::uint32_t>> {interface.call(QStringLiteral("Supported"))};
  if (!reply.isValid()) {
    return std::unexpected(with_dbus_detail(QStringLiteral("Supported"), reply.error()));
  }

  auto const list = reply.value();
  auto modes = std::vector<std::uint32_t> {};
  modes.reserve(static_cast<std::size_t>(list.size()));
  for (auto const mode_value : list) {
    modes.push_back(mode_value);
  }

  return modes;
}

auto build_snapshot(QDBusInterface& interface) -> kontrol::SnapshotResult {
  auto snapshot = kontrol::SystemSnapshot {};

  auto const mode = reply_u(interface, QStringLiteral("Mode"));
  if (!mode) {
    return std::unexpected(mode.error());
  }
  snapshot.current_mode = *mode;

  auto const pending_mode = reply_u(interface, QStringLiteral("PendingMode"));
  if (!pending_mode) {
    return std::unexpected(pending_mode.error());
  }
  snapshot.pending_mode = *pending_mode;

  auto const pending_action = reply_u(interface, QStringLiteral("PendingUserAction"));
  if (!pending_action) {
    return std::unexpected(pending_action.error());
  }
  snapshot.pending_action = *pending_action;

  auto const power = reply_u(interface, QStringLiteral("Power"));
  if (!power) {
    return std::unexpected(power.error());
  }
  snapshot.power_status = *power;

  auto const vendor = reply_string(interface, QStringLiteral("Vendor"));
  if (vendor) {
    snapshot.dgpu_vendor = *vendor;
  }

  auto const supported_modes = reply_supported_modes(interface);
  if (!supported_modes) {
    return std::unexpected(supported_modes.error());
  }

  snapshot.supported_modes = *supported_modes
    | std::views::transform([](auto const raw_mode) {
        return kontrol::mode_to_option(raw_mode, true);
      })
    | std::ranges::to<std::vector>();
  kontrol::ensure_preferred_modes(snapshot.supported_modes);

  parse_asus_info(snapshot);
  if (snapshot.product_family.empty()) {
    snapshot.product_family = "Unknown";
  }

  if (snapshot.board_name.empty()) {
    snapshot.board_name = "Unknown";
  }

  if (snapshot.dgpu_vendor.empty()) {
    snapshot.dgpu_vendor = "Unknown";
  }

  return snapshot;
}

} // namespace

namespace kontrol {

auto DbusBackend::snapshot() -> SnapshotResult {
  auto interface = make_interface();
  interface.setTimeout(dbus_timeout_ms());
  if (!interface.isValid()) {
    return dbus_error("Unable to connect to org.supergfxctl.Daemon");
  }

  return build_snapshot(interface);
}

auto DbusBackend::switch_mode(std::uint32_t raw_mode) -> SnapshotResult {
  auto interface = make_interface();
  interface.setTimeout(dbus_timeout_ms());
  if (!interface.isValid()) {
    return dbus_error("Unable to connect to org.supergfxctl.Daemon");
  }

  auto const reply = QDBusReply<std::uint32_t> {interface.call(QStringLiteral("SetMode"), raw_mode)};
  if (!reply.isValid()) {
    auto error = with_dbus_detail(QStringLiteral("SetMode"), reply.error());
    error.remediation = "Check permissions, whether mode is supported, and supergfxd state";
    return std::unexpected(std::move(error));
  }

  return build_snapshot(interface);
}

auto snapshot(BackendVariant& backend) -> SnapshotResult {
  return std::visit([](auto& selected) -> SnapshotResult { return selected.snapshot(); }, backend);
}

auto switch_mode(BackendVariant& backend, std::uint32_t raw_mode) -> SnapshotResult {
  return std::visit(
    [&](auto& selected) -> SnapshotResult {
      return selected.switch_mode(raw_mode);
    },
    backend);
}

} // namespace kontrol
