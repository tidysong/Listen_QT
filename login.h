#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <service.h>
#include <mydialog.h>
#include <inifile.h>
#include <sigup.h>
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    void set(QString u, QString p);
signals:
    logSuccess();
    logFail();
private slots:
    void on_close_clicked();
    void sendClose();
    void on_loginButton_clicked();
    void LoginSuccess();
    void LoginFail();
    void on_sign_clicked();
    void signReturn();
    void sigupSuccess(QString id);
private:
    Ui::login *ui;
    bool is_Press;
    bool isAutoLogin = false;
    QPoint m_point;
    void initUI();
    void mousePressEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseMoveEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseReleaseEvent(QMouseEvent *event);//进行鼠界面的拖动
};

#endif // LOGIN_H
