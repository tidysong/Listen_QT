#ifndef LIKEPAGE_H
#define LIKEPAGE_H

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
namespace Ui {
class likePage;
}

class likePage : public QWidget
{
    Q_OBJECT

public:
    explicit likePage(QWidget *parent = 0);
    ~likePage();
    void load();
private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();

    void on_musicList_doubleClicked(const QModelIndex &index);

    void on_musicList_customContextMenuRequested(const QPoint &pos);

    void deleteFromList();
    void addToList();

    void on_playAll_clicked();
private:
    Ui::likePage *ui;
    void initUI();
    void showPointList(QList<searchInfo*> list);//展示指定list
    QList<searchInfo*> allList;
    QList<searchInfo*> showList;
    int selectedIndex;
    void save();

};

#endif // LIKEPAGE_H
