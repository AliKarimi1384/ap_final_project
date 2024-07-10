#include "pvp_mode.h"
#include "ui_pvp_mode.h"
#include <string>
#include <QString>
#include <iostream>
#include "quiz.h"
#include "ctgs.h"
#include "randstr.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <QSoundEffect>
pvp_mode::pvp_mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pvp_mode)
{
    ui->setupUi(this);
    srand(time(0));
    ui->stacked->setGeometry(0,0,this->width(),this->height());
}
void pvp_mode::bring_difficulty(){
    ui->stacked->setCurrentIndex(2);
}
void pvp_mode::bring_cat(){
    ui->stacked->setCurrentIndex(3);
    ctgs ct;
    std::string temp_c[4];
    for(int i=0;i<4;i++){
        temp_c[i] = ct.get_rand();
    }
    ui->cat_1->setText(QString::fromStdString(temp_c[0]));
    ui->cat_2->setText(QString::fromStdString(temp_c[1]));
    ui->cat_3->setText(QString::fromStdString(temp_c[2]));
    ui->cat_4->setText(QString::fromStdString(temp_c[3]));
}
void pvp_mode::bring_question(){
    ctgs ct;
    category_i = ct.get_index(category)+9;
    Question question = fetchQuestion(10,difficulty,category_i);
    crt_ans = question.correct_answer;
    int temp1 = p2_score;
    int temp2 = p2_score_t;
    if(is_p1){
        temp1 = p1_score;
        temp2 = p1_score_t;
    }
    std::vector<int> nums = {0, 1, 2, 3};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));
    std::string temp3 = "Main score: "+to_string(temp1);
    std::string temp4 = "Round score: "+to_string(temp2);
    ui->m_score->setText(QString::fromStdString(temp3));
    ui->r_score->setText(QString::fromStdString(temp4));
    ui->q_box->setText(QString::fromStdString(question.question));
    ui->q_ans1->setText(QString::fromStdString(question.options[nums[0]]));
    ui->q_ans2->setText(QString::fromStdString(question.options[nums[1]]));
    ui->q_ans3->setText(QString::fromStdString(question.options[nums[2]]));
    ui->q_ans4->setText(QString::fromStdString(question.options[nums[3]]));
    start_timer();
    ui->stacked->setCurrentIndex(8);
}
void pvp_mode::start_timer(){
    ui->timesh->setValue(0);
    connect(&timer[0], &QTimer::timeout, this, [this]() {
            //when user did'nt answer->
            bring_false(true);
            stoptimer(0);
        });
    timer[0].start(30000);
    for(int i=1;i<30;i++){
        connect(&timer[i], &QTimer::timeout, this, [this,i]() {
                this->ui->timesh->setValue(i);
                stoptimer(i);
            });
        timer[i].start(i*1000);
    }
}
void pvp_mode::stoptimer(int index){
    timer[index].stop();
}
void pvp_mode::stop_timer(){
    for(int i=0;i<30;i++){
        stoptimer(i);
    }
}
void pvp_mode::bring_countdown(){
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/wait.wav"));
    start->play();
    ui->stacked->setCurrentIndex(5);
    QTimer::singleShot(1000, this, [this]() {
        ui->stacked->setCurrentIndex(6);
        QSoundEffect *start = new QSoundEffect();
        start->setSource(QUrl::fromLocalFile("fx/wait.wav"));
        start->play();
    } );
    QTimer::singleShot(2000, this, [this]() {
        ui->stacked->setCurrentIndex(7);
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
void pvp_mode::bring_turn(){
    counter_2 = 0;
    std::string temp;
    if(is_p1){
        temp = player_1;
    } else{
        temp = player_2;
    }
    temp = "It's " + temp + "'s turn";
    ui->turn->setText(QString::fromStdString(temp));
    randstr rd;
    ui->hint_1->setText(QString::fromStdString(rd.getstr(0)));
    ui->stacked->setCurrentIndex(4);
    is_p1 = !is_p1;
}
void pvp_mode::bring_true(){
    if(is_p1){
        p1_score_t++;
    } else{
        p2_score_t++;
    }
    counter_2++;
    randstr rd;
    ui->hint_2->setText(QString::fromStdString(rd.getstr(1)));
    ui->stacked->setCurrentIndex(9);
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/correct.wav"));
    start->play();
}
void pvp_mode::bring_false(bool flag){
    if(flag){
        ui->f_disp->setText("Time's up!");
    } else{
        ui->f_disp->setText("Wrong answer");
    }
    counter_2++;
    randstr rd;
    ui->hint_3->setText(QString::fromStdString(rd.getstr(2)));
    ui->stacked->setCurrentIndex(10);
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/wrong.wav"));
    start->play();
}
void pvp_mode::bring_r_finished(){
    std::string temp1 = "Round "+std::to_string(counter_1)+" finished";
    ui->rf_title->setText(QString::fromStdString(temp1));
    temp1 = std::to_string(p1_score_t) + " : " + std::to_string(p2_score_t);
    ui->rf_rscore->setText(QString::fromStdString(temp1));
    if(p1_score_t > p2_score_t){
        temp1 = "The winner of this round is "+player_1;
        p1_score++;
    }else if(p1_score_t < p2_score_t){
        temp1 = "The winner of this round is "+player_2;
        p2_score++;
    } else{
        temp1 = "The winner of this round is no one";
    }
    ui->rf_win->setText(QString::fromStdString(temp1));
    ui->rf_p1->setText(QString::fromStdString(player_1));
    ui->rf_p2->setText(QString::fromStdString(player_2));
    ui->rf_ms1->display(p1_score);
    ui->rf_ms2->display(p2_score);
    counter_2 = 0;
    p1_score_t = 0;
    p2_score_t = 0;
    ui->stacked->setCurrentIndex(11);
}
void pvp_mode::bring_fpage(bool is_g){
    counter_1++;
    if(is_g){
        ui->gdround->show();
    }
    std::string temp = "Round "+std::to_string(counter_1);
    ui->round_counter->setText(QString::fromStdString(temp));
    ui->stacked->setCurrentIndex(1);
}
void pvp_mode::bring_winner(std::string inp){
    QSoundEffect *start = new QSoundEffect();
    start->setSource(QUrl::fromLocalFile("fx/winning.wav"));
    start->play();
    ui->winner_e->hide();
    ui->winner_b->hide();
    ui->stacked->setCurrentIndex(12);
    QTimer::singleShot(500, this, [this]() {
        ui->winner_m->setText(QString::fromStdString("winner"));
    } );
    QTimer::singleShot(1000, this, [this]() {
        ui->winner_m->setText(QString::fromStdString("chicken"));
    } );
    QTimer::singleShot(1500, this, [this]() {
        ui->winner_m->setText(QString::fromStdString("dinner"));
    } );
    QTimer::singleShot(2500, this, [this,inp]() {
        ui->winner_m->setText(QString::fromStdString(inp));
    } );
    QTimer::singleShot(3500, this, [this]() {
        ui->winner_e->show();
        ui->winner_b->show();
    } );
}
pvp_mode::~pvp_mode()
{
    delete ui;
}

void pvp_mode::on_pushButton_clicked()
{
    pvp_mode::player_1 = ui->player_1_name->toPlainText().toStdString();
    pvp_mode::player_2 = ui->player_2_name->toPlainText().toStdString();
    ui->stacked->setCurrentIndex(1);
    ui->gdround->hide();
}

void pvp_mode::on_round_btn_clicked()
{
    if(counter_1 < 5){
        bring_difficulty();
    } else{
        difficulty = "medium";
        ctgs ct;
        category = ct.get_rand();
        bring_turn();
    }
}

void pvp_mode::on_dif_e_clicked()
{
    difficulty = ui->dif_e->text().toStdString();
    bring_cat();
}

void pvp_mode::on_dif_m_clicked()
{
    difficulty = ui->dif_m->text().toStdString();
    bring_cat();
}

void pvp_mode::on_dif_h_clicked()
{
    difficulty = ui->dif_h->text().toStdString();
    bring_cat();
}


void pvp_mode::on_cat_1_clicked()
{
    category = ui->cat_1->text().toStdString();
    bring_turn();
}

void pvp_mode::on_cat_2_clicked()
{
    category = ui->cat_2->text().toStdString();
    bring_turn();
}

void pvp_mode::on_cat_3_clicked()
{
    category = ui->cat_3->text().toStdString();
    bring_turn();
}

void pvp_mode::on_cat_4_clicked()
{
    category = ui->cat_4->text().toStdString();
    bring_turn();
}

void pvp_mode::on_turner_btn_clicked()
{
    bring_countdown();
}

void pvp_mode::on_q_ans1_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans1->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void pvp_mode::on_q_ans2_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans2->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void pvp_mode::on_q_ans3_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans3->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void pvp_mode::on_q_ans4_clicked()
{
    stop_timer();
    std::string temp = ui->q_ans4->text().toStdString();
    if(temp == crt_ans){
        bring_true();
    } else{
        bring_false(false);
    }
}

void pvp_mode::on_t_wid_clicked()
{
    if(counter_2 < 5){
        bring_question();
    } else if(is_p1){
        bring_turn();
    } else{
        bring_r_finished();
    }
}

void pvp_mode::on_f_wid_clicked()
{
    if(counter_2 < 5){
        bring_question();
    } else if(is_p1){
        bring_turn();
    } else{
        bring_r_finished();
    }
}

void pvp_mode::on_rf_con_clicked()
{
    if(counter_1<4){
        //continue
        bring_fpage(false);
    } else if(p1_score > p2_score){
        //p1 won
        bring_winner(player_1);
    } else if(p1_score < p2_score){
        //p2 won
        bring_winner(player_2);
    } else{
        //golden round
        bring_fpage(true);
    }
}
