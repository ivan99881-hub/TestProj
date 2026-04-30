#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "SearchServer.h"
#include <nlohmann/json.hpp>

/**
 * @brief Class for JSON data transformation and file management
 */
class ConverterJSON {
public:
    ConverterJSON() = default;

    /**
     * @brief Returns file contents listed in config.json
     */
    std::vector<std::string> GetTextDocuments();

    /**
     * @brief Returns max_responses limit from config.json
     */
    int GetResponsesLimit();

    /**
     * @brief Returns list of queries from requests.json
     */
    std::vector<std::string> GetRequests();

    /**
     * @brief Writes search results to answers.json
     */
    void PutAnswers(std::vector<std::vector<RelativeIndex>> answers);
};