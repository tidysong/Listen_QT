#include "playlist.h"
#include "ui_playlist.h"
playList::playList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playList)
{
    ui->setupUi(this);
    initUI();

    connect(player::p, SIGNAL(listChange()), this, SLOT(listChange()));
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

void playList::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
        QListWidgetItem* curItem = ui->listWidget->itemAt( pos );
        if( curItem == NULL )
            return;

        QMenu *popMenu = new QMenu( this );
        popMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
        QAction *deleteSeed = new QAction(tr("从列表删除"), this);
        selectedIndex =  ui->listWidget->row(curItem);
        popMenu->addAction( deleteSeed );

        connect(deleteSeed,SIGNAL(triggered()),this,SLOT(deleteMusicFromList()));
        popMenu->exec( QCursor::pos() );
        delete popMenu;
        delete deleteSeed;
}

void playList::listChange(){
    ui->label_2->setText( QString::number(player::p->musicList.length()) + "首歌曲");
    QListWidget *list= ui->listWidget;
    list->clear();
    for(int i = 0; i < player::p->musicList.length(); i++){
        QListWidgetItem *item=new QListWidgetItem(list,i);
        item->setSizeHint(QSize(256,75));
        listSingle *w = new listSingle(list);
        w->set( player::p->musicList.at(i)->name, player::p->musicList.at(i)->Author, i ,player::p->musicList.at(i)->des);
        list->setItemWidget(item,w);
    }
}

void playList::deleteMusicFromList(){
    player::p->remove(selectedIndex);
}
