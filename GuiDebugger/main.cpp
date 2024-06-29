#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSurfaceFormat>

#include "offsetisland/offsetview.h"
#include "settings/settings.h"

using namespace debugger;

int main(int argc, char *argv[])
{
    qmlRegisterType<NgSettings>("PolyDebugger", 1, 0, "NgSettings");
    qmlRegisterType<OffsetView>("PolyDebugger", 1, 0, "OffsetView");

    QGuiApplication app(argc, argv);
    QFont defaultFont(app.font().family(), 12);
    app.setFont(defaultFont);

    QSurfaceFormat format;
    format.setSamples(16);
    QSurfaceFormat::setDefaultFormat(format);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
