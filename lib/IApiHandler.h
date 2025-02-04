#ifndef I_API_HANDLER_H
#define I_API_HANDLER_H

#include <string>
#include "SessionManager.h"

class IApiHandler {
public:
    virtual ~IApiHandler() = default;

    // Updated method with the role_name parameter to allow dynamic role handling
    virtual std::string get_response(
        const std::string& session_id,
        const std::string& user_input,
        SessionManager& session_manager,
        const std::string& role_name
    ) = 0;
};

#endif // I_API_HANDLER_H
