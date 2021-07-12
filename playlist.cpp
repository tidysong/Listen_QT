#include "playlist.h"
#include "ui_playlist.h"
playList::playList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playList)
{
    ui->setupUi(this);
    initUI();
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

    QListWidget *list= ui->listWidget;
    for(int i = 0; i < 10; i++){
        QListWidgetItem *item=new QListWidgetItem(list,i);
        item->setSizeHint(QSize(256,75));
        listSingle *w = new listSingle(list);
        w->set(i);
        list->setItemWidget(item,w);
    }
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
        QAction *playSeed = new QAction(tr("立即播放"), this);
        QAction *deleteSeed = new QAction(tr("从列表删除"), this);

        QAction *cloudSeed = new QAction(tr("添加到歌单"), this);
        QAction *likeSeed = new QAction(tr("收藏歌曲"), this);
        popMenu->addAction( playSeed );
        popMenu->addAction( deleteSeed );
        popMenu->addAction( cloudSeed );
        popMenu->addAction( likeSeed );
        popMenu->exec( QCursor::pos() );
        delete popMenu;
        delete deleteSeed;
        delete playSeed;delete cloudSeed;delete likeSeed;
}
