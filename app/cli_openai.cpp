
#include "SessionManager.h"
#include "IApiHandler.h"
#include "AIHandlerFactory.h"
#include "OpenAIHandler.h"
#include <iostream>
#include "DebugUtils.h"

void main() {
    SessionManager session_manager(true);
    std::string session_id = "openAI_chat";

    OpenAIHandler* ai_handler = static_cast<OpenAIHandler*>(create_ai_handler(AIPlatform::OpenAI));
    ai_handler->set_system_prompt("You are a conversational assistant with a focus on clarity and friendliness.");

    DEBUG_LOG(DebugLevel::INFO, "Launching OpenAI Chat Platform");
    std::cout << "openAI Chat Platform\nType 'exit' to quit.\n";

    while (true) {
        std::string user_input;
        std::cout << "You: ";
        std::getline(std::cin, user_input);

        if (user_input == "exit")
            break;

        session_manager.add_message(session_id, "user", user_input);

        DEBUG_LOG(DebugLevel::INFO, "Processing user input");
        try {
            std::string ai_response = ai_handler->get_response(session_id, user_input, session_manager, "openai_handler");
            session_manager.add_message(session_id, "openai_handler", ai_response);
            std::cout << "openAI: " << ai_response << "\n";
        } catch (const std::exception& e) {
            DEBUG_LOG(DebugLevel::ERROR, std::string("Exception caught: ") + e.what());
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    delete ai_handler;
}
