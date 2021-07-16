#include "lyricspage.h"
#include "ui_lyricspage.h"

lyricsPage::lyricsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lyricsPage)
{
    ui->setupUi(this);

    initUI();
    //player::p->play();
    connect(player::p, SIGNAL(MediaChanged(const QMediaContent)), this, SLOT(MediaChanged(const QMediaContent)));
    connect(player::p, SIGNAL(PositionChanged(qint64)), this, SLOT(PositionChanged(qint64)));
    connect(player::p, SIGNAL(DurationChanged(qint64)), this, SLOT(DurationChanged(qint64)));
    connect(player::p, SIGNAL(stateChange(QMediaPlayer::State)), this, SLOT(stateChange(QMediaPlayer::State)));
    connect(player::p, SIGNAL(volumeChange(int)), this, SLOT(volumeChange(int)));
    connect(player::p, SIGNAL(modeChange(QMediaPlaylist::PlaybackMode)), this, SLOT(modeChange(QMediaPlaylist::PlaybackMode)));
    connect(player::p, SIGNAL(stateChange(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    //openLyrics("");
}

lyricsPage::~lyricsPage()
{
    delete ui;
}

void lyricsPage::initUI(){
    normal = new QFont;                        //字体前后变化
    normalcolor = new QColor("#666666");       //字体前后变化
    now = new QFont;                           //字体前后变化
    nowcolor = new QColor("#333333");          //字体前后变化
    now->setPointSize(16);
    now->setFamily("等线");
    normal->setPointSize(12);
    normal->setFamily("等线");


    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 1);//设置向哪个方向产生阴影效果(dx,dy)，(0,0)代表向四周发散
    effect->setColor(QColor("#999999"));//设置阴影颜色
    effect->setBlurRadius(20);//设定阴影的半径大小 30-40
    ui->widget_3->setGraphicsEffect(effect);//应用至widget
}
void lyricsPage::on_close_clicked()
{
    qApp->quit();
}

void lyricsPage::on_closePage_clicked()
{
    emit closePage();
}

void lyricsPage::on_showList_clicked()
{
    emit showList();
}
void lyricsPage::DurationChanged(qint64 postion){
    ui->time2->setText(formatTime(postion));
    ui->horizontalSlider->setRange(0,postion);
    ui->horizontalSlider->setEnabled(postion>0);
    ui->horizontalSlider->setPageStep(postion/10);
}
void lyricsPage::PositionChanged(qint64 postion){
    if(isJustOpen){
        return;
    }
    ui->horizontalSlider->setValue(postion);
    ui->time1->setText(formatTime(postion));
    int index = r->getIndex(postion);
    if(index != lastIndex){
        labelList.at(lastIndex)->setFont(*normal);
        labelList.at(lastIndex)->setTextColor(*normalcolor);
        labelList.at(index)->setFont(*now);
        labelList.at(index)->setTextColor(*nowcolor);
        lastIndex = index;
        if(index < 2){
            ui->listWidget->verticalScrollBar()->setValue(0);
        }else{
            ui->listWidget->verticalScrollBar()->setValue( index - 2 );
        }
    }
}

QString lyricsPage::formatTime(qint64 ms)
{
    int ss = 1000;
    int mi = ss * 60;
    int hh = mi * 60;
    int dd = hh * 24;
    long day = ms / dd;
    long hour = (ms - day * dd) / hh;
    long minute = (ms - day * dd - hour * hh) / mi;
    long second = (ms - day * dd - hour * hh - minute * mi) / ss;
    QString min = QString::number(minute,10).sprintf("%02d",minute);
    QString sec = QString::number(second,10).sprintf("%02d",second);
    return min + ":" + sec ;
}

void lyricsPage::on_listWidget_doubleClicked(const QModelIndex &index)
{
    player::p->setPosition(r->lrclist.at(index.row()).ms);
}



void lyricsPage::on_play_clicked()
{
    if(isPlay){
        player::p->pause();
    }else{
        player::p->play();
    }
}

void lyricsPage::stateChange(QMediaPlayer::State newState){
    if(newState == QMediaPlayer::PlayingState){
        isPlay = true;
        QIcon myicon;
        myicon.addFile(tr(":/pic/pause.png"),QSize(25,25));
        ui->play->setIcon(myicon);
    }else if(newState == QMediaPlayer::PausedState){
        isPlay = false;
        QIcon myicon;
        myicon.addFile(tr(":/pic/play.png"),QSize(25,25));
        ui->play->setIcon(myicon);
    }
}

void lyricsPage::on_horizontalSlider_sliderMoved(int position)
{
    prePosition = position;
    //player::p->setPosition(position);
}



void lyricsPage::on_pushButton_3_clicked()
{
    if(player::p->varplaylist->playbackMode() == QMediaPlaylist::CurrentItemInLoop){
        //当前是单曲循环则采用index方式
        if(player::p->musicList.length()  == player::p->varplaylist->currentIndex() + 1){
            player::p->varplaylist->setCurrentIndex(0);
        }else{
            player::p->varplaylist->setCurrentIndex( player::p->varplaylist->currentIndex() + 1 );
        }
        return;
    }
    player::p->next();
}

void lyricsPage::on_pushButton_2_clicked()
{
    if(player::p->varplaylist->playbackMode() == QMediaPlaylist::CurrentItemInLoop){
        //当前是单曲循环则采用index方式
        if(player::p->varplaylist->currentIndex() == 0){
            player::p->varplaylist->setCurrentIndex( player::p->musicList.length() -1 );
        }else{
            player::p->varplaylist->setCurrentIndex( player::p->varplaylist->currentIndex() - 1 );
        }
        return;
    }
    player::p->pre();
}


void lyricsPage::on_pushButton_clicked()
{

    player::p->addMusic("F:/毛不易.mp3");
}

void lyricsPage::on_pushButton_4_clicked()
{
    //widget_3
    if(VolShow){
        hideVol();
    }else{
        showVol();
    }

}

void lyricsPage::showVol(){
    QPropertyAnimation *anim = new QPropertyAnimation(ui->widget_3, "geometry");
    anim->setDuration(100);
    anim->setKeyValueAt(0, QRect(600, 570, 60, 0));
    anim->setKeyValueAt(1, QRect(600, 370, 60, 220));
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
    ui->verticalSlider->setValue(player::p->varplay->volume());
    ui->volRate->setText( QString::number(ui->verticalSlider->value()) + "%");
    VolShow = true;
}

void lyricsPage::hideVol(){
    QPropertyAnimation *anim = new QPropertyAnimation(ui->widget_3, "geometry");
    anim->setDuration(100);
    anim->setKeyValueAt(0, QRect(600, 370, 60, 220));
    anim->setKeyValueAt(1, QRect(600, 570, 60, 0));
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
    ui->volRate->clear();
    VolShow = false;
}

void lyricsPage::on_verticalSlider_valueChanged(int value)
{
    player::p->setVol(value);
    ui->volRate->setText(QString::number(value) + "%");
}

void lyricsPage::volumeChange(int position){
    if(VolShow){
        ui->verticalSlider->setValue(position);
    }

}

void lyricsPage::volCheck(int x,int y){
    if(VolShow){
        hideVol();
    }
}

void lyricsPage::on_horizontalSlider_sliderReleased()
{
    player::p->setPosition(prePosition);
}


void lyricsPage::openLyrics(QString filePath){
    filePath = filePath.replace(QRegularExpression("\\..*"),".lrc");
    QFile file(filePath);
    QString cont;
    if(!file.open(QIODevice::ReadOnly)){
        cont = "[00:00.000]当前歌曲暂无歌词";
    }else{
        QTextStream stream(&file);
        stream.setCodec( QTextCodec::codecForName("GB2312") );
        cont = stream.readAll();
    }
    r = new readLyrics(cont);
    r->process();
    line = r->lrclist.length();
    ui->listWidget->clear();
    labelList.clear();
    for(int i = 0;i < line;i++){
        QListWidgetItem *item = new QListWidgetItem(r->getLyricText(i));
        item->setTextAlignment(0x0004 | 0x0080);
        item->setFont(*normal);
        item->setTextColor(*normalcolor);
        labelList.append(item);
        ui->listWidget->addItem(item);
    }
    //file.close();//销毁file
}
void lyricsPage::MediaChanged(const QMediaContent &content){
    isJustOpen = false;
    //#E2EAF2
    //#DDDDDD
    ui->label->setText(player::p->musicList.at(player::p->varplaylist->currentIndex())->name);
    ui->label_2->setText(player::p->musicList.at(player::p->varplaylist->currentIndex())->Author);
    openLyrics(player::p->musicList.at(player::p->varplaylist->currentIndex())->filePath);
    lastIndex = 0;

}

void lyricsPage::modeChange(QMediaPlaylist::PlaybackMode mode){
    Inifile *i = new Inifile;
    if(mode == QMediaPlaylist::CurrentItemInLoop){
        //单曲循环
        QIcon myicon;
        myicon.addFile(tr(":/pic/mode2.png"),QSize(25,25));
        ui->modeChange->setIcon(myicon);
        ui->modeChange->setToolTip("单曲循环");
        i->Saveplaymode("2");

    }else if(mode == QMediaPlaylist::Loop){
        //列表循环
        QIcon myicon;
        myicon.addFile(tr(":/pic/mode1.png"),QSize(25,25));
        ui->modeChange->setIcon(myicon);
        ui->modeChange->setToolTip("列表循环");
        i->Saveplaymode("1");
    }else if(mode == QMediaPlaylist::Random){
        //随机播放
        QIcon myicon;
        myicon.addFile(tr(":/pic/mode3.png"),QSize(25,25));
        ui->modeChange->setIcon(myicon);
        ui->modeChange->setToolTip("随机播放");
        i->Saveplaymode("3");
    }
}

void lyricsPage::on_pushButton_5_clicked()
{
    player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Random);
}

void lyricsPage::on_modeChange_clicked()
{
    if(player::p->varplaylist->playbackMode() == QMediaPlaylist::Loop){
        player::p->varplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }else if(player::p->varplaylist->playbackMode() == QMediaPlaylist::CurrentItemInLoop){
        player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Random);
    }else{
        player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    }
}

void lyricsPage::stateChanged(QMediaPlayer::State newState){
    if(newState == QMediaPlayer::PlayingState){
        ui->widget->setStyleSheet(QString("background-color : qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 ") + QString("#E2EAF2") + QString(", stop:1 #FFFFFF);border-radius:10px;"));
    }else{
        ui->widget->setStyleSheet(QString("background-color : qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 ") + QString("#DDDDDD") + QString(", stop:1 #FFFFFF);border-radius:10px;"));
    }
}
