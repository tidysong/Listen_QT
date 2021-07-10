#include "lyrics.h"
#include "ui_lyrics.h"

lyrics::lyrics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lyrics)
{
    ui->setupUi(this);
}

lyrics::~lyrics()
{
    delete ui;
}
