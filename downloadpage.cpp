#include "downloadpage.h"
#include "ui_downloadpage.h"

downloadPage::downloadPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::downloadPage)
{
    ui->setupUi(this);
    initUI();
    load();
}

downloadPage::~downloadPage()
{
    delete ui;
}
void downloadPage::initUI(){
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

    //int RowCont;
    //RowCont=ui->musicList->rowCount();
    //ui->musicList->insertRow(RowCont);
    //ui->musicList->setItem(RowCont,0,new QTableWidgetItem("01"));
    //ui->musicList->setItem(RowCont,1,new QTableWidgetItem("浪费"));
    //ui->musicList->setItem(RowCont,2,new QTableWidgetItem("林宥嘉"));
    //ui->musicList->setItem(RowCont,3,new QTableWidgetItem("LIVE"));
    //ui->musicList->setItem(RowCont,4,new QTableWidgetItem("2021-07-10"));

}
void downloadPage::on_searchText_textChanged(const QString &arg1)
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

void downloadPage::on_searchIcon_clicked()
{
    if(ui->searchText->text().length() != 0){
        ui->searchText->setText("");
    }
}

void downloadPage::showPointList(QList<searchInfo*> list){
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
        ui->musicList->setItem(RowCont,4,new QTableWidgetItem(list.at(i)->createTime));
    }
    this->showList = list;
}

void downloadPage::load(){
    QFile file("download.dat");
    QString cont;
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    stream.setCodec( QTextCodec::codecForName("UTF8") );
    cont = stream.readAll();
    //qDebug() << cont;
    QStringList tList = cont.split("&");

    for(int i=0;i < tList.length() - 1;i++){
        QStringList uList = tList.at(i).split("-");
        searchInfo *s = new searchInfo(uList[0], uList[1], uList[3], uList[4], uList[2],uList[6],uList[5]);
        s->setCreateTime(uList[7].replace(":","-"));
        allList.append(s);
    }
    showPointList(allList);
}

void downloadPage::on_musicList_doubleClicked(const QModelIndex &index)
{
    player::p->addOlMusic(showList.at(index.row())->id,showList.at(index.row())->title,showList.at(index.row())->author,showList.at(index.row())->url,showList.at(index.row())->lyricsUrl,showList.at(index.row())->time,showList.at(index.row())->album);
    player::p->setIndex(player::p->musicList.length() - 1);//新增的索引
}



void downloadPage::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("download"));
}
