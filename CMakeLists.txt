cmake_minimum_required(VERSION 3.15)

include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

file(COPY ${CMAKE_SOURCE_DIR}/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/requests.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(search_server 
    main.cpp 
    ConverterJSON.cpp 
    InvertedIndex.cpp 
    SearchServer.cpp
)

target_include_directories(search_server PRIVATE ${INCLUDE_DIR})

target_link_libraries(search_server PRIVATE nlohmann_json::nlohmann_json)

if(MSVC)
    set_target_properties(search_server PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()