#ifndef WEATHERPROVIDER_H
#define WEATHERPROVIDER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "forecastpoint.h"

class WeatherProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 currentTemp READ currentTemp NOTIFY currentTempChanged FINAL)
    Q_PROPERTY(qint16 currentPress READ currentPress NOTIFY currentPressChanged FINAL)
    Q_PROPERTY(qint16 currentHumid READ currentHumid NOTIFY currentHumidChanged FINAL)
    Q_PROPERTY(QString currentWeatherDescription READ currentWeatherDescription NOTIFY currentWeatherDescriptionChanged FINAL)
    Q_PROPERTY(QString currentWeatherIcon READ currentWeatherIcon NOTIFY currentWeatherIconChanged FINAL)
    Q_PROPERTY(QVector<ForecastPoint> forecast READ forecast NOTIFY forecastChanged FINAL)
public:
    explicit WeatherProvider(QObject *parent = nullptr);

    qint16 currentTemp() const {return _currentTemp;}
    qint16 currentPress() const {return _currentPress;}
    qint16 currentHumid() const {return _currentHumid;}
    QString currentWeatherDescription() const {return _currentWeatherDescription;}
    QString currentWeatherIcon() const {return _currentWeatherIcon;}
    QVector<ForecastPoint> forecast() const {return _forecast;}

    Q_INVOKABLE void setChart(QObject* chart);

signals:
    void currentTempChanged();
    void currentPressChanged();
    void currentHumidChanged();
    void currentWeatherDescriptionChanged();
    void currentWeatherIconChanged();
    void forecastChanged();

public slots:
    void timerTick();

private slots:
    void onReply(QNetworkReply* reply);

private:
    qint16 _currentTemp = 20;
    qint16 _currentPress = 900;
    qint16 _currentHumid = 65;
    QString _currentWeatherDescription = "few clouds";
    QString _currentWeatherIcon = "02d";
    QVector<ForecastPoint> _forecast;
    QObject* _chart;

    QTimer _timer;
    QNetworkAccessManager _netManager;

    void checkTheWeather();
    void checkTheForecast();
    void parseWeather(QJsonObject obj);
    void parseForecast(QJsonObject obj);
};

#endif // WEATHERPROVIDER_H
