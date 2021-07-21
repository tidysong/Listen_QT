#include "localmusic.h"
#include "ui_localmusic.h"

localMusic::localMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::localMusic)
{
    ui->setupUi(this);
    initUI();
    load();
    //ui->musicList->setShowGrid(false);
}

localMusic::~localMusic()
{
    delete ui;
}


void localMusic::initUI(){
    ui->musicList->setColumnWidth(0,60);
    ui->musicList->setColumnWidth(1,300);
    ui->musicList->setColumnWidth(2,150);
    ui->musicList->setColumnWidth(3,100);
    ui->musicList->setColumnWidth(4,150);
    ui->musicList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->musicList->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color:white; border:none; border-right:1px solid #E5E5E5;height:25px;border-top-right-radius:10px;border-top-left-radius:10px;}");
    ui->musicList->horizontalHeader()->setHighlightSections(false);

    ui->musicList->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    ui->musicList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->musicList->verticalHeader()->setVisible(false); //隐藏列表头
    ui->musicList->setSelectionMode(QAbstractItemView::SingleSelection);//只选一行
    ui->musicList->horizontalHeader()->setVisible(true);
    //int RowCont;
    //RowCont=ui->musicList->rowCount();
    //ui->musicList->insertRow(RowCont);
    //ui->musicList->setItem(RowCont,0,new QTableWidgetItem("01"));
    //ui->musicList->setItem(RowCont,1,new QTableWidgetItem("浪费"));
    //ui->musicList->setItem(RowCont,2,new QTableWidgetItem("林宥嘉"));
    //ui->musicList->setItem(RowCont,3,new QTableWidgetItem("04:30"));
    //ui->musicList->setItem(RowCont,4,new QTableWidgetItem("2021-07-10 14:39"));
    //ui->musicList->horizontalHeader()->setStyleSheet("QHeaderView::section{border:0px;}");
}

void localMusic::on_searchText_textChanged(const QString &arg1)
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

void localMusic::on_searchIcon_clicked()
{
    if(ui->searchText->text().length() != 0){
        ui->searchText->setText("");
    }
}


void localMusic::load(){
    QFile file("local.dat");
    QString cont;
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    stream.setCodec( QTextCodec::codecForName("UTF8") );
    cont = stream.readAll();
    //qDebug() << cont;
    QStringList pathList = cont.split("&");
    allList.clear();
    for(int i=0;i < pathList.length() - 1;i++){
        QFileInfo fileInfo(pathList.at(i));
        playInfo *temp = player::p->getInf(pathList.at(i));
        //qDebug() << temp->name << "&" << temp->duration;
        searchInfo *info = new searchInfo(temp->name,temp->filePath,temp->Author,temp->duration,fileInfo.created().toString("yyyy-MM-dd"));
        allList.append(info);
    }
    showPointList(allList);
    file.close();
    //qDebug() << "?";
}


void localMusic::showPointList(QList<searchInfo*> list){
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
        ui->musicList->setItem(RowCont,3,new QTableWidgetItem(list.at(i)->time));
        ui->musicList->setItem(RowCont,4,new QTableWidgetItem(list.at(i)->createTime));
    }
    this->showList = list;
}

void localMusic::on_musicList_doubleClicked(const QModelIndex &index)
{
    player::p->addMusic( showList.at(index.row())->url );
    player::p->setIndex(player::p->musicList.length() - 1);//新增的索引
    player::p->play();
}



void localMusic::on_musicList_customContextMenuRequested(const QPoint &pos)
{
    QTableWidgetItem* curItem = ui->musicList->itemAt( pos );
    if( curItem == NULL )
        return;

    QMenu *popMenu = new QMenu( this );
    popMenu->setStyleSheet("QMenu{background-color : #ffffff;color:#333333}QMenu::item:selected{background-color:#E2E2E2}");
    //popMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    QAction *deleteSeed = new QAction(tr("从本地音乐中移除"), this);

    QAction *addSeed = new QAction(tr("添加至播放列表"), this);

    QAction *likeSeed = new QAction(tr("添加至收藏"), this);
    selectedIndex =  ui->musicList->row(curItem);
    popMenu->addAction( deleteSeed );
    popMenu->addAction( addSeed );
    popMenu->addAction( likeSeed );

    connect(deleteSeed,SIGNAL(triggered()),this,SLOT(deleteFromList()));

    connect(addSeed,SIGNAL(triggered()),this,SLOT(addToList()));
    connect(likeSeed,SIGNAL(triggered()),this,SLOT(addToLike()));
    popMenu->exec( QCursor::pos() );
}

void localMusic::addToList(){
    player::p->addMusic( showList.at(selectedIndex)->url );
    success *s = new success;
    s->set("成功添加至播放列表");
    s->show();
}

void localMusic::deleteFromList(){
    if(ui->searchText->text().isEmpty()){
        //showList = allList
        allList.removeAt(selectedIndex);
    }
    showPointList(allList);
    save();
    success *s = new success;
    s->set("成功从本地音乐中移除");
    s->show();
}

void localMusic::save(){
    QString str;
    for(int i=0;i<allList.length();i++){
        str += allList.at(i)->url + "&";
    }
    QFile file("local.dat");
    file.open(QIODevice::WriteOnly);
    file.write(str.toUtf8());

    file.close();
}


void localMusic::on_playAll_clicked()
{
    int index = player::p->musicList.length();
    if(showList.length() != 0){
        for(int i = 0;i < showList.length(); i++){
            player::p->addMusic( showList.at(i)->url );
        }
    }
    player::p->setIndex(index);
    player::p->play();
    success *s = new success;
    s->set("成功添加至播放列表");
    s->show();
}
void localMusic::setLike(likePage *l){
    like_page = l;
}

void localMusic::addToLike(){
    QFile file("like.dat");
    file.open(QIODevice::Append);
    file.write( QString(showList.at(selectedIndex)->url + "&").toUtf8() );
    file.close();
    success *s = new success;
    s->set("成功添加至收藏");
    s->show();
    like_page->load();
}
