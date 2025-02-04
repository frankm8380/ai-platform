
#include "SessionManager.h"
#include "DebugUtils.h"
#include <sqlite3.h>
#include <iostream>
#include <sstream>

SessionManager::SessionManager(bool use_database) : use_database(use_database), db(nullptr) {
    if (use_database) {
        init_database();
    }
}

SessionManager::~SessionManager() {
    if (use_database) {
        cleanup_database();
    }
}

void SessionManager::add_message(const std::string& session_id, const std::string& role, const std::string& content) {
    if (use_database) {
        add_message_to_db(session_id, role, content);
    } else {
        memory_store[session_id].emplace_back(role, content);
    }
}

std::vector<std::pair<std::string, std::string>> SessionManager::get_history(const std::string& session_id) const {
    if (use_database) {
        return get_history_from_db(session_id);
    } else {
        auto it = memory_store.find(session_id);
        return (it != memory_store.end()) ? it->second : std::vector<std::pair<std::string, std::string>>{};
    }
}

void SessionManager::init_database() {
    const char* create_table_sql = R"(
        CREATE TABLE IF NOT EXISTS messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            session_id TEXT NOT NULL,
            role TEXT NOT NULL,
            content TEXT NOT NULL
        );
    )";

    if (sqlite3_open("session_manager.db", reinterpret_cast<sqlite3**>(&db)) != SQLITE_OK) {
        DEBUG_LOG(DEBUG_LEVEL_ERROR, std::string("Failed to open SQLite database: ") + sqlite3_errmsg(reinterpret_cast<sqlite3*>(db)));
    }

    char* error_message = nullptr;
    if (sqlite3_exec(reinterpret_cast<sqlite3*>(db), create_table_sql, nullptr, nullptr, &error_message) != SQLITE_OK) {
        std::cerr << "Failed to create table: " << error_message << std::endl;
        sqlite3_free(error_message);
    }
}

void SessionManager::cleanup_database() {
    if (db) {
        sqlite3_close(reinterpret_cast<sqlite3*>(db));
        db = nullptr;
    }
}

void SessionManager::add_message_to_db(const std::string& session_id, const std::string& role, const std::string& content) {
    const char* insert_sql = R"(
        INSERT INTO messages (session_id, role, content)
        VALUES (?, ?, ?);
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(reinterpret_cast<sqlite3*>(db), insert_sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, session_id.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, role.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, content.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert message: " << sqlite3_errmsg(reinterpret_cast<sqlite3*>(db)) << std::endl;
        }

        sqlite3_finalize(stmt);
    }
}

std::vector<std::pair<std::string, std::string>> SessionManager::get_history_from_db(const std::string& session_id) const {
    const char* select_sql = R"(
        SELECT role, content
        FROM messages
        WHERE session_id = ?
        ORDER BY id;
    )";

    sqlite3_stmt* stmt;
    std::vector<std::pair<std::string, std::string>> history;

    if (sqlite3_prepare_v2(reinterpret_cast<sqlite3*>(db), select_sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, session_id.c_str(), -1, SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string content = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            history.emplace_back(role, content);
        }

        sqlite3_finalize(stmt);
    }

    return history;
}
