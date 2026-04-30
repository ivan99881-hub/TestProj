cmake_minimum_required(VERSION 3.15)

project(SkillboxSearchEngine)

# --- Global Settings ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- External Libraries (FetchContent) ---
include(FetchContent)

# 1. nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

# 2. Google Test (GTest)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Apply settings and download
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(nlohmann_json googletest)

# --- Executable: Main Application ---
# Contains business logic and entry point
add_executable(SkillboxSearchEngine 
    src/main.cpp 
    src/ConverterJSON.cpp 
    src/InvertedIndex.cpp
    src/SearchServer.cpp
)

# --- Executable: Unit Tests ---
# Contains logic and tests (without main.cpp to avoid double main())
add_executable(test_engine 
    src/InvertedIndex.cpp 
    src/SearchServer.cpp
    src/test_main.cpp
)

# --- Headers and Includes ---
target_include_directories(SkillboxSearchEngine PRIVATE include)
target_include_directories(test_engine PRIVATE include)

# --- Linking Libraries ---
target_link_libraries(SkillboxSearchEngine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(test_engine PRIVATE gtest_main nlohmann_json::nlohmann_json)

# --- Testing Configuration ---
include(GoogleTest)
enable_testing()
gtest_discover_tests(test_engine)

# --- MSVC Visual Studio Fixes ---
if(MSVC)
    # Sets working directory to project root so JSON files are found
    set_target_properties(SkillboxSearchEngine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    set_target_properties(test_engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()