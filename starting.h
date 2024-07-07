#ifndef STARTING_H
#define STARTING_H

#include <QMainWindow>

namespace Ui {
class starting;
}

class starting : public QMainWindow
{
    Q_OBJECT

public:
    explicit starting(QWidget *parent = nullptr);
    ~starting();

private:
    Ui::starting *ui;
};

#endif // STARTING_H
