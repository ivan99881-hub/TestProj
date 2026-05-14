#include "ConverterJSON.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::ifstream configFile("config.json");
    if (!configFile.is_open()) {
        throw std::runtime_error("config file is missing");
    }

    json config;
    configFile >> config;

    if (!config.contains("config")) {
        throw std::runtime_error("config file is empty");
    }

    std::cout << "Starting: " << config["config"]["name"].get<std::string>() << std::endl;

    std::vector<std::string> documents;
    for (const auto& path : config["files"]) {
        std::ifstream file(path.get<std::string>());
        if (file.is_open()) {
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            documents.push_back(content);
        }
        else {
            std::cerr << "File not found: " << path << std::endl;
        }
    }
    return documents;
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream configFile("config.json");
    if (!configFile.is_open()) return 5;

    json config;
    configFile >> config;

    /** Default limit is 5 if not specified in config */
    if (config["config"].contains("max_responses")) {
        return config["config"]["max_responses"].get<int>();
    }
    return 5;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream requestFile("requests.json");
    if (!requestFile.is_open()) {
        std::cerr << "requests.json is missing" << std::endl;
        return {};
    }

    json data;
    requestFile >> data;
    return data["requests"].get<std::vector<std::string>>();
}

void ConverterJSON::PutAnswers(std::vector<std::vector<RelativeIndex>> answers) {
    nlohmann::json output;

    for (size_t i = 0; i < answers.size(); ++i) {
        char buf[15];
        snprintf(buf, sizeof(buf), "request%03zu", i + 1);
        std::string reqId(buf);

        if (answers[i].empty()) {
            output["answers"][reqId]["result"] = "false";
        }
        else {
            output["answers"][reqId]["result"] = "true";

            /** If more than one result, use 'relevance' array per TZ */
            if (answers[i].size() > 1) {
                for (const auto& res : answers[i]) {
                    nlohmann::json item;
                    item["docid"] = res.doc_id;
                    item["rank"] = res.rank;
                    output["answers"][reqId]["relevance"].push_back(item);
                }
            }
            else {
                output["answers"][reqId]["docid"] = answers[i][0].doc_id;
                output["answers"][reqId]["rank"] = answers[i][0].rank;
            }
        }
    }

    std::ofstream outFile("answers.json");
    if (outFile.is_open()) {
        outFile << output.dump(4);
    }
}