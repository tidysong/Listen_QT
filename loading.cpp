#include "loading.h"
#include "ui_loading.h"

loading::loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loading)
{
    ui->setupUi(this);


    //setWindowFlags(Qt::FramelessWindowHint);//设置底无边框
    //setAttribute(Qt::WA_TranslucentBackground);//设置底透明

    QMovie *movie = new QMovie("F:/Qt_project/listen/pic/loading1.gif");
    ui->label->setMovie(movie);
    movie->start();
}

loading::~loading()
{
    delete ui;
}
