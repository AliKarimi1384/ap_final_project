#ifndef QST_H
#define QST_H
#include <string>
struct Question {
    std::string question;
    std::string options[4];
    std::string correct_answer;
};

#endif // QST_H
