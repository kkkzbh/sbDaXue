#include "tray/TrayController.h"
#include "ui/AppController.h"

#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtGui/QWindow>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QtWidgets/QApplication>

auto main(int argc, char* argv[]) -> int {
  auto app = QApplication(argc, argv);
  app.setApplicationName(QStringLiteral("Kontrol"));
  app.setOrganizationName(QStringLiteral("kontrol"));

  QQuickStyle::setStyle(QStringLiteral("Fusion"));

  auto parser = QCommandLineParser {};
  parser.setApplicationDescription(QStringLiteral("Kontrol ASUS utility frontend"));
  parser.addHelpOption();

  auto minimized_option = QCommandLineOption {
    QStringList {QStringLiteral("m"), QStringLiteral("minimized")},
    QStringLiteral("Start minimized to tray"),
  };
  parser.addOption(minimized_option);
  parser.process(app);

  auto controller = kontrol::AppController {};

  auto engine = QQmlApplicationEngine {};
  engine.rootContext()->setContextProperty(QStringLiteral("appController"), &controller);

  QObject::connect(
    &engine,
    &QQmlApplicationEngine::objectCreated,
    &app,
    [&](QObject* object, QUrl const& object_url) -> void {
      if (object == nullptr && object_url == QUrl(QStringLiteral("qrc:/qml/Main.qml"))) {
        QCoreApplication::exit(-1);
      }
    },
    Qt::QueuedConnection);

  engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  auto* window = qobject_cast<QWindow*>(engine.rootObjects().constFirst());
  auto tray = kontrol::TrayController {controller, window, &app};

  if (window != nullptr && parser.isSet(minimized_option)) {
    window->hide();
  }

  return app.exec();
}
