#include "core/gfx_dispatch.h"

#include <cstdint>
#include <expected>

namespace {

struct FakePrimary {
  auto snapshot() -> kontrol::SnapshotResult {
    return std::unexpected(kontrol::GfxError {
      .code = kontrol::GfxError::Code::DbusUnavailable,
      .message = "dbus down",
      .remediation = "fallback",
    });
  }

  auto switch_mode(std::uint32_t) -> kontrol::SnapshotResult {
    return snapshot();
  }
};

struct FakeFallback {
  auto snapshot() -> kontrol::SnapshotResult {
    auto snapshot = kontrol::SystemSnapshot {};
    snapshot.current_mode = kontrol::mode::asus_mux_dgpu;
    snapshot.supported_modes.push_back(kontrol::mode_to_option(kontrol::mode::asus_mux_dgpu, true));
    return snapshot;
  }

  auto switch_mode(std::uint32_t mode) -> kontrol::SnapshotResult {
    auto snapshot = kontrol::SystemSnapshot {};
    snapshot.current_mode = mode;
    snapshot.supported_modes.push_back(kontrol::mode_to_option(mode, true));
    return snapshot;
  }
};

} // namespace

auto main() -> int {
  auto primary = FakePrimary {};
  auto fallback = FakeFallback {};

  auto const snap = kontrol::run_with_fallback(primary, fallback, [](auto& backend) -> kontrol::SnapshotResult {
    return backend.snapshot();
  });

  if (!snap || snap->current_mode != kontrol::mode::asus_mux_dgpu) {
    return 1;
  }

  auto const switched = kontrol::run_with_fallback(primary, fallback, [](auto& backend) -> kontrol::SnapshotResult {
    return backend.switch_mode(kontrol::mode::integrated);
  });

  if (!switched || switched->current_mode != kontrol::mode::integrated) {
    return 1;
  }

  return 0;
}
