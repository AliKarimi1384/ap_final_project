#include "names.h"
#include "ui_names.h"

names::names(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::names)
{
//    setAutoFillBackground(true);
    ui->setupUi(this);
}

names::~names()
{
    delete ui;
}

void names::on_pushButton_clicked()
{
    this->setStyleSheet("background-color: rgb(192, 28, 40);");
}
