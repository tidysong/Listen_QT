#include "service.h"

service::service(QObject *parent) : QObject(parent)
{

}
bool service::login(QString u,QString p){

    HTTPGP *http = new HTTPGP;
    QString res = http->httppost("http://localhost:3000/z_user/query",QString("username=%1&password=%2").arg(u).arg(p));
    qDebug() << res;
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson("{\"status\":\"200\",\"data\":[{\"id\":1,\"username\":\"啦啦啦\",\"avatar\":\"/uploads/20210619/bc7698478f5c416de6e26a96d497e09fa54ea08a.jpg\",\"age\":18,\"sex\":\"1\",\"status\":\"1\",\"create_time\":1624167027,\"password\":\"1\",\"update_time\":1626278508}]}",&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return false;
    }

    QJsonObject jsonObject = document.object();
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
                    QString usn = icon["username"].toString();
                    qDebug()<< usn;
                }
            }
        }
return true;
}
