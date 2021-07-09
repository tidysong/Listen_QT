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
