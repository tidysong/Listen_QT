#include "playlist.h"
#include "ui_playlist.h"

playList::playList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playList)
{
    ui->setupUi(this);
    initUI();
}

playList::~playList()
{
    delete ui;
}


void playList::initUI(){
    setWindowFlags(Qt::FramelessWindowHint);//设置底无边框
    setAttribute(Qt::WA_TranslucentBackground);//设置底透明

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(-4, 0);//设置向哪个方向产生阴影效果(dx,dy)，(0,0)代表向四周发散
    effect->setColor(QColor("#A9A9A9"));//设置阴影颜色
    effect->setBlurRadius(20);//设定阴影的半径大小 30-40
    ui->widget->setGraphicsEffect(effect);//应用至widget
}

void playList::on_pushButton_4_clicked()
{
    emit closeList();
}
