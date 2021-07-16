#include "sigup.h"
#include "ui_sigup.h"

sigUp::sigUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sigUp)
{
    ui->setupUi(this);


    setWindowFlags(Qt::FramelessWindowHint);//设置底无边框
    setAttribute(Qt::WA_TranslucentBackground);//设置底透明



    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 1);//设置向哪个方向产生阴影效果(dx,dy)，(0,0)代表向四周发散
    effect->setColor(QColor("#444444"));//设置阴影颜色
    effect->setBlurRadius(20);//设定阴影的半径大小 30-40
    ui->widget->setGraphicsEffect(effect);//应用至widget
}

sigUp::~sigUp()
{
    delete ui;
}
void sigUp::set(QString pwd){
    password = pwd;
}


void sigUp::on_cancel_clicked()
{
    close();
}

void sigUp::on_password_textChanged(const QString &arg1)
{
    ui->label_2->clear();
}

void sigUp::on_ok_clicked()
{
    if(ui->password->text() != password){
        ui->label_2->setText("两次密码输入不一致！");
    }else{
        emit signReturn();
        close();
    }
}
