#ifndef API_H
#define API_H
#include <string>
#include <nlohmann/json.hpp>

class api
{
public:
    api();
    static nlohmann::json fetchTriviaQuestions(const std::string& category, const std::string& difficulty, int amount);
private:
    static std::string httpGet(const std::string& url);
};

#endif // API_H
