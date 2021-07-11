#include "readlyrics.h"

readLyrics::readLyrics()
{

}

bool readLyrics::process(QString filePath){
    //QString.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    list = filePath.split("\n");//QString字符串分割函数
    //qDebug()<<list;
    if(!list.isEmpty())
    return true;
    else
        return false;
}
int readLyrics::getIndex(qint64 position){
    int num=list.length();
    QRegularExpression rex("\\[(\\d+)?:(\\d+\\.\\d+)?\\]"); // 正则表达式匹配时间
    QRegularExpression rew("(\\[(\\d+)?:(\\d+\\.\\d+)?\\])(.*)"); // 正则表达式匹配歌词
    for(int i=0;i<num;i++){
        QString readStr = list.at(i);
        Wordms lrc;
        QRegularExpressionMatch match1 = rex.match(readStr);
        QRegularExpressionMatch match2 = rew.match(readStr);
        lrc.ms = static_cast<unsigned int>((match1.captured(1).toInt() * 60000 + match1.captured(2).toDouble() * 1000)); // 毫秒
        lrc.word = match2.captured(4); // 歌词
        if(!lrc.word.isEmpty()){
            lrclist.append(lrc); // QVector<Wordms> 结构体容器
        }
    }
    /*for(int f=0;f<lrclist.length();f++){
        qDebug()<<lrclist.at(f).ms<<endl;
        qDebug()<<lrclist.at(f).word<<endl;
    }*/
    for(int f=0;f<lrclist.length();f++){
        if(position>lrclist.at(f).ms&&position<lrclist.at(f+1).ms){
            //qDebug()<<lrclist.length()<<endl;
            //qDebug()<<f;
            return f;
        }
    }
}
QString readLyrics::getLyricText(int index){
    if(index>=0&&index<=lrclist.length()){
        qDebug()<<lrclist.at(index).word;
        return lrclist.at(index).word;
    }
}
