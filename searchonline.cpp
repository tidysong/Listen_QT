#include "searchonline.h"
#include "ui_searchonline.h"

searchOnline::searchOnline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchOnline)
{
    ui->setupUi(this);
    initUI();
}

searchOnline::~searchOnline()
{
    delete ui;
}
void searchOnline::initUI(){
    ui->musicList->setColumnWidth(0,60);
    ui->musicList->setColumnWidth(1,300);
    ui->musicList->setColumnWidth(2,150);
    ui->musicList->setColumnWidth(3,150);
    ui->musicList->setColumnWidth(4,100);
    ui->musicList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->musicList->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color:white; border:none; border-right:1px solid #E5E5E5;height:25px;border-top-right-radius:10px;border-top-left-radius:10px;}");
    ui->musicList->horizontalHeader()->setHighlightSections(false);

    ui->musicList->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    ui->musicList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->musicList->verticalHeader()->setVisible(false); //隐藏列表头
    ui->musicList->setSelectionMode(QAbstractItemView::SingleSelection);//只选一行
    ui->musicList->horizontalHeader()->setVisible(true);
}
void searchOnline::set(QString title){
    //搜索
    for(int row = ui->musicList->rowCount() - 1;row >= 0; row--)
    {
        ui->musicList->removeRow(row);
    }
    service *search = new service;
    connect(search, SIGNAL(searchSuccess(QList<searchInfo*>)), this, SLOT(searchSuccess(QList<searchInfo*>)));
    search->search(title);
    ui->label->setText("正在搜索有关“" + title + "”" + "的歌曲");
}
void searchOnline::searchSuccess(QList<searchInfo*> list){
    this->list = list;
    emit succ();
    ui->musicList->clearContents();
    ui->label->setText(QString("找到%1首单曲").arg(list.length()));
    for(int i = 0; i < list.length(); i++){
        int RowCont;
        RowCont=ui->musicList->rowCount();
        ui->musicList->insertRow(RowCont);
        ui->musicList->setItem(RowCont,0,new QTableWidgetItem(QString::number(i + 1).sprintf("%02d",i + 1)));
        ui->musicList->setItem(RowCont,1,new QTableWidgetItem(list.at(i)->title));
        ui->musicList->setItem(RowCont,2,new QTableWidgetItem(list.at(i)->author));
        ui->musicList->setItem(RowCont,3,new QTableWidgetItem(list.at(i)->album));
        ui->musicList->setItem(RowCont,4,new QTableWidgetItem(list.at(i)->time));
    }
}

void searchOnline::on_musicList_doubleClicked(const QModelIndex &index)
{
    player::p->addOlMusic(list.at(index.row())->id,list.at(index.row())->title,list.at(index.row())->author,list.at(index.row())->url,list.at(index.row())->lyricsUrl,list.at(index.row())->time,list.at(index.row())->album);
    player::p->setIndex(player::p->musicList.length() - 1);//新增的索引
}

void searchOnline::on_musicList_customContextMenuRequested(const QPoint &pos)
{
    QTableWidgetItem* curItem = ui->musicList->itemAt( pos );
    if( curItem == NULL )
        return;

    QMenu *popMenu = new QMenu( this );
    popMenu->setStyleSheet("QMenu{background-color : #ffffff;color:#333333}QMenu::item:selected{background-color:#E2E2E2}");
    //popMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    QAction *addSeed = new QAction(tr("添加至播放列表"), this);

    QAction *cloudSeed = new QAction(tr("添加至云上歌单"), this);
    QAction *downSeed = new QAction(tr("下载歌曲"), this);
    selectedIndex =  ui->musicList->row(curItem);
    popMenu->addAction( addSeed );
    popMenu->addAction( cloudSeed );
    popMenu->addAction( downSeed );

    connect(addSeed,SIGNAL(triggered()),this,SLOT(addToList()));
    connect(cloudSeed,SIGNAL(triggered()),this,SLOT(addToCloud()));
    connect(downSeed,SIGNAL(triggered()),this,SLOT(downMusic()));
    popMenu->exec( QCursor::pos() );
}

void searchOnline::addToList(){
    player::p->addOlMusic(list.at(selectedIndex)->id,list.at(selectedIndex)->title,list.at(selectedIndex)->author,list.at(selectedIndex)->url,list.at(selectedIndex)->lyricsUrl,list.at(selectedIndex)->time,list.at(selectedIndex)->album);
    success *s = new success;
    s->set("成功添加至播放列表");
    s->show();
}

void searchOnline::setCloud(cloudList *s){
    this->cloud_page = s;
}
void searchOnline::setDown(downloadPage *s){
    this->download_page = s;
}
void searchOnline::addToCloud(){
    service *s = new service;
    connect( s, SIGNAL(addCloudSuccess()),this,SLOT(addCloudSuccess()));
    s->addCloud(list.at(selectedIndex)->id);
}


void searchOnline::addCloudSuccess(){
    cloud_page->load();
    success *s = new success;
    s->set("成功添加至云上歌单");
    s->show();
}


void searchOnline::downMusic(){
    downFile *d1 = new downFile;
    connect(d1, SIGNAL(success(QString,int)), this, SLOT(downSuccess(QString,int)));
    d1->down(list.at(selectedIndex)->url,list.at(selectedIndex)->id,1);
    downFile *d2 = new downFile;
    d2->down(list.at(selectedIndex)->lyricsUrl,list.at(selectedIndex)->id,2);
}

void searchOnline::downSuccess(QString id,int type){
    if(type == 1){
        QFile file("download.dat");
        file.open(QIODevice::Append);
        for(int i=0;i<list.length();i++){
            if(list.at(i)->id == id){
                QString str = list.at(i)->id + "-" + list.at(i)->title + "-" + list.at(i)->author + "-" + list.at(i)->url + "-" + list.at(i)->lyricsUrl + "-" + list.at(i)->time + "-" + list.at(i)->album + "-" + QDate::currentDate().toString("yyyy-MM-dd").replace("-",":") + "&";
                fileproce *fp = new fileproce;
                fp->copy(QString("cache/%1.mp3").arg(id),QString("download/%1.mp3").arg(list.at(i)->title + "-" + list.at(i)->author));
                file.write(str.toUtf8());
            }
        }
        file.close();
        success *s = new success;
        s->set("下载成功");
        s->show();
        download_page->load();
    }
}
