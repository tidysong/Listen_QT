#include "downfile.h"

downFile::downFile(QObject *parent) : QObject(parent)
{

}
void downFile::down(QString url, QString id, int type){
    this->url = url;
    this->id = id;
    this->type = type;
    m_networkManager.setProxy(QNetworkProxy::NoProxy);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    connect(&m_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    m_networkManager.get(request);
}

void downFile::replyFinished(QNetworkReply *reply)
{

    // 获取响应状态码，200表示正常
    // QVariant nCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString name;
        if(type == 1){
            name =  QString("cache/%1.mp3").arg(id);
        }else{
            name =  QString("cache/%1.lrc").arg(id);
        }
        QFile file(name);
        if (file.open(QIODevice::WriteOnly))
            file.write(bytes);

        file.close();
        emit success(id,type);
    }
    else
    {
        emit fail();
    }
}


