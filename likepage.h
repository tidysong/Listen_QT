#ifndef LIKEPAGE_H
#define LIKEPAGE_H

#include <QWidget>

namespace Ui {
class likePage;
}

class likePage : public QWidget
{
    Q_OBJECT

public:
    explicit likePage(QWidget *parent = 0);
    ~likePage();

private:
    Ui::likePage *ui;
    void initUI();
};

#endif // LIKEPAGE_H
