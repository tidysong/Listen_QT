#ifndef CLOUDLIST_H
#define CLOUDLIST_H

#include <QWidget>
#include <QMenu>
#include <QTableWidgetItem>
#include <QAction>
#include <QFile>
#include <service.h>
#include <player.h>
#include <success.h>
#include <fileproce.h>

#include <downloadpage.h>
namespace Ui {
class cloudList;
}

class cloudList : public QWidget
{
    Q_OBJECT

public:
    explicit cloudList(QWidget *parent = 0);
    ~cloudList();
    void load();
    void clear();
    void setDown(downloadPage *s);
private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();
    void cloudSuccess(QList<searchInfo*> list);
    void on_musicList_doubleClicked(const QModelIndex &index);


    void on_musicList_customContextMenuRequested(const QPoint &pos);
    void deleteFromList();
    void deleteCloudSuccess();
    void addToList();
    void downMusic();
    void downSuccess(QString id,int type);
private:
    Ui::cloudList *ui;
    void initUI();
    void showPointList(QList<searchInfo*> list);//展示指定list
    QList<searchInfo*> allList;
    QList<searchInfo*> showList;
    int selectedIndex;
    downloadPage *download_page;
};

#endif // CLOUDLIST_H
