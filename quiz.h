#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <random>  // Include for random engine
#include <sstream>  // Include for std::istringstream

// Structure to store question data
struct Question {
    std::string question;
    std::string options[4];
    std::string correct_answer;
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Question fetchQuestion(int amount, const std::string& difficulty, int category) {
    std::string readBuffer;
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://opentdb.com/api.php?amount=10" + std::to_string(amount)
                        + "&difficulty=" + difficulty
                        + "&category=" + std::to_string(category);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    curl_global_cleanup();

    nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
    auto result = jsonData["results"][0];

    Question question;
    question.question = result["question"].get<std::string>();
    question.options[0] = result["correct_answer"].get<std::string>();
    for (nlohmann::json::size_type i = 0; i < result["incorrect_answers"].size(); ++i) {  // Use json::size_type
        question.options[i + 1] = result["incorrect_answers"][i].get<std::string>();
    }
    question.correct_answer = result["correct_answer"].get<std::string>();

    // Shuffle the options
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(std::begin(question.options), std::end(question.options), g);

    return question;
}

#endif // QUIZ_H
