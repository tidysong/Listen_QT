#ifndef CLOUDLIST_H
#define CLOUDLIST_H

#include <QWidget>

namespace Ui {
class cloudList;
}

class cloudList : public QWidget
{
    Q_OBJECT

public:
    explicit cloudList(QWidget *parent = 0);
    ~cloudList();

private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();

private:
    Ui::cloudList *ui;
    void initUI();
};

#endif // CLOUDLIST_H
