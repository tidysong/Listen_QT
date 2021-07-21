#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyDialog)
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

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::set(int type, QString text, int time){
    alertType = type;
    if(type == 0){
        //error
        ui->label_2->setText(text);
        ui->ok->setStyleSheet("#ok{border-bottom-left-radius : 10px;border-bottom-right-radius : 10px;color: #EB4534;}#ok:hover{background-color : #DDDEDE;}#ok:pressed{background-color : #CCCCCC;}");

    }else{
        //success
        ui->label_2->setText(text);
        ui->ok->setStyleSheet("#ok{border-bottom-left-radius : 10px;border-bottom-right-radius : 10px;color: #3176F6;}#ok:hover{background-color : #DDDEDE;}#ok:pressed{background-color : #CCCCCC;}");
    }
    showTime = time;
    ui->label_3->setText(QString::number(time) + "s后自动消失");
    //QTimer *timer = new QTimer(this);

    QTimer::singleShot( time, this, SLOT(update()) );
    //connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(1000);
}
/*
 #ok{
    border-bottom-left-radius : 10px;
    border-bottom-right-radius : 10px;
    color: rgba(3,122,250,1);
}
#ok:hover{
    background-color : #DDDEDE;
}
#ok:hover{
    background-color : #CCCCCC;
}*/

void MyDialog::on_ok_clicked()
{
    close();
}

void MyDialog::update(){
    times++;
    if(times == showTime){
        close();
        return;
    }
    ui->label_3->setText(QString::number(showTime - times) + "s后自动消失");
}
