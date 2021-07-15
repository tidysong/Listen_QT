#include "listsingle.h"
#include "ui_listsingle.h"
#include <QString>
#include <QTextCodec>

listSingle::listSingle(QWidget *parent) : QWidget(parent), ui(new Ui::listSingle)
{
    ui->setupUi(this);
    HideLine();

    //QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    //建立动画
    QPropertyAnimation *anim = new QPropertyAnimation(ui->r1, "geometry");
    anim->setDuration(1000);
    anim->setKeyValueAt(0, QRect(180, 32, 5, 0));
    anim->setKeyValueAt(0.5, QRect(180, 32, 5, 10));
    anim->setKeyValueAt(1, QRect(180, 32, 5, 0));
    anim->setLoopCount(-1);
    anim->start();
    QPropertyAnimation *anim1 = new QPropertyAnimation(ui->r2, "geometry");
    anim1->setDuration(1000);
    anim1->setKeyValueAt(0, QRect(188, 32, 5, 2));
    anim1->setKeyValueAt(0.4, QRect(188, 32, 5, 10));
    anim1->setKeyValueAt(0.9, QRect(188, 32, 5, 0));
    anim1->setKeyValueAt(1, QRect(188, 32, 5, 2));
    anim1->setLoopCount(-1);
    anim1->start();
    QPropertyAnimation *anim2 = new QPropertyAnimation(ui->r3, "geometry");
    anim2->setDuration(1000);
    anim2->setKeyValueAt(0, QRect(196, 32, 5, 6));
    anim2->setKeyValueAt(0.2, QRect(196, 32, 5, 10));
    anim2->setKeyValueAt(0.7, QRect(196, 32, 5, 0));
    anim2->setKeyValueAt(1, QRect(196, 32, 5, 6));
    anim2->setLoopCount(-1);
    anim2->start();
    QPropertyAnimation *anim3 = new QPropertyAnimation(ui->r4, "geometry");
    anim3->setDuration(1000);
    anim3->setKeyValueAt(0, QRect(204, 32, 5, 4));
    anim3->setKeyValueAt(0.3, QRect(204, 32, 5, 10));
    anim3->setKeyValueAt(0.8, QRect(204, 32, 5, 0));
    anim3->setKeyValueAt(1, QRect(204, 32, 5, 4));
    anim3->setLoopCount(-1);
    anim3->start();
    connect(player::p, SIGNAL(stateChange(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(player::p, SIGNAL(MediaChanged(const QMediaContent)), this, SLOT(MediaChanged(const QMediaContent)));

}

listSingle::~listSingle()
{
    delete ui;
}


void listSingle::set(QString name,QString author,int i){
    strScrollCation = name;
    QTimer *pTimer = new QTimer(this);
    connect(pTimer,SIGNAL(timeout()),this,SLOT(scrollCaption()));

    // 定时200毫秒
    pTimer->start(1000);
    //ui->label->setText(name);
    ui->label_2->setText(author);
    ui->label->setToolTip(name);
    ui->label_2->setToolTip(author);
    this->i = i;
    if( player::p->varplay->state() == QMediaPlayer::PlayingState){
        if(player::p->varplaylist->currentIndex() == i){
            ShowLine();
            return;
        }
    }
}
void listSingle::stateChanged(QMediaPlayer::State newState){
    if(newState == QMediaPlayer::PlayingState){
        if(player::p->varplaylist->currentIndex() == i){
            ShowLine();
            return;
        }
    }
    HideLine();
}
void listSingle::MediaChanged(const QMediaContent &content){
    if( player::p->varplay->state() == QMediaPlayer::PlayingState){
        if(player::p->varplaylist->currentIndex() == i){
            ShowLine();
            return;
        }
    }
    HideLine();
}
void listSingle::ShowLine(){
    ui->r1->setStyleSheet("QPushButton{background-color : #3393F9;border : 0px;}");
    ui->r2->setStyleSheet("QPushButton{background-color : #3393F9;border : 0px;}");
    ui->r3->setStyleSheet("QPushButton{background-color : #3393F9;border : 0px;}");
    ui->r4->setStyleSheet("QPushButton{background-color : #3393F9;border : 0px;}");
    if( player::p->varplay->state() == QMediaPlayer::PlayingState){
        QIcon myicon;
        myicon.addFile(tr(":/pic/pause_tg.png"),QSize(20,20));
        ui->play->setIcon(myicon);
        isPlay = true;
    }

}
void listSingle::HideLine(){
    ui->r1->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
    ui->r2->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
    ui->r3->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
    ui->r4->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
    QIcon myicon;
    myicon.addFile(tr(":/pic/play_tg.png"),QSize(25,25));
    ui->play->setIcon(myicon);
    isPlay = false;
}

void listSingle::on_play_clicked()
{
    if(isPlay){
        //如果播放的是当前文件，则直接暂停
        player::p->pause();
    }else{
        //如果播放的不是当前文件/或当前暂停，则切换到当前歌曲播放
        qDebug() << player::p->varplaylist->currentIndex();
        if(player::p->varplaylist->currentIndex() == i){
            player::p->play();
            return;
        }
        player::p->setIndex(i);
        player::p->play();
    }
}
void listSingle::scrollCaption()
{
    static int nPos = 0;

    // 当截取的位置比字符串长时，从头开始
    if (nPos > strScrollCation.length())
        nPos = 0;

    ui->label->setText(strScrollCation.mid(nPos));
    nPos++;
}
