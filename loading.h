#ifndef LOADING_H
#define LOADING_H

#include <QWidget>
#include <QMovie>
namespace Ui {
class loading;
}

class loading : public QWidget
{
    Q_OBJECT

public:
    explicit loading(QWidget *parent = 0);
    ~loading();

private:
    Ui::loading *ui;
};

#endif // LOADING_H
