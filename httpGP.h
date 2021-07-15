#ifndef HTTPPOST_H
#define HTTPPOST_H
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QObject>

class HTTPGP : public QObject
{
    Q_OBJECT
public:
    QNetworkAccessManager * naManager;
    explicit HTTPGP(QObject *parent = 0);
    QString httpget(QString ht);
    QString httppost(QString ht,QString testData);
signals:

public slots:
    void requestFinished(QNetworkReply* reply);
};

#endif // HTTPPOST_H
