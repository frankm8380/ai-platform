
#ifndef OPENAI_HANDLER_H
#define OPENAI_HANDLER_H

#include "IApiHandler.h"

class OpenAIHandler : public IApiHandler {
private:
    std::string system_prompt;  // Added to support system prompts

public:
    void set_system_prompt(const std::string& prompt) { system_prompt = prompt; }
    std::string get_response(const std::string& session_id, const std::string& user_input, SessionManager& session_manager, const std::string& role_name) override;
};

#endif // OPENAI_HANDLER_H
