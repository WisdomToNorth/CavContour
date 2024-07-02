#include <QFont>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>

#include "viewer/Viewer2d.h"

#include "settings/settings.h"

using namespace debugger;

int main(int argc, char *argv[])
{
    qmlRegisterType<SettingItem>("PolyDebugger", 1, 0, "SettingItem");
    qmlRegisterType<SceneViewer>("PolyDebugger", 1, 0, "SceneViewer");

    QGuiApplication app(argc, argv);
    QFont defaultFont("Arial", 12);
    app.setFont(defaultFont);

    QSurfaceFormat format;
    format.setSamples(4);
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

    Settings::instance().load();
    int run_result = app.exec();
    if (run_result == 0)
    {
        Settings::instance().save();
    }
    return run_result;
}
