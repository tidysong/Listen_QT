#ifndef LOCALMUSIC_H
#define LOCALMUSIC_H

#include <QWidget>
#include <qDebug>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QFileInfo>
#include <QMenu>
#include <QAction>
#include <QCursor>

#include <searchinfo.h>
#include <player.h>

#include <success.h>
#include <likepage.h>
namespace Ui {
class localMusic;
}

class localMusic : public QWidget
{
    Q_OBJECT

public:
    explicit localMusic(QWidget *parent = 0);
    ~localMusic();
    void load();
    void setLike(likePage *l);
private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();

    void on_musicList_doubleClicked(const QModelIndex &index);

    void on_musicList_customContextMenuRequested(const QPoint &pos);

    void deleteFromList();
    void addToList();

    void on_playAll_clicked();
    void addToLike();
private:
    Ui::localMusic *ui;
    void initUI();
    void showPointList(QList<searchInfo*> list);//展示指定list
    QList<searchInfo*> allList;
    QList<searchInfo*> showList;
    int selectedIndex;
    void save();
    likePage *like_page;
};

#endif // LOCALMUSIC_H
