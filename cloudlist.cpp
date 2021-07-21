#include "cloudlist.h"
#include "ui_cloudlist.h"

cloudList::cloudList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cloudList)
{
    ui->setupUi(this);
    initUI();
}

cloudList::~cloudList()
{
    delete ui;
}


void cloudList::initUI(){
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

void cloudList::on_searchText_textChanged(const QString &arg1)
{
    //对搜索框尾部的按钮处理
    if(arg1.length() > 0){
        QIcon myicon;
        myicon.addFile(tr(":/pic/close.png"));
        ui->searchIcon->setIcon(myicon);
        ui->searchIcon->setCursor(Qt::PointingHandCursor);//手型
    }else if(arg1.length() == 0){
        QIcon myicon;
        myicon.addFile(tr(":/pic/search.png"));
        ui->searchIcon->setIcon(myicon);
        ui->searchIcon->setCursor(Qt::ArrowCursor);//箭型
    }
    if(arg1.isEmpty()){
        showPointList(allList);
    }else{
        //非空 开始匹配
        QList<searchInfo*> tempList;
        for(int i=0;i<allList.length();i++){
            if(allList.at(i)->title.contains(arg1) != 0){
                tempList.append(allList.at(i));
            }
        }
        showList = tempList;
        showPointList(showList);
    }
}

void cloudList::on_searchIcon_clicked()
{
    if(ui->searchText->text().length() != 0){
        ui->searchText->setText("");
    }
}


void cloudList::load(){
    service *l = new service;

    connect(l, SIGNAL(cloudSuccess(QList<searchInfo*>)), this, SLOT(cloudSuccess(QList<searchInfo*>)));
    l->cloud();
}


void cloudList::cloudSuccess(QList<searchInfo*> list){
    this->allList = list;
    this->showList = list;
    for(int row = ui->musicList->rowCount() - 1;row >= 0; row--)
    {
        ui->musicList->removeRow(row);
    }
    ui->musicList->clearContents();
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
void cloudList::showPointList(QList<searchInfo*> list){
    for(int row = ui->musicList->rowCount() - 1;row >= 0; row--)
    {
        ui->musicList->removeRow(row);
    }//先删除原表格
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
    this->showList = list;
}
void cloudList::on_musicList_doubleClicked(const QModelIndex &index)
{
    player::p->addOlMusic(showList.at(index.row())->id,showList.at(index.row())->title,showList.at(index.row())->author,showList.at(index.row())->url,showList.at(index.row())->lyricsUrl,showList.at(index.row())->time,showList.at(index.row())->album);
    player::p->setIndex(player::p->musicList.length() - 1);//新增的索引
}



void cloudList::on_musicList_customContextMenuRequested(const QPoint &pos)
{
    QTableWidgetItem* curItem = ui->musicList->itemAt( pos );
    if( curItem == NULL )
        return;

    QMenu *popMenu = new QMenu( this );
    popMenu->setStyleSheet("QMenu{background-color : #ffffff;color:#333333}QMenu::item:selected{background-color:#E2E2E2}");
    //popMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    QAction *deleteSeed = new QAction(tr("从歌单移除"), this);

    QAction *addSeed = new QAction(tr("添加至播放列表"), this);
    QAction *downSeed = new QAction(tr("下载歌曲"), this);
    selectedIndex =  ui->musicList->row(curItem);
    popMenu->addAction( deleteSeed );
    popMenu->addAction( addSeed );
    popMenu->addAction( downSeed );

    connect(deleteSeed,SIGNAL(triggered()),this,SLOT(deleteFromList()));

    connect(downSeed,SIGNAL(triggered()),this,SLOT(downMusic()));
    connect(addSeed,SIGNAL(triggered()),this,SLOT(addToList()));
    popMenu->exec( QCursor::pos() );
}


void cloudList::deleteFromList(){
    service *s = new service;
    connect(s, SIGNAL(deleteCloudSuccess()),this,SLOT(deleteCloudSuccess()));
    s->deleteCloud(showList.at(selectedIndex)->InfoId);
}

void cloudList::addToList(){
    player::p->addOlMusic(showList.at(selectedIndex)->id,showList.at(selectedIndex)->title,showList.at(selectedIndex)->author,showList.at(selectedIndex)->url,showList.at(selectedIndex)->lyricsUrl,showList.at(selectedIndex)->time,showList.at(selectedIndex)->album);
    success *s = new success;
    s->set("成功添加至播放列表");
    s->show();
}
void cloudList::deleteCloudSuccess(){
    if(ui->searchText->text().isEmpty()){
        //如果是空
        showList.removeAt(selectedIndex);
        allList.removeAt(selectedIndex);
        showPointList(showList);
    }else{
        for(int i=0;i<allList.length();i++){
            if( allList.at(i)->InfoId == showList.at(selectedIndex)->InfoId){
                allList.removeAt(i);
                break;
            }
        }
        showList.removeAt(selectedIndex);
        showPointList(showList);
    }
    success *s = new success;
    s->set("成功从云歌单中移除");
    s->show();
}

void cloudList::clear(){
    for(int row = ui->musicList->rowCount() - 1;row >= 0; row--)
    {
        ui->musicList->removeRow(row);
    }
    showList.clear();
    allList.clear();

}


void cloudList::downMusic(){
    downFile *d1 = new downFile;
    connect(d1, SIGNAL(success(QString,int)), this, SLOT(downSuccess(QString,int)));
    d1->down(showList.at(selectedIndex)->url,showList.at(selectedIndex)->id,1);
    downFile *d2 = new downFile;
    d2->down(showList.at(selectedIndex)->lyricsUrl,showList.at(selectedIndex)->id,2);
}

void cloudList::setDown(downloadPage *s){
    this->download_page = s;
}
void cloudList::downSuccess(QString id,int type){
    if(type == 1){
        QFile file("download.dat");
        file.open(QIODevice::Append);
        for(int i=0;i<allList.length();i++){
            if(allList.at(i)->id == id){
                QString str = allList.at(i)->id + "-" + allList.at(i)->title + "-" + allList.at(i)->author + "-" + allList.at(i)->url + "-" + allList.at(i)->lyricsUrl + "-" + allList.at(i)->time + "-" + allList.at(i)->album + "-" + QDate::currentDate().toString().replace("-",":") + "&";
                file.write(str.toUtf8());

                fileproce *fp = new fileproce;
                fp->copy(QString("cache/%1.mp3").arg(id),QString("download/%1.mp3").arg(allList.at(i)->title + "-" + allList.at(i)->author));
                break;
            }
        }
        file.close();
        success *s = new success;
        s->set("下载成功");
        s->show();

        download_page->load();
    }
}
