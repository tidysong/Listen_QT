#include "mainwidget.h"
#include "ui_mainwidget.h"
bool MainWidget::isLogin = false;
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    connect(player::p, SIGNAL(MediaChanged(const QMediaContent)), this, SLOT(MediaChanged(const QMediaContent)));
    connect(player::p, SIGNAL(PositionChanged(qint64)), this, SLOT(PositionChanged(qint64)));
    connect(player::p, SIGNAL(DurationChanged(qint64)), this, SLOT(DurationChanged(qint64)));
    connect(player::p, SIGNAL(stateChange(QMediaPlayer::State)), this, SLOT(stateChange(QMediaPlayer::State)));
    //connect(player::p, SIGNAL(volumeChange(int)), this, SLOT(volumeChange(int)));
    connect(player::p, SIGNAL(modeChange(QMediaPlaylist::PlaybackMode)), this, SLOT(modeChange(QMediaPlaylist::PlaybackMode)));


    initUI();
    initConfig();



    //loading *load = new loading;
    //load->show();
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::initUI(){
    //初始化UI

    setWindowFlags(Qt::FramelessWindowHint);//设置底无边框
    setAttribute(Qt::WA_TranslucentBackground);//设置底透明

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 1);//设置向哪个方向产生阴影效果(dx,dy)，(0,0)代表向四周发散
    effect->setColor(QColor("#444444"));//设置阴影颜色
    effect->setBlurRadius(20);//设定阴影的半径大小 30-40
    ui->widget->setGraphicsEffect(effect);//应用至widget

    ui->menu->setFocusPolicy(Qt::NoFocus);

    localMusic_page = new localMusic(this);//初始化四个widget
    download_page = new downloadPage(this);
    cloud_page = new cloudList(this);
    like_page = new likePage(this);
    search_page = new searchOnline(this);
    ui->stackedWidget->addWidget(localMusic_page);//添加至
    ui->stackedWidget->addWidget(download_page);
    ui->stackedWidget->addWidget(cloud_page);
    ui->stackedWidget->addWidget(like_page);
    ui->stackedWidget->addWidget(search_page);
    ui->stackedWidget->setCurrentWidget(localMusic_page);//设置默认widget
    ui->menu->item(0)->setSelected(true);


    lyrics_page = new lyricsPage(this);
    lyrics_page->hide();
    connect(lyrics_page,SIGNAL(closePage()),this,SLOT(closeLyrics()));
    connect(lyrics_page,SIGNAL(showList()),this,SLOT(showList()));
    playlist_page = new playList(this);
    playlist_page->hide();
    connect(playlist_page,SIGNAL(closeList()),this,SLOT(closeList()));

    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect(this);
    effect1->setOffset(0, 1);//设置向哪个方向产生阴影效果(dx,dy)，(0,0)代表向四周发散
    effect1->setColor(QColor("#999999"));//设置阴影颜色
    effect1->setBlurRadius(20);//设定阴影的半径大小 30-40
    ui->widget_4->setGraphicsEffect(effect1);//应用至widget

    player::p->addMusic("F:/毛不易 - 借.mp3");
    player::p->setIndex(0);
    //curve; //动作曲线
    curve.setType(QEasingCurve::InCubic); //动作曲线方式


}
void MainWidget::initConfig(){
    Inifile *i = new Inifile;
    //读取登录信息
    if( !(i->Readpassword().isEmpty() && i->Readusername().isEmpty()) ){
        //以前登录成功过
        login *temp = new login();
        connect(temp,SIGNAL(logSuccess()),this,SLOT(logSuccess()));
        temp->set(i->Readusername(),i->Readpassword());
        temp->show();
    }
    //读取播放顺序
    QString mode = i->Readplaymode();
    player::p->varplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    if(mode.isEmpty()){
        player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Loop);
        i->Saveplaymode("1");
    }else{
        if( mode == "1"){
            player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Loop);
        }else if( mode == "2" ){
            player::p->varplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        }else if( mode == "3" ){
            player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Random);
        }
    }
}
void MainWidget::on_close_clicked()
{
    //关闭按钮
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    QTimer *timer;
    timer = new QTimer(this);//初始化
    timer->setSingleShot(true);//定时器只开启一次（可以根据实际需求修改）
    //信号和槽，timer的开始计时信号触发，等待时长，触发this的showMinimized()执行
    connect(timer, SIGNAL(timeout()), qApp, SLOT(quit()));
    timer->start(500);
}


