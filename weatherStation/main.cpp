#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>

#include "timeprovider.h"
#include "weatherprovider.h"
#include "forecastpoint.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    qRegisterMetaType<ForecastPoint>("ForecastPoint");
    qRegisterMetaType<QVector<ForecastPoint>>("QVector<ForecastPoint>");

    QFontDatabase::addApplicationFont(":/fonts/PFDinDisplayPro-Med.ttf");
    QQmlApplicationEngine engine;


    TimeProvider timeProvider;
    engine.rootContext()->setContextProperty("timeProvider", &timeProvider);
    WeatherProvider weatherProvider;
    engine.rootContext()->setContextProperty("weatherProvider", &weatherProvider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
