#pragma once

#include "core/gfx_types.h"

#include <concepts>
#include <cstdint>

namespace kontrol {

template <typename T>
concept GfxBackend = requires(T backend, std::uint32_t mode) {
  { backend.snapshot() } -> std::same_as<SnapshotResult>;
  { backend.switch_mode(mode) } -> std::same_as<SnapshotResult>;
};

} // namespace kontrol
