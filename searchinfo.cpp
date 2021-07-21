#include "searchinfo.h"

searchInfo::searchInfo(QString id,QString title, QString url, QString lyricsUrl, QString author,QString album,QString time)
{
    this->id = id;
    this->title = title;
    this->url = url;
    this->author = author;
    this->lyricsUrl = lyricsUrl;
    this->album = album;
    this->time = time;
}
searchInfo::searchInfo(QString id,QString title, QString url, QString lyricsUrl, QString author,QString album,QString time,QString InfoId)
{
    this->id = id;
    this->title = title;
    this->url = url;
    this->author = author;
    this->lyricsUrl = lyricsUrl;
    this->album = album;
    this->time = time;
    this->InfoId = InfoId;
}

searchInfo::searchInfo(QString title, QString url, QString author,QString time,QString createTime)
{
    this->title = title;
    this->url = url;
    this->author = author;
    this->time = time;
    this->createTime = createTime;
}

void searchInfo::setCreateTime(QString createTime){
    this->createTime = createTime;
}
