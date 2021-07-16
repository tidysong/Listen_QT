#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
namespace Ui {
class MyDialog;
}

class MyDialog : public QWidget
{
    Q_OBJECT
signals:
    sendClose();
public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();
    void set(int,QString,int);

private slots:
    void on_ok_clicked();
    void update();

private:
    Ui::MyDialog *ui;
    int times = 0;
    int showTime = 0;
    int alertType = 0;
};

#endif // MYDIALOG_H
