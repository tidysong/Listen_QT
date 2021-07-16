#ifndef SIGUP_H
#define SIGUP_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
namespace Ui {
class sigUp;
}

class sigUp : public QWidget
{
    Q_OBJECT
signals:
    void signReturn();
public:
    explicit sigUp(QWidget *parent = 0);
    ~sigUp();
    void set(QString pwd);

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

    void on_password_textChanged(const QString &arg1);

private:
    Ui::sigUp *ui;
    QString password;
};

#endif // SIGUP_H
