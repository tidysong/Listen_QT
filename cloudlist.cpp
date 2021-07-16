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
    int RowCont;
    RowCont=ui->musicList->rowCount();
    ui->musicList->insertRow(RowCont);
    ui->musicList->setItem(RowCont,0,new QTableWidgetItem("01"));
    ui->musicList->setItem(RowCont,1,new QTableWidgetItem("浪费"));
    ui->musicList->setItem(RowCont,2,new QTableWidgetItem("林宥嘉"));
    ui->musicList->setItem(RowCont,3,new QTableWidgetItem("LIVE"));
    ui->musicList->setItem(RowCont,4,new QTableWidgetItem("04:30"));
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
