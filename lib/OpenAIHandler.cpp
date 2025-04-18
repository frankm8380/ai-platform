
#include "OpenAIHandler.h"
#include "DebugUtils.h"
#include "config.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>

#define OPENAI_API_URL "https://api.openai.com/v1/chat/completions"
#define OPENAI_MODEL "gpt-4"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string perform_openai_api_call(const std::string& payload) {
    CURL* curl = curl_easy_init();
    DEBUG_LOG(DEBUG_LEVEL_ERROR, "Failed to initialize CURL.");
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL.");
    }

    std::string response_data;
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + std::string(API_KEY)).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, OPENAI_API_URL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        throw std::runtime_error("CURL error: " + std::string(curl_easy_strerror(res)));
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    DEBUG_LOG(DEBUG_LEVEL_INFO, "Received API response: " + response_data);
    return response_data;
}

std::string OpenAIHandler::get_response(const std::string& session_id, const std::string& user_input, SessionManager& session_manager, const std::string& role_name) {
    auto history = session_manager.get_history(session_id);

    nlohmann::json messages = nlohmann::json::array();

   // Add system prompt
    if (!system_prompt.empty()) {
        messages.push_back({ {"role", "system"}, {"content", system_prompt} });
    }

    for (const auto& [role, content] : history) {
        std::string api_role = (role == role_name) ? "assistant" : "user";
        messages.push_back({ {"role", api_role}, {"content", content} });
    }

    messages.push_back({ {"role", "user"}, {"content", user_input} });

    nlohmann::json payload = {
        {"model", OPENAI_MODEL},
        {"messages", messages}
    };

    std::string payload_str = payload.dump();
    std::string response_data = perform_openai_api_call(payload_str);

    nlohmann::json response_json = nlohmann::json::parse(response_data);
    std::string message_content = response_json["choices"][0]["message"]["content"];

    session_manager.add_message(session_id, role_name, message_content);

    return message_content;
}
