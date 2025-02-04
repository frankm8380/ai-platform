#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include <iostream>

// Define debug levels as constants to work with preprocessor macros
constexpr int DEBUG_LEVEL_NONE = 0;
constexpr int DEBUG_LEVEL_ERROR = 1;
constexpr int DEBUG_LEVEL_WARNING = 2;
constexpr int DEBUG_LEVEL_INFO = 3;

// Define the active debug level globally (e.g., set to DEBUG_LEVEL_INFO to see all logs)
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DEBUG_LEVEL_INFO
#endif

// Simplified macro to handle debug logging with integer level comparison
#define DEBUG_LOG(level, message) do { \
    if (level <= DEBUG_LEVEL) { \
        std::cerr << message << std::endl; \
    } \
} while (0)

#endif // DEBUG_UTILS_H
