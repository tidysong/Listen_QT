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
    QString headUrl = "http://localhost:8181";

    QList<searchInfo*> searchList;
    QList<searchInfo*> cloudList;
    void addCloud(QString);
    void deleteCloud(QString id);
    void sigup(QString u,QString p);
signals:
    void LoginSuccess();
    void searchSuccess(QList<searchInfo*>);
    void cloudSuccess(QList<searchInfo*>);
    void LoginFail();
    void addCloudSuccess();
    void deleteCloudSuccess();
    void sigupSuccess(QString id);
private slots:
    void loginReturn(QString);
    void searchReturn(QString);
    void cloudReturn(QString res);
    void addCloudReturn(QString);
    void deleteCloudReturn(QString);
    void sigupReturn(QString res);
public slots:
};

#endif // SERVICE_H
