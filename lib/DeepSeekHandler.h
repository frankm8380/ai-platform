#ifndef DEEPSEEK_HANDLER_H
#define DEEPSEEK_HANDLER_H

#include "IApiHandler.h"

class DeepSeekHandler : public IApiHandler {
public:
    std::string get_response(const std::string& session_id, const std::string& user_input, SessionManager& session_manager) override;
};

#endif // DEEPSEEK_HANDLER_H
