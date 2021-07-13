#ifndef LYRICSPAGE_H
#define LYRICSPAGE_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QIODevice>
#include <QScrollBar>
#include <QColor>
#include <QListWidgetItem>
#include <QTime>
#include <QFont>
#include <readlyrics.h>
#include <player.h>
namespace Ui {
class lyricsPage;
}

class lyricsPage : public QWidget
{
    Q_OBJECT

public:
    explicit lyricsPage(QWidget *parent = 0);
    ~lyricsPage();
    void volCheck(int, int);

signals:
    void closePage();
    void showList();
private slots:
    void on_close_clicked();

    void on_closePage_clicked();

    void on_showList_clicked();
    void PositionChanged(qint64 postion);
    void DurationChanged(qint64 postion);

    void on_listWidget_doubleClicked(const QModelIndex &index);
    void stateChange(QMediaPlayer::State newState);
    void on_play_clicked();

    void on_horizontalSlider_sliderMoved(int position);


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_verticalSlider_valueChanged(int value);
    void volumeChange(int);
    void on_horizontalSlider_sliderReleased();

private:
    Ui::lyricsPage *ui;
    //QList<QPushButton*> labelList;
    QList<QListWidgetItem *>labelList;
    readLyrics *r;
    int lastIndex = 0;
    int line = 0;
    int prePosition;
    QFont *normal;
    QColor *normalcolor;
    QFont *now;
    QColor *nowcolor;
    QString formatTime(qint64 ms);
    bool isPlay = false;
    bool VolShow = false;
    bool is_Press;
    QPoint m_point;
    void showVol();
    void hideVol();
};

#endif // LYRICSPAGE_H
