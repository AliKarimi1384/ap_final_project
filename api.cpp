#include "api.h"
#include <curl/curl.h>
#include <iostream>
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        // Handle memory problem
        return 0;
    }
    return newLength;
}

std::string api::httpGet(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    if(res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    return readBuffer;
}

nlohmann::json api::fetchTriviaQuestions(const std::string& category, const std::string& difficulty, int amount) {
    std::string url = "https://opentdb.com/api.php?amount=" + std::to_string(amount) +
                      "&category=" + category +
                      "&difficulty=" + difficulty +
                      "&type=multiple";

    std::string response = httpGet(url);
    nlohmann::json jsonResponse = nlohmann::json::parse(response);

    return jsonResponse;
}
