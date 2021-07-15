#include "httpGP.h"

HTTPGP::HTTPGP(QObject *parent) :
    QObject(parent)
{

}
void HTTPGP::httpget(QString ht){//get
    QNetworkRequest request;
    naManager = new QNetworkAccessManager;
    connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    //Q_ASSERT(connRet);
    request.setUrl(QUrl(ht));
    QNetworkReply *reply = naManager->get(request);

}
void HTTPGP::httppost(QString ht,QString testData){//post
    QNetworkRequest request;
    naManager = new QNetworkAccessManager;
    connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    //Q_ASSERT(connRet);
    request.setUrl(QUrl(ht));
    QNetworkReply *reply = naManager->post(request,testData.toUtf8());

}
void HTTPGP::requestFinished(QNetworkReply* reply) {//reply
    // 获取http状态码
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        // 获取返回内容
        QByteArray bytes=reply->readAll();
        QString string = bytes;
        //qDebug() <<string;
        emit RequestFinished(string);
    }
}
