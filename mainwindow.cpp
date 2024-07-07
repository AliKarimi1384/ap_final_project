#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_play_pvp_clicked()
{
    //this function opens the pvp mode page
}

void MainWindow::on_play_survival_clicked()
{
    //this function opens the survival mode page
}
