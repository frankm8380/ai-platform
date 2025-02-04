# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(AIChatApps VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a static library from common source files in the `lib` directory
add_library(AIPlatform STATIC
    lib/AiHandlerFactory.cpp
    lib/OpenAiHandler.cpp
    lib/DeepSeekHandler.cpp
    lib/SessionManager.cpp
)

# Include directories for the library
target_include_directories(AIPlatform PRIVATE ${PROJECT_SOURCE_DIR}/lib)

# Define the executable target for OpenAiChat
add_executable(OpenAiChat
    app/cli_openai.cpp
)

# Define the executable target for DeepSeekChat
add_executable(DeepSeekChat
    app/cli_deepseek.cpp
)

# Define the executable target for AIConversationApp
add_executable(AIConversationApp
    app/ai_conversation_app.cpp
)

# Include the directories for headers (both `lib` and `app`)
target_include_directories(OpenAiChat PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/app
)

target_include_directories(DeepSeekChat PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/app
)

target_include_directories(AIConversationApp PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/app
)

# Link the common library to all executables
target_link_libraries(OpenAiChat AIPlatform)
target_link_libraries(DeepSeekChat AIPlatform)
target_link_libraries(AIConversationApp AIPlatform)

