#ifndef AI_HANDLER_FACTORY_H
#define AI_HANDLER_FACTORY_H

#include "IApiHandler.h"
#include "OpenAIHandler.h"
#include "DeepSeekHandler.h"
#include <stdexcept>

// Enum to define supported AI platforms
enum class AIPlatform { OpenAI, DeepSeek };

// Factory function to create the appropriate handler
IApiHandler* create_ai_handler(AIPlatform platform);

#endif // AI_HANDLER_FACTORY_H
