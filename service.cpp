#include "service.h"

service::service(QObject *parent) : QObject(parent)
{

}
void service::login(QString u,QString p){

    HTTPGP *http = new HTTPGP;
    connect(http, SIGNAL(RequestFinished(QString)), this, SLOT(loginReturn(QString)));
    http->httppost(QString("http://42.193.148.10:3000/z_user/query"),QString("username=%1&password=%2").arg(u).arg(p));
    //qDebug() << res;
    //QJsonParseError parseJsonErr;
    //QJsonDocument document = QJsonDocument::fromJson("{\"status\":\"200\",\"data\":[{\"id\":1,\"username\":\"啦啦啦\",\"avatar\":\"/uploads/20210619/bc7698478f5c416de6e26a96d497e09fa54ea08a.jpg\",\"age\":18,\"sex\":\"1\",\"status\":\"1\",\"create_time\":1624167027,\"password\":\"1\",\"update_time\":1626278508}]}",&parseJsonErr);
    //if(!(parseJsonErr.error == QJsonParseError::NoError))
    //{
    //    qDebug()<<tr("解析json文件错误！");
    //    return false;
    //}
    //
    //QJsonObject jsonObject = document.object();
    //if(jsonObject.contains(QStringLiteral("data")))
    //    {
    //        QJsonValue arrayValue = jsonObject.value(QStringLiteral("data"));
    //        if(arrayValue.isArray())
    //        {
    //            QJsonArray array = arrayValue.toArray();
    //            for(int i=0;i<array.size();i++)
    //            {
    //                QJsonValue iconArray = array.at(i);
    //                QJsonObject icon = iconArray.toObject();
    //                QString usn = icon["username"].toString();
    //                qDebug()<< usn;
    //            }
    //        }
    //    }
}
void service::search(QString title){
    HTTPGP *http = new HTTPGP;
    connect(http, SIGNAL(RequestFinished(QString)), this, SLOT(searchReturn(QString)));
    http->httppost(QString("http://42.193.148.10:3000/z_music/query"),QString("title=%1").arg(title));

}

void service::cloud(){
    Inifile *i = new Inifile;
    HTTPGP *http = new HTTPGP;
    connect(http, SIGNAL(RequestFinished(QString)), this, SLOT(cloudReturn(QString)));
    http->httppost(QString("http://42.193.148.10:3000/z_cloud/query"),QString("userId=%1").arg(i->Readlogintime()));
}
void service::loginReturn(QString res){
    //qDebug() << res;
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(res.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }

    QJsonObject jsonObject = document.object();
    if(jsonObject.contains(QStringLiteral("data"))){
        QJsonValue arrayValue = jsonObject.value(QStringLiteral("data"));
        //qDebug() << arrayValue.toArray().size();
        if( arrayValue.toArray().size() == 1){
            QJsonArray array = arrayValue.toArray();
            QJsonValue iconArray = array.at(0);
            QJsonObject icon = iconArray.toObject();
            Inifile *i = new Inifile;
            i->Savelogintime(QString::number(icon["id"].toInt()));
            emit LoginSuccess();
            return;
        }
        //if(arrayValue.isArray())
        //{
        //    QJsonArray array = arrayValue.toArray();
        //    for(int i=0;i<array.size();i++)
        //    {
        //        QJsonValue iconArray = array.at(i);
        //        QJsonObject icon = iconArray.toObject();
        //        QString usn = icon["username"].toString();
        //        qDebug()<< usn;
        //    }
        //}
    }
    emit LoginFail();
}


void service::searchReturn(QString res){
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(res.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }

    QJsonObject jsonObject = document.object();
    searchList.clear();
    if(jsonObject.contains(QStringLiteral("data")))
    {
        QJsonValue arrayValue = jsonObject.value(QStringLiteral("data"));
        if(arrayValue.isArray())
        {
            QJsonArray array = arrayValue.toArray();
            for(int i=0;i<array.size();i++)
            {
                QJsonValue iconArray = array.at(i);
                QJsonObject icon = iconArray.toObject();
                //QString usn = icon["musicFile"].toString();
                //qDebug()<< usn;//QString id ,QString title, QString url, QString lyricsUrl, QString author
                //qDebug() << icon["id"].toString();
                searchInfo *s = new searchInfo(QString::number(icon["Id"].toInt()), icon["title"].toString(), headUrl + icon["musicFile"].toString(), headUrl + icon["lrcFile"].toString(), icon["author"].toString(),icon["album"].toString(), icon["time"].toString());
                searchList.append(s);
            }
        }
    }
    emit searchSuccess(searchList);
}



void service::cloudReturn(QString res){
    //qDebug() << res;
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(res.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }

    QJsonObject jsonObject = document.object();
    cloudList.clear();
    if(jsonObject.contains(QStringLiteral("data")))
    {
        QJsonValue arrayValue = jsonObject.value(QStringLiteral("data"));
        if(arrayValue.isArray())
        {
            QJsonArray array = arrayValue.toArray();
            for(int i=0;i<array.size();i++)
            {
                QJsonValue iconArray = array.at(i);
                QJsonObject icon = iconArray.toObject();
                QJsonObject arrayValue1 = icon.value(QStringLiteral("z_music")).toObject();

                searchInfo *s = new searchInfo(QString::number(arrayValue1["Id"].toInt()), arrayValue1["title"].toString(), headUrl + arrayValue1["musicFile"].toString(), headUrl + arrayValue1["lrcFile"].toString(), arrayValue1["author"].toString(),arrayValue1["album"].toString(), arrayValue1["time"].toString(),QString::number(icon["Id"].toInt()));
                cloudList.append(s);
            }
        }
    }
    emit cloudSuccess(cloudList);
}


void service::addCloud(QString id){
    Inifile *i = new Inifile;
    QString userId = i->Readlogintime();
    HTTPGP *http = new HTTPGP;
    connect(http, SIGNAL(RequestFinished(QString)), this, SLOT(addCloudReturn(QString)));
    http->httppost(QString("http://42.193.148.10:3000/z_cloud/add"),QString("userId=%1&musicId=%2").arg(userId).arg(id));
}

void service::addCloudReturn(QString){
    emit addCloudSuccess();
}


void service::deleteCloud(QString id){

    HTTPGP *http = new HTTPGP;
    connect(http, SIGNAL(RequestFinished(QString)), this, SLOT(deleteCloudReturn(QString)));
    http->httppost(QString("http://42.193.148.10:3000/z_cloud/update"),QString("Id=%1").arg(id));

}


void service::deleteCloudReturn(QString res){
    emit deleteCloudSuccess();
}


void service::sigup(QString u,QString p){
    HTTPGP *http = new HTTPGP;
    connect(http, SIGNAL(RequestFinished(QString)), this, SLOT(sigupReturn(QString)));
    http->httppost(QString("http://42.193.148.10:3000/z_user/add"),QString("username=%1&password=%2").arg(u).arg(p));
}

void service::sigupReturn(QString res){
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(res.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }
    emit sigupSuccess( QString::number(document.object()["id"].toInt()) );
}
