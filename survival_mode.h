#ifndef SURVIVAL_MODE_H
#define SURVIVAL_MODE_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class survival_mode;
}

class survival_mode : public QWidget
{
    Q_OBJECT

public:
    explicit survival_mode(QWidget *parent = nullptr);
    ~survival_mode();

private slots:
    void bring_start();
    void bring_question();
    void bring_true();
    void bring_false(bool flag);
    void bring_game_over();
    void start_timer();
    void stoptimer(int index);
    void stop_timer();
    void on_dif_e_clicked();

    void on_dif_m_clicked();

    void on_dif_h_clicked();

    void on_turner_btn_clicked();

    void on_q_ans1_clicked();

    void on_q_ans2_clicked();

    void on_q_ans3_clicked();

    void on_q_ans4_clicked();

    void on_t_wid_clicked();

    void on_f_wid_clicked();

private:
    Ui::survival_mode *ui;
    std::string difficulty;
    QTimer timer[15];
    std::string crt_ans;
    int counter=3;
    int score=0;
};

#endif // SURVIVAL_MODE_H
