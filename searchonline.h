#ifndef SEARCHONLINE_H
#define SEARCHONLINE_H

#include <QWidget>
#include <QMenu>
#include <QTableWidgetItem>
#include <QAction>
#include <QDate>
#include <service.h>
#include <searchinfo.h>
#include <player.h>
#include <success.h>
#include <cloudlist.h>
#include <fileproce.h>
#include <downloadpage.h>
namespace Ui {
class searchOnline;
}

class searchOnline : public QWidget
{
    Q_OBJECT
signals:
    void succ();
public:
    explicit searchOnline(QWidget *parent = 0);
    ~searchOnline();
    void set(QString title);
    void setCloud(cloudList *);
    void setDown(downloadPage *s);
private slots:
    void searchSuccess(QList<searchInfo*>);
    void on_musicList_doubleClicked(const QModelIndex &index);

    void on_musicList_customContextMenuRequested(const QPoint &pos);
    void addToList();
    void addToCloud();
    void addCloudSuccess();
    void downMusic();
    void downSuccess(QString,int);
private:
    Ui::searchOnline *ui;
    void initUI();
    QList<searchInfo*> list;
    int selectedIndex;
    cloudList *cloud_page;
    downloadPage *download_page;
};

#endif // SEARCHONLINE_H
