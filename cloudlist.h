#ifndef CLOUDLIST_H
#define CLOUDLIST_H

#include <QWidget>
#include <service.h>
namespace Ui {
class cloudList;
}

class cloudList : public QWidget
{
    Q_OBJECT

public:
    explicit cloudList(QWidget *parent = 0);
    ~cloudList();
    void load();
private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();
    void cloudSuccess(QList<searchInfo*> list);
private:
    Ui::cloudList *ui;
    void initUI();
};

#endif // CLOUDLIST_H
