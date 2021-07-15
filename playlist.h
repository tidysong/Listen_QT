#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QMenu>
#include <QAction>
#include <player.h>
#include <listsingle.h>
namespace Ui {
class playList;
}

class playList : public QWidget
{
    Q_OBJECT

public:
    explicit playList(QWidget *parent = 0);
    ~playList();

private slots:
    void on_pushButton_4_clicked();
    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void listChange();
    void deleteMusicFromList();

signals:
    void closeList();
private:
    Ui::playList *ui;
    void initUI();
    int selectedIndex = 0;
};

#endif // PLAYLIST_H
