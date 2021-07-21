#ifndef SEARCHINFO_H
#define SEARCHINFO_H

#include <QString>
class searchInfo
{
public:
    searchInfo(QString id ,QString title, QString url, QString lyricsUrl, QString author, QString album,QString time);
    searchInfo(QString id ,QString title, QString url, QString lyricsUrl, QString author, QString album,QString time,QString InfoId);
    searchInfo(QString title, QString url, QString author, QString time, QString createTime);
    void setCreateTime(QString);
    QString id,title,url,lyricsUrl,author,album,time,InfoId,createTime;

};

#endif // SEARCHINFO_H
