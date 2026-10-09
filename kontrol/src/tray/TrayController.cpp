#include "tray/TrayController.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QAction>
#include <QtGui/QIcon>

namespace kontrol {

TrayController::TrayController(AppController& app_controller, QWindow* main_window, QObject* parent)
  : QObject(parent)
  , controller(app_controller)
  , window(main_window)
  , tray_menu(new QMenu()) {
  tray_icon.setIcon(QIcon::fromTheme(QStringLiteral("preferences-system")));
  tray_icon.setToolTip(QStringLiteral("Kontrol"));

  refresh_modes_menu();

  auto* refresh_action = tray_menu->addAction(QStringLiteral("Refresh"));
  QObject::connect(refresh_action, &QAction::triggered, &controller, &AppController::refresh);

  auto* open_action = tray_menu->addAction(QStringLiteral("Open"));
  QObject::connect(open_action, &QAction::triggered, this, [this]() -> void {
    if (window != nullptr) {
      window->show();
      window->raise();
      window->requestActivate();
    }
  });

  auto* quit_action = tray_menu->addAction(QStringLiteral("Quit"));
  QObject::connect(quit_action, &QAction::triggered, []() -> void {
    QCoreApplication::quit();
  });

  tray_icon.setContextMenu(tray_menu);
  tray_icon.show();

  QObject::connect(&controller, &AppController::modesChanged, this, [this]() -> void {
    refresh_modes_menu();
  });

  QObject::connect(&controller, &AppController::snapshotChanged, this, [this]() -> void {
    auto const tip = QStringLiteral("Kontrol | %1").arg(controller.current_mode_label());
    tray_icon.setToolTip(tip);
  });

  QObject::connect(&tray_icon, &QSystemTrayIcon::activated, this, [this](auto reason) -> void {
    if (reason == QSystemTrayIcon::Trigger && window != nullptr) {
      window->show();
      window->raise();
      window->requestActivate();
    }
  });
}

auto TrayController::refresh_modes_menu() -> void {
  auto const previous_actions = tray_menu->actions();
  for (auto* action : previous_actions) {
    if (action->property("modeEntry").toBool()) {
      tray_menu->removeAction(action);
      delete action;
    }
  }

  auto const mode_entries = controller.modes();
  auto* insertion_before = tray_menu->actions().isEmpty() ? nullptr : tray_menu->actions().front();

  for (auto const& entry : mode_entries) {
    auto const map = entry.toMap();
    auto const label = map.value(QStringLiteral("label")).toString();
    auto const raw_mode = map.value(QStringLiteral("rawMode")).toUInt();

    auto* action = new QAction(label, tray_menu);
    action->setProperty("modeEntry", true);
    QObject::connect(action, &QAction::triggered, this, [this, raw_mode]() -> void {
      controller.applyMode(raw_mode);
    });

    tray_menu->insertAction(insertion_before, action);
  }

  if (!mode_entries.isEmpty()) {
    auto* separator = new QAction(tray_menu);
    separator->setSeparator(true);
    separator->setProperty("modeEntry", true);
    tray_menu->insertAction(insertion_before, separator);
  }
}

} // namespace kontrol
