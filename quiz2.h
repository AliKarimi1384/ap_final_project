#ifndef QUIZ2_H
#define QUIZ2_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <random>
#include <queue>
#include <chrono>
#include <thread>

// Structure to store question information
struct Question {
    std::string question;
    std::string options[4];
    std::string correct_answer;
};

// Static queue to store fetched questions
static std::queue<Question> questionQueue;
static std::chrono::steady_clock::time_point lastFetchTime;

// Callback function for libcurl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void fetchQuestions(int amount, const std::string& difficulty) {
    std::string readBuffer;
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://opentdb.com/api.php?amount=" + std::to_string(amount)
                        + "&difficulty=" + difficulty + "&type=multiple";

        std::cout << "Fetching URL: " << url << std::endl;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        std::cout << "Response code: " << response_code << std::endl;

        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return;
        }

        std::cout << "Response content: " << readBuffer << std::endl;
    }
    curl_global_cleanup();

    try {
        auto jsonData = nlohmann::json::parse(readBuffer);

        if (jsonData["response_code"] != 0) {
            std::cerr << "Error: API returned a non-zero response code." << std::endl;
            return;
        }

        for (const auto& result : jsonData["results"]) {
            Question question;

            if (result.contains("question") && result["question"].is_string()) {
                question.question = result["question"].get<std::string>();
            } else {
                std::cerr << "Error: Question field is missing or not a string." << std::endl;
                continue;
            }

            if (result.contains("correct_answer") && result["correct_answer"].is_string()) {
                question.options[0] = result["correct_answer"].get<std::string>();
                question.correct_answer = question.options[0];
            } else {
                std::cerr << "Error: Correct answer field is missing or not a string." << std::endl;
                continue;
            }

            if (result.contains("incorrect_answers") && result["incorrect_answers"].is_array()) {
                int i = 1;
                for (const auto& incorrect : result["incorrect_answers"]) {
                    if (incorrect.is_string()) {
                        if (i < 4) {  // Ensure we do not go out of bounds
                            question.options[i++] = incorrect.get<std::string>();
                        } else {
                            std::cerr << "Error: Too many incorrect answers." << std::endl;
                            continue;
                        }
                    } else {
                        std::cerr << "Error: An incorrect answer is not a string." << std::endl;
                        continue;
                    }
                }
            } else {
                std::cerr << "Error: Incorrect answers field is missing or not an array." << std::endl;
                continue;
            }

            // Shuffle the options to randomize their order
            std::shuffle(std::begin(question.options), std::end(question.options), std::default_random_engine{});

            // Push the question to the queue
            questionQueue.push(question);
        }

        // Update the last fetch time
        lastFetchTime = std::chrono::steady_clock::now();
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
}

Question fetchQuestion(int amount, const std::string& difficulty) {
    // If the queue is empty, fetch new questions
    if (questionQueue.empty()) {
        // Check if it's been more than 5 seconds since the last fetch
        auto now = std::chrono::steady_clock::now();
        auto durationSinceLastFetch = std::chrono::duration_cast<std::chrono::seconds>(now - lastFetchTime).count();
        if (durationSinceLastFetch < 5) {
            std::cerr << "Error: Too soon to fetch new questions. Please wait." << std::endl;
            return {};
        }

        fetchQuestions(amount, difficulty);
    }

    // Get the next question from the queue
    if (!questionQueue.empty()) {
        Question question = questionQueue.front();
        questionQueue.pop();
        return question;
    } else {
        // Log error if the queue is still empty after fetching
        std::cerr << "Error: No questions available in the queue." << std::endl;
        return {};
    }
}

#endif // QUIZ2_H
