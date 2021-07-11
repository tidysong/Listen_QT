#ifndef LOCALMUSIC_H
#define LOCALMUSIC_H

#include <QWidget>
#include <qDebug>
namespace Ui {
class localMusic;
}

class localMusic : public QWidget
{
    Q_OBJECT

public:
    explicit localMusic(QWidget *parent = 0);
    ~localMusic();

private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();

private:
    Ui::localMusic *ui;
    void initUI();
};

#endif // LOCALMUSIC_H
