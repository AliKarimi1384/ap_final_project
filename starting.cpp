#include "starting.h"
#include "ui_starting.h"

starting::starting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::starting)
{
    ui->setupUi(this);
}

starting::~starting()
{
    delete ui;
}
