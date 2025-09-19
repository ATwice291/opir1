#include "timeprovider.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QProcess>
#include <QDateTime>
#include <QTimeZone>

TimeProvider::TimeProvider(QObject *parent)
    : QObject{parent}
{
    connect(&_timer, &QTimer::timeout, this, &TimeProvider::checkTheTime);
    _timer.setInterval(1000);
    _timer.start();
    _counter = 0;
    checkTheTime();
}

void TimeProvider::checkTheTime() {
    QString dateTime = QDateTime::currentDateTime().toString("dd.MM hh:mm");
    if( dateTime.compare(_timeString) != 0) {
        _timeString = dateTime;
        emit timeStringChanged();
    }
    if(_counter <= 0) {
        _counter = TIME_REFRESH_PERIOD;
        requestIP();
    }
    --_counter;
}

void TimeProvider::requestIP() {
    connect(&_netManager, &QNetworkAccessManager::finished,
            this, &TimeProvider::parseIP);
    QString url = QString("http://api.ipify.org?format=json");
    QNetworkRequest request((QUrl(url)));
    qDebug() << "request ip...";
    _netManager.get(request);
}

void TimeProvider::requestTimeZone(QString ip) {
    connect(&_netManager, &QNetworkAccessManager::finished,
            this, &TimeProvider::parseTimeZone);
    QString url = QString("http://ip-api.com/json/%1").arg(ip);
    QNetworkRequest request((QUrl(url)));
    qDebug() << QString("request timezone - %1 ...").arg(url);
    _netManager.get(request);
}

void TimeProvider::parseIP(QNetworkReply* reply) {
    disconnect(&_netManager, &QNetworkAccessManager::finished,
               this, &TimeProvider::parseIP);
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
    QString ip = obj["ip"].toString();
    qDebug() << "ip:" << ip;
    requestTimeZone(ip);
}

void TimeProvider::parseTimeZone(QNetworkReply* reply) {
    disconnect(&_netManager, &QNetworkAccessManager::finished,
               this, &TimeProvider::parseTimeZone);
    if (reply->error()) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();

    QString dateStr = reply->rawHeader("date");  // старый способ (Qt5 и Qt6 тоже работает)
    qDebug() << "Date header string:" << dateStr;

    QDateTime dt = QDateTime::fromString(dateStr, "ddd, dd MMM yyyy HH:mm:ss 'GMT'");
    dt.setTimeSpec(Qt::UTC);  // "Tue, 16 Sep 2025 17:43:01 GMT" → UTC время
    qDebug() << "Parsed datetime:" << dt.toString();
    QString cmd = "date -s \"" + dt.toString("yyyy-MM-dd hh:mm:ss") + "\"";
    QProcess::execute(cmd);

    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(response);
    if (!doc.isObject()) {
        return;
    }
    QJsonObject obj = doc.object();
    QString timezone = obj["timezone"].toString();
    qDebug() << "timezone: " << timezone;
    QProcess::execute(QString("ln -sf /usr/share/zoneinfo/%1 /etc/localtime").arg(timezone));
}
