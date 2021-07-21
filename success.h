#ifndef SUCCESS_H
#define SUCCESS_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QTimer>
namespace Ui {
class success;
}

class success : public QWidget
{
    Q_OBJECT

public:
    explicit success(QWidget *parent = 0);
    ~success();
    void set(QString v);
private:
    Ui::success *ui;
};

#endif // SUCCESS_H
