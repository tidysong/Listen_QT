#include "mainwidget.h"
#include "ui_mainwidget.h"

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
    initUI();
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
    ui->stackedWidget->addWidget(localMusic_page);//添加至
    ui->stackedWidget->addWidget(download_page);
    ui->stackedWidget->addWidget(cloud_page);
    ui->stackedWidget->addWidget(like_page);
    ui->stackedWidget->setCurrentWidget(localMusic_page);//设置默认widget
    ui->menu->item(0)->setSelected(true);


    lyrics_page = new lyricsPage(this);
    lyrics_page->hide();
    connect(lyrics_page,SIGNAL(closePage()),this,SLOT(closeLyrics()));
    connect(lyrics_page,SIGNAL(showList()),this,SLOT(showList()));
    playlist_page = new playList(this);
    playlist_page->hide();
    connect(playlist_page,SIGNAL(closeList()),this,SLOT(closeList()));


    player::p->addMusic("F:/毛不易 - 借.mp3");
    player::p->setIndex(0);
    //curve; //动作曲线
    curve.setType(QEasingCurve::InCubic); //动作曲线方式


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
    login *temp = new login();
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
