#ifndef SEARCHINFO_H
#define SEARCHINFO_H

#include <QString>
class searchInfo
{
public:
    searchInfo(QString id ,QString title, QString url, QString lyricsUrl, QString author, QString album,QString time);
    QString id,title,url,lyricsUrl,author,album,time;

};

#endif // SEARCHINFO_H
