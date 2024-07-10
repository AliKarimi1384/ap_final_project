#include "survival_mode.h"
#include "ui_survival_mode.h"
#include <string>
#include <QString>
#include <iostream>
#include "quiz2.h"
#include "ctgs.h"
#include "randstr.h"
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <QSoundEffect>

survival_mode::survival_mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::survival_mode)

{
    ui->setupUi(this);
    ui->stacked->setGeometry(0,0,this->width(),this->height());
}
void survival_mode::bring_start(){
    randstr rd;
    QString temp = QString::fromStdString(rd.getstr(0));
    ui->hint_1->setText(temp);
    ui->stacked->setCurrentIndex(1);
}
void survival_mode::bring_question(){
    std::string temp = "Score: "+std::to_string(score);
    ui->m_score->setText(QString::fromStdString(temp));
    if(counter < 3){
        ui->heart3->hide();
    }
    if(counter < 2){
        ui->heart2->hide();
    }
    if(counter < 1){
        ui->heart1->hide();
    }
    Question question = fetchQuestion(10,difficulty);
    crt_ans = question.correct_answer;
    std::vector<int> nums = {0, 1, 2, 3};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));
    ui->q_box->setText(QString::fromStdString(question.question));
    ui->q_ans1->setText(QString::fromStdString(question.options[nums[0]]));
    ui->q_ans2->setText(QString::fromStdString(question.options[nums[1]]));
    ui->q_ans3->setText(QString::fromStdString(question.options[nums[2]]));
    ui->q_ans4->setText(QString::fromStdString(question.options[nums[3]]));
    ui->stacked->setCurrentIndex(5);
    start_timer();
}
void survival_mode::bring_true(){
    score++;
    randstr rd;
    ui->hint_2->setText(QString::fromStdString(rd.getstr(1)));
    ui->stacked->setCurrentIndex(6);
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/correct.wav"));
    start->play();
}
void survival_mode::bring_false(bool flag){
    counter--;
    if(flag){
        ui->f_disp->setText("Time's up!");
    } else{
        ui->f_disp->setText("Wrong answer");
    }
    randstr rd;
    ui->hint_3->setText(QString::fromStdString(rd.getstr(2)));
    ui->stacked->setCurrentIndex(7);
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/wrong.wav"));
    start->play();
}
void survival_mode::bring_game_over(){
    ui->go_l2->hide();
    ui->go_score->hide();
    ui->go_dif->hide();
    std::string temp1 = "Your score: "+std::to_string(score);
    std::string temp2 = "Difficulty: "+difficulty;
    ui->go_score->setText(QString::fromStdString(temp1));
    ui->go_dif->setText(QString::fromStdString(temp2));
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/game_over.wav"));
    start->play();
    QTimer::singleShot(1000, this, [this]() {
        ui->go_l2->show();
    } );
    QTimer::singleShot(2000, this, [this]() {
        ui->go_score->show();
    } );
    QTimer::singleShot(3000, this, [this]() {
        ui->go_dif->show();
    } );
    ui->stacked->setCurrentIndex(8);
}
void survival_mode::start_timer(){
    ui->timesh->setValue(0);
    connect(&timer[0], &QTimer::timeout, this, [this]() {
            //when user did'nt answer->
            bring_false(true);
            stoptimer(0);
        });
    timer[0].start(15000);
    for(int i=1;i<15;i++){
        connect(&timer[i], &QTimer::timeout, this, [this,i]() {
                this->ui->timesh->setValue(i);
                stoptimer(i);
            });
        timer[i].start(i*1000);
    }
}
void survival_mode::stoptimer(int index){
    timer[index].stop();
}
void survival_mode::stop_timer(){
    for(int i=0;i<15;i++){
        stoptimer(i);
    }
}
survival_mode::~survival_mode()
{
    delete ui;
}

void survival_mode::on_dif_e_clicked()
{
    difficulty = ui->dif_e->text().toStdString();
    bring_start();
}

void survival_mode::on_dif_m_clicked()
{
    difficulty = ui->dif_m->text().toStdString();
    bring_start();
}

void survival_mode::on_dif_h_clicked()
{
    difficulty = ui->dif_h->text().toStdString();
    bring_start();
}

void survival_mode::on_turner_btn_clicked()
{
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/wait.wav"));
    start->play();
    ui->stacked->setCurrentIndex(2);
    QTimer::singleShot(1000, this, [this]() {
        ui->stacked->setCurrentIndex(3);
        QSoundEffect *start = new QSoundEffect();
        start->setSource(QUrl::fromLocalFile("fx/wait.wav"));
        start->play();
    } );
    QTimer::singleShot(2000, this, [this]() {
        ui->stacked->setCurrentIndex(4);
        QSoundEffect *start = new QSoundEffect();
        start->setSource(QUrl::fromLocalFile("fx/wait.wav"));
        start->play();
    } );
    QTimer::singleShot(3000, this, [this]() {
        QSoundEffect *start = new QSoundEffect();
        start->setSource(QUrl::fromLocalFile("fx/start.wav"));
        start->play();
        bring_question();
    } );
}

void survival_mode::on_q_ans1_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans1->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void survival_mode::on_q_ans2_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans1->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void survival_mode::on_q_ans3_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans1->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void survival_mode::on_q_ans4_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans1->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void survival_mode::on_t_wid_clicked()
{
    bring_question();
}

void survival_mode::on_f_wid_clicked()
{
    if(counter == 0){
        bring_game_over();
    } else{
        bring_question();
    }
}
