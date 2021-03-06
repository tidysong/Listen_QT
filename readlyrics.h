#ifndef READLYRICS_H
#define READLYRICS_H
#include <QString>
#include<QStringList>
#include <QDebug>
#include <QRegExp>
#include <QRegularExpressionMatch>
class readLyrics
{

public:
    typedef struct words
    {
        unsigned int ms;
        QString word;
    } Wordms;
    readLyrics(QString fileCon);
    QStringList list;
    QList<Wordms> lrclist;
    QString fileCon;
    bool process();
    int getIndex(qint64 position);
    QString getLyricText(int index);

};

#endif // READLYRICS_H
