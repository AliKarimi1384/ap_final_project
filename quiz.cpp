#include "quiz.h"
#include <iostream>
#include <sstream>
#include <algorithm>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<Question> getQuestions(int numQuestions, const std::string& difficulty, int category) {
    std::vector<Question> questions;

    std::string url = "https://opentdb.com/api.php?amount=10" + std::to_string(numQuestions) +
                      "&category=" + std::to_string(category) +
                      "&difficulty=" + difficulty +
                      "&type=multiple";

    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            Json::Value jsonData;
            Json::CharReaderBuilder builder;
            std::string errs;

            std::istringstream s(readBuffer);

            if (Json::parseFromStream(builder, s, &jsonData, &errs)) {
                for (const auto& item : jsonData["results"]) {
                    Question q;
                    q.questionText = item["question"].asString();
                    q.correctAnswer = item["correct_answer"].asString();
                    q.options.push_back(q.correctAnswer);
                    for (const auto& option : item["incorrect_answers"]) {
                        q.options.push_back(option.asString());
                    }
                    std::random_shuffle(q.options.begin(), q.options.end());
                    questions.push_back(q);
                }
            }
        }
    }

    curl_global_cleanup();
    return questions;
}
