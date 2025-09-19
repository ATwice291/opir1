#ifndef FORECASTPOINT_H
#define FORECASTPOINT_H

#include <QObject>
#include <QString>

class ForecastPoint
{
    Q_GADGET
    Q_PROPERTY(qint16 hour MEMBER hour)
    Q_PROPERTY(qint16 temp MEMBER temp)
    Q_PROPERTY(QString icon MEMBER icon)
public:
    qint16 hour;
    qint16 temp;
    QString icon ;
};

#endif // FORECASTPOINT_H
