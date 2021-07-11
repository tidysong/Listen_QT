#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
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
signals:
    void closeList();
private:
    Ui::playList *ui;
    void initUI();
};

#endif // PLAYLIST_H
