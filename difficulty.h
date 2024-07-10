#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QWidget>

namespace Ui {
class difficulty;
}

class difficulty : public QWidget
{
    Q_OBJECT

public:
    explicit difficulty(QWidget *parent = nullptr);
    ~difficulty();

private:
    Ui::difficulty *ui;
};

#endif // DIFFICULTY_H
