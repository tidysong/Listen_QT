#include "readlyrics.h"

readLyrics::readLyrics(QString fileCon)
{
    this->fileCon = fileCon;
}
bool readLyrics::process(){
    list = fileCon.split("\n");
    int num = list.length();
    QRegularExpression rex("\\[(\\d+)?:(\\d+\\.\\d+)?\\]"); // 正则表达式匹配时间
    QRegularExpression rew("(\\[(\\d+)?:(\\d+\\.\\d+)?\\])(.*)"); // 正则表达式匹配歌词
    for(int i=0 ; i<num ; i++){
        QString readStr = list.at(i);
        Wordms lrc;
        QRegularExpressionMatch match1 = rex.match(readStr);
        QRegularExpressionMatch match2 = rew.match(readStr);
        lrc.ms = static_cast<unsigned int>((match1.captured(1).toInt() * 60000 + match1.captured(2).toDouble() * 1000)); // 毫秒
        lrc.word = match2.captured(4); // 歌词
        if(!lrc.word.isEmpty()){
            lrclist.append(lrc);
        }
    }
    if( !lrclist.isEmpty() )
        return true;
    else
        return false;
}
int readLyrics::getIndex(qint64 position){
    for(int f=0;f<lrclist.length();f++){
        if( position > lrclist.at(f).ms && position < lrclist.at(f+1).ms ){
            return f;
        }
    }
}
QString readLyrics::getLyricText(int index){
    if( index >= 0 && index <= lrclist.length() ){
        return lrclist.at(index).word;
    }
}
