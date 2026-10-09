#include "core/gfx_types.h"

#include <cstdint>
#include <optional>

auto main() -> int {
  if (kontrol::mode::hybrid != 0U || kontrol::mode::integrated != 1U || kontrol::mode::nvidia_no_modeset != 2U
      || kontrol::mode::asus_mux_dgpu != 5U || kontrol::mode::unknown != 6U) {
    return 1;
  }

  auto const hybrid = kontrol::mode_from_cli_name("Hybrid");
  if (!hybrid || *hybrid != kontrol::mode::hybrid) {
    return 1;
  }

  auto const no_modeset = kontrol::mode_from_cli_name("NvidiaNoModeset");
  if (!no_modeset || *no_modeset != kontrol::mode::nvidia_no_modeset) {
    return 1;
  }

  auto const mux = kontrol::mode_from_cli_name("asus_mux_discreet");
  if (!mux || *mux != kontrol::mode::asus_mux_dgpu) {
    return 1;
  }

  auto const unknown = kontrol::mode_from_cli_name("x_mode");
  if (unknown.has_value()) {
    return 1;
  }

  auto const label = kontrol::mode_label(kontrol::mode::integrated);
  if (label != "集显模式") {
    return 1;
  }

  auto const no_modeset_label = kontrol::mode_label(kontrol::mode::nvidia_no_modeset);
  if (no_modeset_label != "混合模式") {
    return 1;
  }

  auto const pending_nothing = kontrol::pending_action_label(kontrol::pending_action::nothing);
  if (pending_nothing != QStringLiteral("无需额外操作")) {
    return 1;
  }

  auto const power_off = kontrol::power_status_label(kontrol::power_status::off);
  if (power_off != QStringLiteral("关闭")) {
    return 1;
  }

  if (kontrol::mode_cli_name(kontrol::mode::hybrid) != "Hybrid") {
    return 1;
  }

  return 0;
}
