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
#include <readlyrics.h>
namespace Ui {
class lyricsPage;
}

class lyricsPage : public QWidget
{
    Q_OBJECT

public:
    explicit lyricsPage(QWidget *parent = 0);
    ~lyricsPage();

signals:
    void closePage();
    void showList();
private slots:
    void on_close_clicked();

    void on_closePage_clicked();

    void on_showList_clicked();

private:
    Ui::lyricsPage *ui;
    QList<QLabel*> labelList;
};

#endif // LYRICSPAGE_H
