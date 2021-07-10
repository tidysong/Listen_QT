#ifndef DOWNLOADPAGE_H
#define DOWNLOADPAGE_H

#include <QWidget>

namespace Ui {
class downloadPage;
}

class downloadPage : public QWidget
{
    Q_OBJECT

public:
    explicit downloadPage(QWidget *parent = 0);
    ~downloadPage();

private slots:
    void on_searchText_textChanged(const QString &arg1);

    void on_searchIcon_clicked();

private:
    Ui::downloadPage *ui;
    void initUI();
};

#endif // DOWNLOADPAGE_H
