#ifndef FIRST_PAGE_H
#define FIRST_PAGE_H

#include <QDialog>

namespace Ui {
class first_page;
}

class first_page : public QDialog
{
    Q_OBJECT

public:
    explicit first_page(QWidget *parent = nullptr);
    ~first_page();

private slots:
    void showLabel2();
    void showLabel3();
private:
    Ui::first_page *ui;
};

#endif // FIRST_PAGE_H
