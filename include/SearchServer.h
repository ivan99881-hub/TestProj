#pragma once

#include "InvertedIndex.h"
#include <vector>
#include <string>

/**
 * @brief Search relevance structure
 */
struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

/**
 * @brief Processes queries and ranks results
 */
class SearchServer {
public:
    /** Reference to index must be passed in constructor */
    SearchServer(InvertedIndex& idx) : _index(idx) {};

    /**
     * @brief Performs search and ranking
     */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index; // Changed to reference to avoid copying mutex
};