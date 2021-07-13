#include "lyricspage.h"
#include "ui_lyricspage.h"

lyricsPage::lyricsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lyricsPage)
{
    ui->setupUi(this);

    //player::p->play();
    connect(player::p, SIGNAL(PositionChanged(qint64)), this, SLOT(PositionChanged(qint64)));
    connect(player::p, SIGNAL(DurationChanged(qint64)), this, SLOT(DurationChanged(qint64)));
    connect(player::p, SIGNAL(stateChange(QMediaPlayer::State)), this, SLOT(stateChange(QMediaPlayer::State)));
    connect(player::p, SIGNAL(volumeChange(int)), this, SLOT(volumeChange(int)));

    QFile file("F:/毛不易 - 借.lrc");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    stream.setCodec( QTextCodec::codecForName("GB2312") );
    r = new readLyrics(stream.readAll());

    normal = new QFont;                        //字体前后变化
    normalcolor = new QColor("#666666");       //字体前后变化
    now = new QFont;                           //字体前后变化
    nowcolor = new QColor("#333333");          //字体前后变化
    now->setPointSize(16);
    now->setFamily("等线");
    normal->setPointSize(12);
    normal->setFamily("等线");
    r->process();
    line = r->lrclist.length();
    for(int i = 0;i < line;i++){
        QListWidgetItem *item = new QListWidgetItem(r->getLyricText(i));
        item->setTextAlignment(0x0004 | 0x0080);
        item->setFont(*normal);
        item->setTextColor(*normalcolor);
        labelList.append(item);
        ui->listWidget->addItem(item);
    }
}

lyricsPage::~lyricsPage()
{
    delete ui;
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
    player::p->next();
}

void lyricsPage::on_pushButton_2_clicked()
{
    player::p->pre();
}


void lyricsPage::on_pushButton_clicked()
{

    player::p->addMusic("F:/毛不易 - 借.mp3");
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
    anim->setKeyValueAt(0, QRect(590, 600, 80, 0));
    anim->setKeyValueAt(1, QRect(590, 400, 80, 210));
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
    ui->volRate->setText( QString::number(ui->verticalSlider->value()) + "%");
    VolShow = true;
}

void lyricsPage::hideVol(){
    QPropertyAnimation *anim = new QPropertyAnimation(ui->widget_3, "geometry");
    anim->setDuration(100);
    anim->setKeyValueAt(0, QRect(590, 400, 80, 210));
    anim->setKeyValueAt(1, QRect(590, 600, 80, 0));
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
    ui->verticalSlider->setValue(position);
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


