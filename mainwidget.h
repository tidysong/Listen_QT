#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QPoint>
#include <QMouseEvent>
#include <qDebug>
#include <QPropertyAnimation>
#include <QRect>
#include <QTimer>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_close_clicked();

    void on_min_clicked();

private:
    Ui::MainWidget *ui;
    bool is_Press;
    QPoint m_point;
    void initUI();
    void mousePressEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseMoveEvent(QMouseEvent *event);//进行鼠界面的拖动
    void mouseReleaseEvent(QMouseEvent *event);//进行鼠界面的拖动
    void showEvent(QShowEvent *event);//恢复最小化事件
};

#endif // MAINWIDGET_H
