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
    app/main.cpp
    app/cli.cpp
)

# Define the executable target for DeepSeekChat
add_executable(DeepSeekChat
    app/main_deepseek.cpp
    app/cli_deepseek.cpp
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

# Link the common library to both executables
target_link_libraries(OpenAiChat AIPlatform)
target_link_libraries(DeepSeekChat AIPlatform)

# Specify CURL and Zlib include and library paths
set(CURL_INCLUDE_DIR "C:/Users/frank/vcpkg/installed/x64-windows/include/curl")  # Adjust this path
set(CURL_LIBRARY "C:/Users/frank/vcpkg/installed/x64-windows/lib/libcurl.lib")  # Adjust this path
set(ZLIB_INCLUDE_DIR "C:/Users/frank/vcpkg/installed/x64-windows/include")      # Adjust this path
set(ZLIB_LIBRARY "C:/Users/frank/vcpkg/installed/x64-windows/lib/zlib.lib")     # Adjust this path

# Find CURL package
find_package(CURL REQUIRED)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(OpenAiChat ${CURL_LIBRARIES})
    target_link_libraries(DeepSeekChat ${CURL_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find CURL. Ensure it is installed and available.")
endif()

# Find Zlib package
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(OpenAiChat ${ZLIB_LIBRARIES})
    target_link_libraries(DeepSeekChat ${ZLIB_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find Zlib. Ensure it is installed and available.")
endif()

# Post-build commands to copy required DLLs to the output directory for OpenAiChat
add_custom_command(
    TARGET OpenAiChat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/frank/vcpkg/installed/x64-windows/bin/libcurl.dll"    # Adjust path
        $<TARGET_FILE_DIR:OpenAiChat>
)
add_custom_command(
    TARGET OpenAiChat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/frank/vcpkg/installed/x64-windows/bin/sqlite3.dll"    # Adjust path
        $<TARGET_FILE_DIR:OpenAiChat>
)
add_custom_command(
    TARGET OpenAiChat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/frank/vcpkg/installed/x64-windows/bin/zlib1.dll"      # Adjust path
        $<TARGET_FILE_DIR:OpenAiChat>
)

# Post-build commands to copy required DLLs to the output directory for DeepSeekChat
add_custom_command(
    TARGET DeepSeekChat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/frank/vcpkg/installed/x64-windows/bin/libcurl.dll"    # Adjust path
        $<TARGET_FILE_DIR:DeepSeekChat>
)
add_custom_command(
    TARGET DeepSeekChat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/frank/vcpkg/installed/x64-windows/bin/sqlite3.dll"    # Adjust path
        $<TARGET_FILE_DIR:DeepSeekChat>
)
add_custom_command(
    TARGET DeepSeekChat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/frank/vcpkg/installed/x64-windows/bin/zlib1.dll"      # Adjust path
        $<TARGET_FILE_DIR:DeepSeekChat>
)

# Output build details for debugging
message(STATUS "CURL Include Dirs: ${CURL_INCLUDE_DIRS}")
message(STATUS "CURL Libraries: ${CURL_LIBRARIES}")
message(STATUS "Zlib Include Dirs: ${ZLIB_INCLUDE_DIRS}")
message(STATUS "Zlib Libraries: ${ZLIB_LIBRARIES}")
