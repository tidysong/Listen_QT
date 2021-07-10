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
    bool isListShow = false;
    bool isLyricsShow = false;
    QPoint m_point;
    void initUI();
    void mousePressEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseMoveEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseReleaseEvent(QMouseEvent *event);//进行鼠界面的拖动
    void showEvent(QShowEvent *event);//恢复最小化事件
};

#endif // MAINWIDGET_H