void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if(VolShow){
        hideVol();
    }
    if(isLyricsShow){
        lyrics_page->volCheck(event->pos().x(), event->pos().y());
    }
    if(isListShow && !(event->pos().x() >=752 && event->pos().x()  <= 1065) ){
        //list展示 且区域不在范围内
        isListShow = false;
        QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(playlist_page, "pos");
        pScaleAnimation->setDuration(200);
        pScaleAnimation->setStartValue(QPoint(752, 0));
        pScaleAnimation->setEndValue(QPoint(1065, 0));
        pScaleAnimation->start();

        QTimer *timer;
        timer = new QTimer(this);//初始化
        timer->setSingleShot(true);//定时器只开启一次（可以根据实际需求修改）
        //信号和槽，timer的开始计时信号触发，等待时长，触发this的showMinimized()执行
        connect(timer, SIGNAL(timeout()), playlist_page, SLOT(show()));
        timer->start(200);
    }
    if (event->button() == Qt::LeftButton && event->pos().y() <= 90)
    {
        is_Press = true;
        m_point = event->pos();
    }
}

// 若鼠标左键被按下，移动窗体位置
void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (is_Press)
        move(event->pos() - m_point + pos());
}

// 设置鼠标未被按下
void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    is_Press = false;
}

void MainWidget::showEvent(QShowEvent *event){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}
void MainWidget::on_min_clicked()
{
    //最小化窗口
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    QTimer *timer;
    timer = new QTimer(this);//初始化
    timer->setSingleShot(true);//定时器只开启一次（可以根据实际需求修改）
    //信号和槽，timer的开始计时信号触发，等待时长，触发this的showMinimized()执行
    connect(timer, SIGNAL(timeout()), this, SLOT(showMinimized()));
    timer->start(300);
}

void MainWidget::on_menu_clicked(const QModelIndex &index)
{
    int _index = index.row();
    if(_index == 0){
        ui->stackedWidget->setCurrentWidget(localMusic_page);
    }else if(_index == 1){
        ui->stackedWidget->setCurrentWidget(download_page);
    }else if(_index == 2){
        ui->stackedWidget->setCurrentWidget(cloud_page);
    }else{
        ui->stackedWidget->setCurrentWidget(like_page);
    }

}

void MainWidget::on_avatar_clicked()
{
    if(MainWidget::isLogin){
        //已经登录过
        return;
    }
    login *temp = new login();
    connect(temp,SIGNAL(logSuccess()),this,SLOT(logSuccess()));
    temp->show();
}

void MainWidget::on_pushButton_4_clicked()
{
    showListf();
}

void MainWidget::showListf(){
    playlist_page->show();
    isListShow = true;
    QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(playlist_page, "pos");
    pScaleAnimation->setDuration(50);
    pScaleAnimation->setStartValue(QPoint(1065, 0));
    pScaleAnimation->setEndValue(QPoint(752, 0));
    pScaleAnimation->setEasingCurve(curve);
    pScaleAnimation->start();
}
void MainWidget::closeListf(){
    isListShow = false;
    QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(playlist_page, "pos");
    pScaleAnimation->setDuration(50);
    pScaleAnimation->setStartValue(QPoint(752, 0));
    pScaleAnimation->setEndValue(QPoint(1065, 0));
    pScaleAnimation->setEasingCurve(curve);
    pScaleAnimation->start();

    QTimer *timer;
    timer = new QTimer(this);//初始化
    timer->setSingleShot(true);//定时器只开启一次（可以根据实际需求修改）
    //信号和槽，timer的开始计时信号触发，等待时长，触发this的showMinimized()执行
    connect(timer, SIGNAL(timeout()), playlist_page, SLOT(hide()));
    timer->start(200);
}
void MainWidget::closeList(){
    //SLOT 关闭playList
    closeListf();
}
void MainWidget::showList(){
    //SLOT 打开playList
    showListf();
}
void MainWidget::closeLyrics(){
    //SLOT 关闭lyrics
    isLyricsShow = false;
    QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(lyrics_page, "pos");
    pScaleAnimation->setDuration(200);
    pScaleAnimation->setStartValue(QPoint(0, 0));
    pScaleAnimation->setEndValue(QPoint(0, 632));
    pScaleAnimation->setEasingCurve(curve);
    pScaleAnimation->start();

    QTimer *timer;
    timer = new QTimer(this);//初始化
    timer->setSingleShot(true);//定时器只开启一次（可以根据实际需求修改）
    //信号和槽，timer的开始计时信号触发，等待时长，触发this的showMinimized()执行
    connect(timer, SIGNAL(timeout()), lyrics_page, SLOT(hide()));
    timer->start(200);
}

void MainWidget::on_pushButton_clicked()
{
    //展示歌词界面
    lyrics_page->show();
    isLyricsShow = true;
    QPropertyAnimation *pScaleAnimation = new QPropertyAnimation(lyrics_page, "pos");
    pScaleAnimation->setDuration(200);
    pScaleAnimation->setStartValue(QPoint(0, 632));
    pScaleAnimation->setEndValue(QPoint(0, 0));
    pScaleAnimation->setEasingCurve(curve);
    pScaleAnimation->start();
}

void MainWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    event->acceptProposedAction();
}

//当用户放下这个文件后，就会触发dropEvent事件
void MainWidget::dropEvent(QDropEvent *event)
{
    //注意：这里如果有多文件存在，意思是用户一下子拖动了多个文件，而不是拖动一个目录
    //如果想读取整个目录，则在不同的操作平台下，自己编写函数实现读取整个目录文件名
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())return;
    foreach(QUrl url, urls) {
        player::p->addMusic(url.toLocalFile());
    }
}


void MainWidget::logSuccess(){
    QIcon myicon;
    myicon.addFile(tr(":/pic/Login.png"),QSize(100,100));
    ui->avatar->setIcon(myicon);

    Inifile *ifile = new Inifile;
    ui->user->setText("欢迎您，" + ifile->Readusername());
    MainWidget::isLogin = true;
    cloud_page->load();
}

void MainWidget::on_searchText_returnPressed()
{
    ui->menu->item(0)->setSelected(false);
    ui->menu->item(1)->setSelected(false);
    ui->menu->item(2)->setSelected(false);
    ui->menu->item(3)->setSelected(false);
    ui->stackedWidget->setCurrentWidget(search_page);
    search_page->set(ui->searchText->text());
}


QString MainWidget::formatTime(qint64 ms)
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
void MainWidget::DurationChanged(qint64 postion){
    ui->time2->setText(formatTime(postion));
    ui->horizontalSlider->setRange(0,postion);
    ui->horizontalSlider->setEnabled(postion>0);
    ui->horizontalSlider->setPageStep(postion/10);
}
void MainWidget::PositionChanged(qint64 postion){
    ui->horizontalSlider->setValue(postion);
    ui->time1->setText(formatTime(postion));
}


void MainWidget::stateChange(QMediaPlayer::State newState){
    if(newState == QMediaPlayer::PlayingState){
        QIcon myicon;
        myicon.addFile(tr(":/pic/pause.png"),QSize(25,25));
        ui->play->setIcon(myicon);
    }else if(newState == QMediaPlayer::PausedState){
        QIcon myicon;
        myicon.addFile(tr(":/pic/play.png"),QSize(25,25));
        ui->play->setIcon(myicon);
    }
}

void MainWidget::MediaChanged(const QMediaContent &content){
    //isJustOpen = false;
    ui->label->setText(player::p->musicList.at(player::p->varplaylist->currentIndex())->name);
    ui->label_2->setText(player::p->musicList.at(player::p->varplaylist->currentIndex())->Author);

}

void MainWidget::modeChange(QMediaPlaylist::PlaybackMode mode){
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


void MainWidget::on_play_clicked()
{
    if(player::p->varplay->state() == QMediaPlayer::PlayingState){
        player::p->pause();
    }else{
        player::p->play();
    }
}

void MainWidget::on_pushButton_2_clicked()
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

void MainWidget::on_pushButton_3_clicked()
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

void MainWidget::on_modeChange_clicked()
{
    if(player::p->varplaylist->playbackMode() == QMediaPlaylist::Loop){
        player::p->varplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }else if(player::p->varplaylist->playbackMode() == QMediaPlaylist::CurrentItemInLoop){
        player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Random);
    }else{
        player::p->varplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    }
}

void MainWidget::on_pushButton_5_clicked()
{
    if(VolShow){
        hideVol();
    }else{
        showVol();
    }
}

void MainWidget::showVol(){
    QPropertyAnimation *anim = new QPropertyAnimation(ui->widget_4, "geometry");
    anim->setDuration(100);
    anim->setKeyValueAt(0, QRect(703, 570, 60, 0));
    anim->setKeyValueAt(1, QRect(703, 370, 60, 220));
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
    ui->volRate->setText( QString::number(ui->verticalSlider->value()) + "%");
    VolShow = true;
}

void MainWidget::hideVol(){
    QPropertyAnimation *anim = new QPropertyAnimation(ui->widget_4, "geometry");
    anim->setDuration(100);
    anim->setKeyValueAt(0, QRect(703, 370, 60, 220));
    anim->setKeyValueAt(1, QRect(703, 570, 60, 0));
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start();
    ui->volRate->clear();
    VolShow = false;
}

void MainWidget::on_verticalSlider_valueChanged(int value)
{
    player::p->setVol(value);
    ui->volRate->setText(QString::number(value) + "%");
}

void MainWidget::on_horizontalSlider_sliderMoved(int position)
{
    prePosition = position;
}

void MainWidget::on_horizontalSlider_sliderReleased()
{
    player::p->setPosition(prePosition);
}
