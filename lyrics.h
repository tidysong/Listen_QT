#ifndef LYRICS_H
#define LYRICS_H

#include <QWidget>

namespace Ui {
class lyrics;
}

class lyrics : public QWidget
{
    Q_OBJECT

public:
    explicit lyrics(QWidget *parent = 0);
    ~lyrics();

private:
    Ui::lyrics *ui;
};

#endif // LYRICS_H
