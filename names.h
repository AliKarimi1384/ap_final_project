#ifndef NAMES_H
#define NAMES_H

#include <QWidget>

namespace Ui {
class names;
}

class names : public QWidget
{
    Q_OBJECT

public:
    explicit names(QWidget *parent = nullptr);
    ~names();

private slots:
    void on_pushButton_clicked();

private:
    Ui::names *ui;
};

#endif // NAMES_H
