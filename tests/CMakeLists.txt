cmake_minimum_required(VERSION 3.15)

project(server_test)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(server_test 
    test_main.cpp 
    ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/SearchServer.cpp
)

target_include_directories(server_test PRIVATE ${INCLUDE_DIR})

target_link_libraries(server_test PRIVATE gtest_main nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(server_test)

if(MSVC)
    set_target_properties(server_test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()