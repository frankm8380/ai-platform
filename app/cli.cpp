#include "SessionManager.h"
#include "IApiHandler.h"
#include "AIHandlerFactory.h"
#include <iostream>

void start_cli() {
    SessionManager session_manager(true); // Initialize the session manager
    std::string session_id = "openAI_chat"; // Use a default session ID for now

    // Select AI platform
    AIPlatform platform = AIPlatform::OpenAI;  // Change to AIPlatform::DeepSeek as needed
    IApiHandler* ai_handler = create_ai_handler(platform);

    std::cout << "openAI Chat Platform\nType 'exit' to quit.\n\n";

    while (true) {
        std::string user_input;

        // Get user input
        std::cout << "You: ";
        std::getline(std::cin, user_input);

        if (user_input == "exit")
            break;

        try {
            // Get the AI response using the handler
            std::string ai_response = ai_handler->get_response(session_id, user_input, session_manager);

            // Display the AI response
            std::cout << "openAI: " << ai_response << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Clean up
    delete ai_handler;
}
