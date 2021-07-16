#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QJsonParseError>
#include <qDebug>
#include <QJsonObject>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonArray>
#include <httpGP.h>
#include <searchinfo.h>
#include <inifile.h>
class service : public QObject
{
    Q_OBJECT
public:
    explicit service(QObject *parent = nullptr);
    void login(QString u,QString p);
    void search(QString title);
    void cloud();
    QString headUrl = "http://localhost:8222/";

    QList<searchInfo*> searchList;
    QList<searchInfo*> cloudList;
signals:
    void LoginSuccess();
    void searchSuccess(QList<searchInfo*>);
    void cloudSuccess(QList<searchInfo*>);
    void LoginFail();
private slots:
    void loginReturn(QString);
    void searchReturn(QString);
    void cloudReturn(QString res);

public slots:
};

#endif // SERVICE_H
