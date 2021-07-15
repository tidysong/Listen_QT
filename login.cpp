#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    initUI();
}

login::~login()
{
    delete ui;
}


void login::initUI(){
    setWindowFlags(Qt::FramelessWindowHint);//设置底无边框
    setAttribute(Qt::WA_TranslucentBackground);//设置底透明

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 1);//设置向哪个方向产生阴影效果(dx,dy)，(0,0)代表向四周发散
    effect->setColor(QColor("#444444"));//设置阴影颜色
    effect->setBlurRadius(20);//设定阴影的半径大小 30-40
    ui->widget->setGraphicsEffect(effect);//应用至widget
}

void login::on_close_clicked()
{

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    QTimer *timer;
    timer = new QTimer(this);//初始化
    timer->setSingleShot(true);//定时器只开启一次（可以根据实际需求修改）
    //信号和槽，timer的开始计时信号触发，等待时长，触发this的showMinimized()执行
    connect(timer, SIGNAL(timeout()), this, SLOT(close()));
    timer->start(500);
}
void login::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        is_Press = true;
        m_point = event->pos();
    }
}

// 若鼠标左键被按下，移动窗体位置
void login::mouseMoveEvent(QMouseEvent *event)
{
    if (is_Press)
        move(event->pos() - m_point + pos());
}

// 设置鼠标未被按下
void login::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    is_Press = false;
}

void login::on_loginButton_clicked()
{
    service::login("","");
}
