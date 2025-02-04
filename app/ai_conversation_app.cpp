
#include "SessionManager.h"
#include "IApiHandler.h"
#include "AIHandlerFactory.h"
#include "OpenAIHandler.h"
#include <iostream>
#include "DebugUtils.h"
#include <thread>
#include <chrono>

void main() {
    SessionManager session_manager(true);
    std::string session_id = "ai_conversation_0";

    // Initialize handlers with their own system prompts
    AIPlatform platform1 = AIPlatform::OpenAI;
    AIPlatform platform2 = AIPlatform::OpenAI;

    OpenAIHandler* ai_handler1 = static_cast<OpenAIHandler*>(create_ai_handler(platform1));
    OpenAIHandler* ai_handler2 = static_cast<OpenAIHandler*>(create_ai_handler(platform2));

    ai_handler1->set_system_prompt("You are a friendly assistant who loves sports discussions.");
    ai_handler2->set_system_prompt("You know nothing about sports, but interested and want to learn.");

    DEBUG_LOG(DEBUG_LEVEL_INFO, "Starting AI Conversation App");
    std::cout << "AI Conversation App\n";

    std::string user_input = "Hello! Let's chat about the Chicago Bears!";
    session_manager.add_message(session_id, "openai_handler_1", user_input);

    int duration_seconds = 120;
    auto start_time = std::chrono::steady_clock::now();
    std::string last_speaker = "openai_handler_1";

    DEBUG_LOG(DEBUG_LEVEL_INFO, "Starting conversation loop");
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count() < duration_seconds) {
        OpenAIHandler* current_handler = (last_speaker == "openai_handler_2") ? ai_handler1 : ai_handler2;
        std::string current_role = (last_speaker == "openai_handler_2") ? "openai_handler_1" : "openai_handler_2";

        std::string last_message = session_manager.get_history(session_id).back().second;

        try {
            std::string ai_response = current_handler->get_response(session_id, last_message, session_manager, current_role);
            std::cout << current_role << ": " << ai_response << "\n";
            last_speaker = current_role;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            DEBUG_LOG(DEBUG_LEVEL_ERROR, std::string("Exception caught: ") + e.what());
            break;
        }
    }

    delete ai_handler1;
    delete ai_handler2;
}
