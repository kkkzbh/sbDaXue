#pragma once

#include "core/gfx_concepts.h"

#include <expected>
#include <variant>

namespace kontrol {

struct DbusBackend {
  auto snapshot() -> SnapshotResult;
  auto switch_mode(std::uint32_t raw_mode) -> SnapshotResult;
};

struct CliBackend {
  auto snapshot() -> SnapshotResult;
  auto switch_mode(std::uint32_t raw_mode) -> SnapshotResult;
};

using BackendVariant = std::variant<DbusBackend, CliBackend>;

auto make_backend() -> BackendVariant;

template <typename Primary, typename Fallback, typename Fn>
requires GfxBackend<Primary> && GfxBackend<Fallback>
auto run_with_fallback(Primary& primary, Fallback& fallback, Fn fn) -> SnapshotResult {
  auto primary_result = fn(primary);
  if (primary_result) {
    return primary_result;
  }

  if (primary_result.error().code != GfxError::Code::DbusUnavailable) {
    return primary_result;
  }

  return fn(fallback);
}

auto snapshot(BackendVariant& backend) -> SnapshotResult;
auto switch_mode(BackendVariant& backend, std::uint32_t raw_mode) -> SnapshotResult;

} // namespace kontrol
