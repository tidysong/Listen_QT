#include "lyricspage.h"
#include "ui_lyricspage.h"

lyricsPage::lyricsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lyricsPage)
{
    ui->setupUi(this);
    int line = 30;
    QString temp = "这是一行歌词";
    ui->scrollAreaWidgetContents->setMinimumHeight( line*50 + 20 );
    for(int i = 0;i < line;i++){
        QLabel *t = new QLabel(ui->scrollAreaWidgetContents);
        t->setAlignment(Qt::AlignHCenter);
        t->setGeometry(0,i*50+20,350,30);
        t->setStyleSheet("background-color:rgba(0,0,0,0);");
        t->setText(temp +  QString::number(i) );
    }
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

void lyricsPage::on_showList_clicked()
{
    emit showList();
}
