#ifndef LISTSINGLE_H
#define LISTSINGLE_H

#include <QWidget>
#include <qDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <player.h>
namespace Ui {
class listSingle;
}

class listSingle : public QWidget
{
    Q_OBJECT

public:
    explicit listSingle(QWidget *parent = 0);
    void set(QString, QString, int);
    ~listSingle();

private:
    Ui::listSingle *ui;
    int i;
    bool isPlay = false;
    void ShowLine();
    void HideLine();
    QString strScrollCation;
private slots:
    void stateChanged(QMediaPlayer::State newState);
    void IndexChanged(int index);
    void on_play_clicked();
    void scrollCaption();
};

#endif // LISTSINGLE_H
