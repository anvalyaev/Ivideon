#include <QApplication>
#include <QQmlApplicationEngine>
#include "dispatcher.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Dispatcher dispatcher(engine.rootObjects().first());
    engine.rootContext()->setContextProperty("Dispatcher", &dispatcher);

    return app.exec();
}
