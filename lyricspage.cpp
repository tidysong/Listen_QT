#include "lyricspage.h"
#include "ui_lyricspage.h"

lyricsPage::lyricsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lyricsPage)
{
    ui->setupUi(this);



    QFile file("E:/借 - 毛不易.lrc");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    stream.setCodec( QTextCodec::codecForName("GB2312") );
    readLyrics *r = new readLyrics(stream.readAll());


    r->process();
    int line = r->lrclist.length();
    qDebug() << line;
    ui->scrollAreaWidgetContents->setMinimumHeight( line*50 + 20 );
    labelList.clear();
    for(int i = 0;i < line;i++){
        QLabel *t = new QLabel(ui->scrollAreaWidgetContents);
        labelList.append(t);
        t->setAlignment(Qt::AlignHCenter);
        t->setGeometry(0,i*50+20,350,30);
        t->setStyleSheet("background-color:rgba(0,0,0,0);");
        t->setText(r->getLyricText(i) );
    }
    labelList.at(5)->setStyleSheet("background-color:rgba(0,0,0,0);font-weight:bold;font-size:18px;");
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
