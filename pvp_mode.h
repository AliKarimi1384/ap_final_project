#ifndef PVP_MODE_H
#define PVP_MODE_H

#include <QWidget>
#include <string>
#include <QTimer>

namespace Ui {
class pvp_mode;
}

class pvp_mode : public QWidget
{
    Q_OBJECT

public:
    explicit pvp_mode(QWidget *parent = nullptr);
    ~pvp_mode();


private slots:
    void on_pushButton_clicked();
    void bring_difficulty();
    void on_round_btn_clicked();
    void bring_cat();
    void bring_turn();
    void bring_question();
    void bring_countdown();
    void bring_true();
    void bring_false(bool flag);
    void start_timer();
    void stoptimer(int index);
    void stop_timer();
    void bring_r_finished();
    void bring_fpage(bool is_g);
    void bring_winner(std::string inp);
    void on_dif_e_clicked();

    void on_dif_m_clicked();

    void on_dif_h_clicked();

    void on_cat_1_clicked();

    void on_cat_2_clicked();

    void on_cat_3_clicked();

    void on_cat_4_clicked();

    void on_turner_btn_clicked();

    void on_q_ans1_clicked();

    void on_q_ans2_clicked();

    void on_q_ans3_clicked();

    void on_q_ans4_clicked();

    void on_t_wid_clicked();

    void on_f_wid_clicked();

    void on_rf_con_clicked();

private:
    Ui::pvp_mode *ui;
    std::string player_1;
    std::string player_2;
    std::string difficulty;
    std::string category;
    bool is_p1 = false;
    QTimer timer[30];
    std::string crt_ans;
    int category_i;
    int counter_1 = 1;
    int counter_2 = 0;
    int p1_score = 0;
    int p2_score = 0;
    int p1_score_t = 0;
    int p2_score_t = 0;
};


#endif // PVP_MODE_H
