#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "first_page.h"
#include "pvp_mode.h"
//#include "Json_Parse.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    first_page fp;
    fp.setModal(true);
    fp.exec();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_play_pvp_clicked()
{
    //this function opens the pvp mode page
    pvp_mode *pvp = new pvp_mode(NULL);
    pvp->show();
}

void MainWindow::on_play_survival_clicked()
{
    //this function opens the survival mode page
}
