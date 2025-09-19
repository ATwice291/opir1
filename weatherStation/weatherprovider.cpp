#include "weatherprovider.h"
#include "openweatherapi.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimeZone>
#include <QDebug>
#include <QValueAxis>

#include <QtCharts/QLineSeries>
using namespace QtCharts;

WeatherProvider::WeatherProvider(QObject *parent)
    : QObject{parent}
{
    _chart = nullptr;
    connect(&_timer, &QTimer::timeout, this, &WeatherProvider::timerTick);
    _timer.setInterval(1000*300);
    _timer.start();

    connect(&_netManager, &QNetworkAccessManager::finished, this, &WeatherProvider::onReply);
    _forecast.clear();
    for(int i = 0; i < 4; i++) {
        _forecast.append({qint16(i+1), 20, "02d"});
    }
    emit forecastChanged();
    timerTick();
}

void WeatherProvider::setChart(QObject *chart) {
    _chart = chart;
}

void WeatherProvider::timerTick() {
    checkTheWeather();
    checkTheForecast();
}

void WeatherProvider::checkTheWeather() {
    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric")
    .arg(city, api_key);
    QNetworkRequest request((QUrl(url)));
    _netManager.get(request);
}

void WeatherProvider::checkTheForecast() {
    QString url = QString("http://api.openweathermap.org/data/2.5/forecast?q=%1&appid=%2&units=metric")
    .arg(city, api_key);
    QNetworkRequest request((QUrl(url)));
    _netManager.get(request);
}

void WeatherProvider::parseWeather(QJsonObject obj) {
    QJsonObject main = obj["main"].toObject();
    _currentTemp = qRound(main["temp"].toDouble());
    emit currentTempChanged();
    _currentPress = main["pressure"].toInt();
    emit currentPressChanged();
    _currentHumid = main["humidity"].toInt();
    emit currentHumidChanged();

    QJsonArray weatherArray = obj["weather"].toArray();
    if (!weatherArray.isEmpty()) {
        _currentWeatherDescription = weatherArray[0].toObject()["description"].toString();
        emit currentWeatherDescriptionChanged();
        _currentWeatherIcon = weatherArray[0].toObject()["icon"].toString();
        emit currentWeatherIconChanged();
    }

    qDebug() << "Temperature:" << _currentTemp << "°C";
    qDebug() << "Pressure:" << _currentPress << "hPa";
    qDebug() << "Humidity:" << _currentHumid << "%";
    qDebug() << "Weather:" << _currentWeatherDescription;
}

void WeatherProvider::parseForecast(QJsonObject obj) {
    QJsonArray forecastArray = obj["list"].toArray();
    int count = qMin(4, forecastArray.size());
    QVariantList points;
    for(int i = 0; i < count; i++) {
        QJsonObject item = forecastArray[i].toObject();
        QString data = item["dt_txt"].toString();
        //_forecast[i].hour = data.midRef(11,2).toInt();
        qint64 dt = item["dt"].toInt();
        QDateTime utc = QDateTime::fromSecsSinceEpoch(dt, Qt::UTC);

        QTimeZone tz(60*60*4); // например, GMT+4
        QDateTime custom = utc.toTimeZone(tz);

        _forecast[i].hour = custom.time().hour();
        _forecast[i].temp = qRound(item["main"].toObject()["temp"].toDouble());
        _forecast[i].icon = item["weather"].toArray()[0].toObject()["icon"].toString();
        qDebug() << _forecast[i].hour << "h - " << _forecast[i].temp << "°C";

        QVariantMap m;
        m["x"] = 2*i+1;
        m["y"] = _forecast[i].temp;
        points << m;
    }
    emit forecastChanged();
    if(!_chart) {
        return;
    }
    QVariant arg = QVariant::fromValue(points);
    bool ok = QMetaObject::invokeMethod(_chart, "updatePoints", Qt::DirectConnection,
                                        Q_ARG(QVariant, arg));
}

void WeatherProvider::onReply(QNetworkReply* reply) {
    if (reply->error()) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(response);
    if (!doc.isObject()) {
        return;
    }

    QJsonObject obj = doc.object();
    if(obj.contains("main")) {
        parseWeather(obj);
    }
    if(obj.contains("list")) {
        parseForecast(obj);
    }
}
