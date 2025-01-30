#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <string>
#include <vector>
#include <map> // Required for std::map
#include <utility> // Required for std::pair

class SessionManager {
public:
    // Constructor
    SessionManager(bool use_database = false);

    // Destructor
    ~SessionManager();

    // Add a message to the session
    void add_message(const std::string& session_id, const std::string& role, const std::string& content);

    // Get conversation history for a session
    std::vector<std::pair<std::string, std::string>> get_history(const std::string& session_id) const;

private:
    bool use_database;

    // In-memory storage
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> memory_store;

    // SQLite database connection
    void* db; // Placeholder for SQLite database handle (if needed)

    // Initialize SQLite database
    void init_database();

    // Clean up SQLite resources
    void cleanup_database();

    // Helper methods for database operations
    void add_message_to_db(const std::string& session_id, const std::string& role, const std::string& content);
    std::vector<std::pair<std::string, std::string>> get_history_from_db(const std::string& session_id) const;
};

#endif // SESSION_MANAGER_H
