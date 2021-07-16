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
