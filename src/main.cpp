#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "../include/twitterakbackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<TwitterakBackend>("Backend",1,0,"Backend");

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/twitterak/qml/Main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
