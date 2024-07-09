#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <ctime>
#include <cstdlib>

struct Question {
    std::string question;
    std::string options[4];
    std::string correct_answer;
};

struct GameData {
    int index;
    std::string id;
    std::string time_stamp;
    int score;
    std::string difficulty;
};

std::string generateRandomID() {
    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int len = 8;
    std::string id;
    for (int i = 0; i < len; ++i) {
        id += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return id;
}

std::string getCurrentTimeStamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ltm);
    return std::string(timestamp);
}

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

void saveGameDataToCSV(const std::string& filename, const std::vector<GameData>& game_data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    file << "Index,ID,Time Stamp,Score,Difficulty\n";
    for (const auto& data : game_data) {
        file << data.index << ","
             << data.id << ","
             << data.time_stamp << ","
             << data.score << ","
             << data.difficulty << "\n";
    }

    file.close();
}

int main() {
    srand(time(0));
    std::vector<Question> questions = fetchQuestions(5, "medium", 18); 
    std::vector<GameData> game_data;

    
    for (int i = 0; i < 5; ++i) {
        GameData data;
        data.index = i + 1;
        data.id = generateRandomID();
        data.time_stamp = getCurrentTimeStamp();
        data.score = rand() % 101; 
        data.difficulty = "medium";
        game_data.push_back(data);
    }

    saveGameDataToCSV("game_data.csv", game_data);

    std::cout << "Game data saved to game_data.csv" << std::endl;

    return 0;
}
