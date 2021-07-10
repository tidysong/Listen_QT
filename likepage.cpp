#include "likepage.h"
#include "ui_likepage.h"

likePage::likePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::likePage)
{
    ui->setupUi(this);
}

likePage::~likePage()
{
    delete ui;
}
