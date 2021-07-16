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
}
void searchOnline::searchSuccess(QList<searchInfo*> list){
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
