#ifndef OPENAI_HANDLER_H
#define OPENAI_HANDLER_H

#include "IApiHandler.h"

class OpenAIHandler : public IApiHandler {
public:
    std::string get_response(const std::string& session_id, const std::string& user_input, SessionManager& session_manager) override;
};

#endif // OPENAI_HANDLER_H
