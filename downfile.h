#ifndef DOWNFILE_H
#define DOWNFILE_H

#include <QObject>
#include <QFile>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkProxy>
class downFile : public QObject
{
    Q_OBJECT
public:
    explicit downFile(QObject *parent = nullptr);
    void down(QString url, QString id, int type);
    QNetworkAccessManager m_networkManager;
    QString url,id;
    int type;
signals:
    success(QString,int);
    fail();
private slots:
    void replyFinished(QNetworkReply *reply);
public slots:
};

#endif // DOWNFILE_H





