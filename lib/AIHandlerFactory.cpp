#include "AIHandlerFactory.h"
#include "DebugUtils.h"

IApiHandler* create_ai_handler(AIPlatform platform) {
    switch (platform) {
        case AIPlatform::OpenAI:
            return new OpenAIHandler();
        case AIPlatform::DeepSeek:
            return new DeepSeekHandler();
        default:
            DEBUG_LOG(DEBUG_LEVEL_ERROR, "Unsupported AI platform.");
        throw std::runtime_error("Unsupported AI platform.");
    }
}
