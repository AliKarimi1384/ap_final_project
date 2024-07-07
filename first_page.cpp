#include "first_page.h"
#include "ui_first_page.h"
#include <QSoundEffect>
#include <thread>
#include <chrono>
#include <QTimer>
#include <string>

first_page::first_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::first_page)
{
    ui->setupUi(this);
    ui->label_2->hide();
    ui->label_3->hide();
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("starting.wav"));
    start->play();
    QTimer::singleShot(2000, this, &first_page::showLabel2);
    QTimer::singleShot(4000, this, &first_page::showLabel3);
    QTimer::singleShot(8000, this, &first_page::close);
}
void first_page::showLabel2() {
    ui->label_2->show();
}

void first_page::showLabel3() {
    ui->label_3->show();
}
first_page::~first_page()
{
    delete ui;
}
