#pragma once

#include "ui/AppController.h"

#include <QtCore/QObject>
#include <QtGui/QWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>

namespace kontrol {

struct TrayController : QObject {
  explicit TrayController(AppController& app_controller, QWindow* main_window = nullptr, QObject* parent = nullptr);

  auto refresh_modes_menu() -> void;

  AppController& controller;
  QWindow* window = nullptr;
  QSystemTrayIcon tray_icon {};
  QMenu* tray_menu = nullptr;

  Q_OBJECT
};

} // namespace kontrol
