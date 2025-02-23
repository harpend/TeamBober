#include "backend_api.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <print>

// Callback for libcurl to write received data into a std::string.
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* str = static_cast<std::string*>(userp);
    size_t totalSize = size * nmemb;
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

namespace BackendAPI {

std::string get_issues() {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set URL for GET /issues
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/issues/recent");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "GET /issues failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return response;
}

std::string createIssue(const std::string& title,
                        const std::string& description,
                        const std::string& location,
                        const std::string& nickname,
                        const std::vector<std::string>& images) {
    CURL* curl;
    CURLcode res;
    std::string response;

    // Generate current UTC timestamp in ISO 8601 format.
    std::time_t now = std::time(nullptr);
    std::tm* gmt = std::gmtime(&now);
    std::stringstream ss;
    ss << std::put_time(gmt, "%Y-%m-%dT%H:%M:%SZ");
    std::string timestamp = ss.str();

    // Build JSON payload using nlohmann/json.
    nlohmann::json j;
    j["title"] = title;
    j["description"] = description;
    j["location"] = location;
    j["nickname"] = nickname;
    j["images"] = images;  // Converts vector to JSON array.

    // Add default fields.
    j["status"] = "pending";
    j["timestamp"] = timestamp;
    j["upvotes"] = 0;

    std::string jsonData = j.dump();

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set URL for POST /issues
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/issues");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Set header to indicate JSON content.
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "POST /issues failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return response;
}

std::string voteIssue(const std::string& issueID) {
    CURL* curl;
    CURLcode res;
    std::string response;
    // std::stringstream urlStream;
    // urlStream << "http://127.0.0.1:5000/issues/" << issueID << "/vote";
    std::string url = std::format("http://127.0.0.1:5000/issues/{}/vote", issueID);
    std::println("vote at {}", url);
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set URL for POST /issues/<issue_id>/vote.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        // Optionally set an empty POSTFIELDS if no body is required.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");

        // Set header to indicate JSON content.
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "POST /issues/<id>/vote failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return response;
}

void setIssueCompleted(const std::string &issueID)
{
    CURL* curl;
    CURLcode res;
    std::string response;
    // std::stringstream urlStream;
    // urlStream << "http://127.0.0.1:5000/issues/" << issueID << "/vote";
    std::string url = std::format("http://127.0.0.1:5000/{}/completed", issueID);
    std::println("vote at {}", url);
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set URL for POST /issues/<issue_id>/vote.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        // Optionally set an empty POSTFIELDS if no body is required.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");

        // Set header to indicate JSON content.
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "POST /issues/<id>/vote failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // return response;
}

} // namespace BackendAPI
