
#include "SessionManager.h"
#include "IApiHandler.h"
#include "AIHandlerFactory.h"
#include "DeepSeekHandler.h"
#include <iostream>
#include "DebugUtils.h"

void main() {
    SessionManager session_manager(true);
    std::string session_id = "deepseek_chat";

    DeepSeekHandler* ai_handler = static_cast<DeepSeekHandler*>(create_ai_handler(AIPlatform::DeepSeek));
    ai_handler->set_system_prompt("You are a research-oriented assistant with expertise in deep technical topics.");

    DEBUG_LOG(DebugLevel::INFO, "Launching DeepSeek Chat Platform");
    std::cout << "DeepSeek Chat Platform\nType 'exit' to quit.\n";

    while (true) {
        std::string user_input;
        std::cout << "You: ";
        std::getline(std::cin, user_input);

        if (user_input == "exit")
            break;

        session_manager.add_message(session_id, "user", user_input);

        DEBUG_LOG(DebugLevel::INFO, "Processing user input");
        try {
            std::string ai_response = ai_handler->get_response(session_id, user_input, session_manager, "deepseek_handler");
            session_manager.add_message(session_id, "deepseek_handler", ai_response);
            std::cout << "deepseekAI: " << ai_response << "\n";
        } catch (const std::exception& e) {
            DEBUG_LOG(DebugLevel::ERROR, std::string("Exception caught: ") + e.what());
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    delete ai_handler;
}
