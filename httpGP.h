#ifndef HTTPPOST_H
#define HTTPPOST_H
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include<QString>
#include <QObject>

class HTTPGP : public QObject
{
    Q_OBJECT
public:
    QNetworkAccessManager * naManager;
    explicit HTTPGP(QObject *parent = 0);


signals:
    void RequestFinished(QString string);
public slots:
    void httpget(QString ht);
    void httppost(QString ht,QString testData);
    void requestFinished(QNetworkReply* reply);
};

#endif // HTTPPOST_H
