
#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <utility>

class SessionManager {
public:
    SessionManager(bool use_database = false);
    ~SessionManager();

    void add_message(const std::string& session_id, const std::string& role, const std::string& content);
    std::vector<std::pair<std::string, std::string>> get_history(const std::string& session_id) const;

private:
    bool use_database;
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> memory_store;
    void* db;

    void init_database();
    void cleanup_database();
    void add_message_to_db(const std::string& session_id, const std::string& role, const std::string& content);
    std::vector<std::pair<std::string, std::string>> get_history_from_db(const std::string& session_id) const;
};

#endif // SESSION_MANAGER_H
