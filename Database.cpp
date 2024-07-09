#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

struct Question {
    std::string question;
    std::string options[4];
    std::string correct_answer;
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<Question> fetchQuestions(int amount, const std::string& difficulty, int category) {
    std::string readBuffer;
    CURL* curl;
    CURLcode res;
    std::vector<Question> questions;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://opentdb.com/api.php?amount=" + std::to_string(amount)
                        + "&difficulty=" + difficulty
                        + "&category=" + std::to_string(category);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return questions;
        }
    }
    curl_global_cleanup();

    Json::CharReaderBuilder reader;
    Json::Value jsonData;
    std::string errs;

    std::istringstream s(readBuffer);
    std::string errs;
    if (!Json::parseFromStream(reader, s, &jsonData, &errs)) {
        std::cerr << "Error parsing JSON: " << errs << std::endl;
        return questions;
    }

    for (const auto& result : jsonData["results"]) {
        Question question;
        question.question = result["question"].asString();
        question.options[0] = result["correct_answer"].asString();
        int i = 1;
        for (const auto& incorrect : result["incorrect_answers"]) {
            question.options[i++] = incorrect.asString();
        }
        question.correct_answer = result["correct_answer"].asString();
        questions.push_back(question);
    }

    return questions;
}

void saveQuestionsToCSV(const std::string& filename, const std::vector<Question>& questions) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    file << "question,option1,option2,option3,option4,correct_answer\n";
    for (const auto& q : questions) {
        file << "\"" << q.question << "\","
             << "\"" << q.options[0] << "\","
             << "\"" << q.options[1] << "\","
             << "\"" << q.options[2] << "\","
             << "\"" << q.options[3] << "\","
             << "\"" << q.correct_answer << "\"\n";
    }

    file.close();
}

int main() {
    std::vector<Question> questions = fetchQuestions(5, "medium", 18);

    saveQuestionsToCSV("questions.csv", questions);

    std::cout << "Questions saved to questions.csv" << std::endl;

    return 0;
}
