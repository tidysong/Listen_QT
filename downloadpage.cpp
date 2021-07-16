#include "downloadpage.h"
#include "ui_downloadpage.h"

downloadPage::downloadPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::downloadPage)
{
    ui->setupUi(this);
    initUI();
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
    ui->musicList->setItem(RowCont,4,new QTableWidgetItem("2021-07-10"));

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
}

void downloadPage::on_searchIcon_clicked()
{
    if(ui->searchText->text().length() != 0){
        ui->searchText->setText("");
    }
}
