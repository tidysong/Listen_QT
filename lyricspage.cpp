#include "lyricspage.h"
#include "ui_lyricspage.h"

lyricsPage::lyricsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lyricsPage)
{
    ui->setupUi(this);
    lyrics *l = new lyrics(this);
    ui->scrollArea->setWidget(l);
}

lyricsPage::~lyricsPage()
{
    delete ui;
}

void lyricsPage::on_close_clicked()
{
    qApp->quit();
}

void lyricsPage::on_closePage_clicked()
{
    emit closePage();
}
