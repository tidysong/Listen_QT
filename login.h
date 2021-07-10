#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_close_clicked();

private:
    Ui::login *ui;
    bool is_Press;
    QPoint m_point;
    void initUI();
    void mousePressEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseMoveEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseReleaseEvent(QMouseEvent *event);//进行鼠界面的拖动
};

#endif // LOGIN_H
