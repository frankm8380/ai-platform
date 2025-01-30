
#include "SessionManager.h"
#include "IApiHandler.h"
#include "AIHandlerFactory.h"
#include <iostream>

void start_cli_deepseek() {
    SessionManager session_manager(true);
    std::string session_id = "deepseek_chat";

    // Select DeepSeek platform
    AIPlatform platform = AIPlatform::DeepSeek;
    IApiHandler* ai_handler = create_ai_handler(platform);

    std::cout << "DeepSeek Chat Platform\nType 'exit' to quit.\n\n";

    while (true) {
        std::string user_input;
        std::cout << "You: ";
        std::getline(std::cin, user_input);

        if (user_input == "exit")
            break;

        try {
            std::string ai_response = ai_handler->get_response(session_id, user_input, session_manager);
            std::cout << "deepseekAI: " << ai_response << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    delete ai_handler;
}
