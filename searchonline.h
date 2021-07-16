#ifndef SEARCHONLINE_H
#define SEARCHONLINE_H

#include <QWidget>
#include <service.h>
#include <searchinfo.h>
namespace Ui {
class searchOnline;
}

class searchOnline : public QWidget
{
    Q_OBJECT

public:
    explicit searchOnline(QWidget *parent = 0);
    ~searchOnline();
    void set(QString title);
private slots:
    void searchSuccess(QList<searchInfo*>);
private:
    Ui::searchOnline *ui;
    void initUI();
};

#endif // SEARCHONLINE_H
