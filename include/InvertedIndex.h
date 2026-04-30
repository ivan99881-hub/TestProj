#pragma once

#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <thread>
#include <sstream>
#include <algorithm>

/**
 * @brief Word frequency in a specific document
 */
struct Entry {
    size_t doc_id, count;

    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

/**
 * @brief Class for creating and managing the inverted search index
 */
class InvertedIndex {
public:
    InvertedIndex() = default;

    /**
     * @brief Updates the database and runs indexing in threads
     */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    /**
     * @brief Returns frequency of a word
     */
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
    std::mutex index_mutex;
};