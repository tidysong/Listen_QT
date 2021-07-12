#ifndef LISTSINGLE_H
#define LISTSINGLE_H

#include <QWidget>
#include <qDebug>
namespace Ui {
class listSingle;
}

class listSingle : public QWidget
{
    Q_OBJECT

public:
    explicit listSingle(QWidget *parent = 0);
    void set(int i);
    ~listSingle();

private:
    Ui::listSingle *ui;
};

#endif // LISTSINGLE_H
