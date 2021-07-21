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
#include <searchonline.h>
#include <lyricspage.h>
#include <inifile.h>
#include <loading.h>
#include <downfile.h>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    static bool isLogin;
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
    void logSuccess();
    void on_searchText_returnPressed();


    void PositionChanged(qint64 postion);
    void DurationChanged(qint64 postion);
    void MediaChanged(const QMediaContent &content);
    void modeChange(QMediaPlaylist::PlaybackMode mode);
    void stateChange(QMediaPlayer::State newState);
    void on_play_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_modeChange_clicked();

    void on_pushButton_5_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderReleased();
    void search_succ();

    void downSucc();
    void loadSlot();
    void loadHideSlot();
private:
    Ui::MainWidget *ui;
    localMusic *localMusic_page;
    downloadPage *download_page;
    cloudList *cloud_page;
    likePage *like_page;
    playList *playlist_page;
    searchOnline *search_page;
    lyricsPage *lyrics_page;
    bool is_Press = false;
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
    void initConfig();
    QString formatTime(qint64 ms);

    void showVol();
    void hideVol();
    bool VolShow = false;
    int prePosition = 0;
    loading *load;
    void hideLoad();
    void showLoad();
};

#endif // MAINWIDGET_H
