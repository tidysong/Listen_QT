#ifndef LYRICSPAGE_H
#define LYRICSPAGE_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>

#include <lyrics.h>
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
private slots:
    void on_close_clicked();

    void on_closePage_clicked();

private:
    Ui::lyricsPage *ui;
};

#endif // LYRICSPAGE_H
