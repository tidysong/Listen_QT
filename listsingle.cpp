#include "listsingle.h"
#include "ui_listsingle.h"
#include <QString>
listSingle::listSingle(QWidget *parent) : QWidget(parent), ui(new Ui::listSingle)
{
    ui->setupUi(this);
}

listSingle::~listSingle()
{
    delete ui;
}


void listSingle::set(int i){
    ui->label_2->setText(QString::number(i));
}
