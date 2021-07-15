#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QJsonParseError>
#include <qDebug>
#include <QJsonObject>
#include <QRegularExpression>
#include <QJsonArray>
#include <httpGP.h>
class service : public QObject
{
    Q_OBJECT
public:
    explicit service(QObject *parent = nullptr);
    static bool login(QString u,QString p);
signals:

public slots:
};

#endif // SERVICE_H
