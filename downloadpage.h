#ifndef DOWNLOADPAGE_H
#define DOWNLOADPAGE_H

#include <QWidget>
#include <searchInfo.h>
#include <QFile>
#include <QTextStream>
#include <QDesktopServices>
#include <QTextCodec>
#include <player.h>
namespace Ui {
class downloadPage;
}

class downloadPage : public QWidget
{
    Q_OBJECT

public:
    explicit downloadPage(QWidget *parent = 0);
    ~downloadPage();
    void load();
private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();

    void on_musicList_doubleClicked(const QModelIndex &index);


    void on_pushButton_clicked();

private:
    Ui::downloadPage *ui;
    void initUI();

    void showPointList(QList<searchInfo*> list);//展示指定list
    QList<searchInfo*> allList;
    QList<searchInfo*> showList;
    int selectedIndex;
};

#endif // DOWNLOADPAGE_H
