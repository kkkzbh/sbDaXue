#include "core/gfx_dispatch.h"

#include <QtCore/QProcess>

namespace {

auto supergfxctl_available() -> bool {
  auto process = QProcess {};
  process.start(QStringLiteral("supergfxctl"), {QStringLiteral("--version")});
  if (!process.waitForFinished(1200)) {
    return false;
  }

  return process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0;
}

} // namespace

namespace kontrol {

auto make_backend() -> BackendVariant {
  if (!supergfxctl_available()) {
    return BackendVariant {CliBackend {}};
  }

  auto dbus_backend = DbusBackend {};
  if (dbus_backend.snapshot()) {
    return BackendVariant {dbus_backend};
  }

  return BackendVariant {CliBackend {}};
}

} // namespace kontrol
