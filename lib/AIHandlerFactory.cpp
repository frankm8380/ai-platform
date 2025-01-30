#include "AIHandlerFactory.h"

IApiHandler* create_ai_handler(AIPlatform platform) {
    switch (platform) {
        case AIPlatform::OpenAI:
            return new OpenAIHandler();
        case AIPlatform::DeepSeek:
            return new DeepSeekHandler();
        default:
            throw std::runtime_error("Unsupported AI platform.");
    }
}
