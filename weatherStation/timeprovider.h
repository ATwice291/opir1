#ifndef TIMEPROVIDER_H
#define TIMEPROVIDER_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class TimeProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timeString READ timeString NOTIFY timeStringChanged FINAL)
public:
    explicit TimeProvider(QObject *parent = nullptr);

    QString timeString() const {return _timeString;}

signals:
    void timeStringChanged();

public slots:
    void checkTheTime();

private:
    QString _timeString = "01.01 23:59";
    QTimer _timer;
    QNetworkAccessManager _netManager;

    static constexpr int TIME_REFRESH_PERIOD = 60*60*24;
    int _counter;

    void requestIP();
    void requestTimeZone(QString ip);

private slots:
    void parseIP(QNetworkReply* reply);
    void parseTimeZone(QNetworkReply* reply);
};

#endif // TIMEPROVIDER_H
