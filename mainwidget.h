#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QPoint>
#include <QMouseEvent>
#include <qDebug>
#include <QPropertyAnimation>
#include <QRect>
#include <QTimer>
#include <QEasingCurve>
#include <QUrl>
#include <QMimeData>
#include <player.h>
#include <localmusic.h>
#include <downloadpage.h>
#include <cloudlist.h>
#include <likepage.h>
#include <login.h>
#include <playlist.h>
#include <lyricspage.h>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_close_clicked();

    void on_min_clicked();

    void on_menu_clicked(const QModelIndex &index);

    void on_avatar_clicked();

    void on_pushButton_4_clicked();

    void closeList();
    void showList();
    void closeLyrics();
    void on_pushButton_clicked();
private:
    Ui::MainWidget *ui;
    localMusic *localMusic_page;
    downloadPage *download_page;
    cloudList *cloud_page;
    likePage *like_page;
    playList *playlist_page;
    lyricsPage *lyrics_page;
    bool is_Press;
    QPoint m_point;
    bool isListShow = false;
    bool isLyricsShow = false;
    QEasingCurve curve;
    void initUI();
    void mousePressEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseMoveEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseReleaseEvent(QMouseEvent *event);//进行鼠界面的拖动
    void showEvent(QShowEvent *event);//恢复最小化事件
    void showListf();//展示音乐list
    void closeListf();//关闭音乐list
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // MAINWIDGET_H
