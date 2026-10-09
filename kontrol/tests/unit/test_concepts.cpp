#include "core/gfx_dispatch.h"

#include <concepts>

auto main() -> int {
  static_assert(kontrol::GfxBackend<kontrol::DbusBackend>);
  static_assert(kontrol::GfxBackend<kontrol::CliBackend>);
  return 0;
}
