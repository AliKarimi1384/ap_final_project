#include "difficulty.h"
#include "ui_difficulty.h"

difficulty::difficulty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::difficulty)
{
    ui->setupUi(this);
}

difficulty::~difficulty()
{
    delete ui;
}
