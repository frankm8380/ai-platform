#ifndef I_API_HANDLER_H
#define I_API_HANDLER_H

#include <string>
#include "SessionManager.h"

class IApiHandler {
public:
    virtual ~IApiHandler() = default;
    virtual std::string get_response(const std::string& session_id, const std::string& user_input, SessionManager& session_manager) = 0;
};

#endif // I_API_HANDLER_H
