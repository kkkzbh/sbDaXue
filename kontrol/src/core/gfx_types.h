#pragma once

#include <QtCore/QString>

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <expected>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace kontrol {

struct GfxError {
  enum struct Code : std::uint8_t {
    DbusUnavailable,
    CliUnavailable,
    PermissionDenied,
    UnsupportedMode,
    BackendRejected,
    Timeout,
    ParseFailed,
    Unknown,
  };

  Code code = Code::Unknown;
  std::string message {};
  std::string remediation {};
};

namespace mode {

inline constexpr auto hybrid = std::uint32_t {0U};
inline constexpr auto integrated = std::uint32_t {1U};
inline constexpr auto nvidia_no_modeset = std::uint32_t {2U};
inline constexpr auto vfio = std::uint32_t {3U};
inline constexpr auto asus_egpu = std::uint32_t {4U};
inline constexpr auto asus_mux_dgpu = std::uint32_t {5U};
inline constexpr auto unknown = std::uint32_t {6U};

} // namespace mode

namespace pending_action {

inline constexpr auto logout = std::uint32_t {0U};
inline constexpr auto reboot = std::uint32_t {1U};
inline constexpr auto switch_to_integrated = std::uint32_t {2U};
inline constexpr auto asus_egpu_disable = std::uint32_t {3U};
inline constexpr auto nothing = std::uint32_t {4U};
inline constexpr auto unknown = std::uint32_t {255U};

} // namespace pending_action

namespace power_status {

inline constexpr auto active = std::uint32_t {0U};
inline constexpr auto suspended = std::uint32_t {1U};
inline constexpr auto off = std::uint32_t {2U};
inline constexpr auto asus_disabled = std::uint32_t {3U};
inline constexpr auto asus_mux_dgpu = std::uint32_t {4U};
inline constexpr auto unknown = std::uint32_t {5U};

} // namespace power_status

struct ModeOption {
  std::uint32_t raw_mode = 0U;
  std::string id {};
  std::string label {};
  bool supported = false;
};

struct SystemSnapshot {
  std::string product_family {};
  std::string board_name {};
  std::string dgpu_vendor {};
  std::uint32_t current_mode = ::kontrol::mode::unknown;
  std::uint32_t pending_mode = ::kontrol::mode::unknown;
  std::uint32_t pending_action = ::kontrol::pending_action::unknown;
  std::uint32_t power_status = ::kontrol::power_status::unknown;
  std::vector<ModeOption> supported_modes {};
};

using SnapshotResult = std::expected<SystemSnapshot, GfxError>;

inline auto lowercase_copy(std::string_view input) -> std::string {
  auto output = std::string {input};
  std::ranges::transform(output, output.begin(), [](auto const ch) -> char {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
  });
  return output;
}

inline auto trim_copy(std::string_view input) -> std::string {
  auto const is_space = [](auto const ch) -> bool {
    return std::isspace(static_cast<unsigned char>(ch)) != 0;
  };

  auto const begin_it = std::ranges::find_if_not(input, is_space);
  if (begin_it == input.end()) {
    return {};
  }

  auto const reverse_view = input | std::views::reverse;
  auto const reverse_it = std::ranges::find_if_not(reverse_view, is_space);
  auto const end_it = reverse_it.base();
  return std::string {begin_it, end_it};
}

inline auto mode_from_cli_name(std::string_view name) -> std::optional<std::uint32_t> {
  auto const normalized = lowercase_copy(trim_copy(name));
  static constexpr auto table = std::array {
    std::pair {std::string_view {"hybrid"}, mode::hybrid},
    std::pair {std::string_view {"integrated"}, mode::integrated},
    std::pair {std::string_view {"nvidianomodeset"}, mode::nvidia_no_modeset},
    std::pair {std::string_view {"nvidia_no_modeset"}, mode::nvidia_no_modeset},
    std::pair {std::string_view {"nvidia_nomodeset"}, mode::nvidia_no_modeset},
    std::pair {std::string_view {"nvidia-no-modeset"}, mode::nvidia_no_modeset},
    std::pair {std::string_view {"vfio"}, mode::vfio},
    std::pair {std::string_view {"asusegpu"}, mode::asus_egpu},
    std::pair {std::string_view {"asus_egpu"}, mode::asus_egpu},
    std::pair {std::string_view {"egpu"}, mode::asus_egpu},
    std::pair {std::string_view {"asusmuxdgpu"}, mode::asus_mux_dgpu},
    std::pair {std::string_view {"asus_mux_dgpu"}, mode::asus_mux_dgpu},
    std::pair {std::string_view {"asusmuxdiscreet"}, mode::asus_mux_dgpu},
    std::pair {std::string_view {"asus_mux_discreet"}, mode::asus_mux_dgpu},
    std::pair {std::string_view {"unknown"}, mode::unknown},
    std::pair {std::string_view {"none"}, mode::unknown},
  };

  auto const it = std::ranges::find_if(table, [&](auto const& item) -> bool { return normalized == item.first; });
  if (it == table.end()) {
    return std::nullopt;
  }

  return it->second;
}

inline auto mode_id(std::uint32_t raw_mode) -> std::string {
  switch (raw_mode) {
  case mode::hybrid:
    return "hybrid";
  case mode::integrated:
    return "integrated";
  case mode::nvidia_no_modeset:
    return "nvidia_no_modeset";
  case mode::vfio:
    return "vfio";
  case mode::asus_egpu:
    return "asus_egpu";
  case mode::asus_mux_dgpu:
    return "asus_mux_dgpu";
  case mode::unknown:
    return "unknown";
  default:
    return "unknown_" + std::to_string(raw_mode);
  }
}

inline auto mode_cli_name(std::uint32_t raw_mode) -> std::string {
  switch (raw_mode) {
  case mode::hybrid:
    return "Hybrid";
  case mode::integrated:
    return "Integrated";
  case mode::nvidia_no_modeset:
    return "NvidiaNoModeset";
  case mode::vfio:
    return "Vfio";
  case mode::asus_egpu:
    return "AsusEgpu";
  case mode::asus_mux_dgpu:
    return "AsusMuxDgpu";
  case mode::unknown:
    return "Unknown";
  default:
    return "unknown_" + std::to_string(raw_mode);
  }
}

inline auto mode_label(std::uint32_t raw_mode) -> std::string {
  switch (raw_mode) {
  case mode::hybrid:
    return "混合模式";
  case mode::integrated:
    return "集显模式";
  case mode::nvidia_no_modeset:
    return "混合模式";
  case mode::vfio:
    return "VFIO";
  case mode::asus_egpu:
    return "ASUS eGPU";
  case mode::asus_mux_dgpu:
    return "独显直连";
  case mode::unknown:
    return "未知模式";
  default:
    return "Mode #" + std::to_string(raw_mode);
  }
}

inline auto mode_to_option(std::uint32_t raw_mode, bool supported) -> ModeOption {
  return ModeOption {
    .raw_mode = raw_mode,
    .id = mode_id(raw_mode),
    .label = mode_label(raw_mode),
    .supported = supported,
  };
}

inline auto preferred_mode_options() -> std::vector<ModeOption> {
  return std::vector {
    mode_to_option(mode::hybrid, true),
    mode_to_option(mode::integrated, true),
    mode_to_option(mode::asus_mux_dgpu, true),
  };
}

inline auto ensure_preferred_modes(std::vector<ModeOption>& modes) -> void {
  auto const has_id = [&](std::string_view id) -> bool {
    return std::ranges::any_of(modes, [&](auto const& mode) -> bool { return mode.id == id; });
  };

  auto const preferred = preferred_mode_options();
  for (auto const& entry : preferred) {
    if (!has_id(entry.id)) {
      modes.push_back(entry);
    }
  }
}

inline auto pending_action_label(std::uint32_t raw_action) -> QString {
  switch (raw_action) {
  case pending_action::logout:
    return QStringLiteral("需要注销");
  case pending_action::reboot:
    return QStringLiteral("需要重启");
  case pending_action::switch_to_integrated:
    return QStringLiteral("需先切换到集显");
  case pending_action::asus_egpu_disable:
    return QStringLiteral("需先禁用 ASUS eGPU");
  case pending_action::nothing:
    return QStringLiteral("无需额外操作");
  default:
    return QStringLiteral("状态待确认");
  }
}

inline auto power_status_label(std::uint32_t raw_status) -> QString {
  switch (raw_status) {
  case power_status::active:
    return QStringLiteral("活跃");
  case power_status::suspended:
    return QStringLiteral("挂起");
  case power_status::off:
    return QStringLiteral("关闭");
  case power_status::asus_disabled:
    return QStringLiteral("Asus 已禁用");
  case power_status::asus_mux_dgpu:
    return QStringLiteral("独显直连");
  case power_status::unknown:
    return QStringLiteral("未知");
  default:
    return QStringLiteral("未知");
  }
}

} // namespace kontrol
