#include "SearchServer.h"
#include <sstream>
#include <set>
#include <algorithm>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> result;

    for (const auto& query : queries_input) {
        std::stringstream ss(query);
        std::string word;
        std::set<std::string> unique_words;

        while (ss >> word) {
            unique_words.insert(word);
        }

        if (unique_words.empty()) {
            result.push_back({});
            continue;
        }

        std::map<size_t, size_t> abs_relevance;
        size_t max_abs_relevance = 0;

        for (const auto& w : unique_words) {
            auto entries = _index.GetWordCount(w); // Use _index reference
            for (const auto& entry : entries) {
                abs_relevance[entry.doc_id] += entry.count;
                if (abs_relevance[entry.doc_id] > max_abs_relevance) {
                    max_abs_relevance = abs_relevance[entry.doc_id];
                }
            }
        }

        if (max_abs_relevance == 0) {
            result.push_back({});
            continue;
        }

        std::vector<RelativeIndex> ranked_docs;
        for (const auto& [doc_id, count] : abs_relevance) {
            float rel_rank = static_cast<float>(count) / max_abs_relevance;
            ranked_docs.push_back({ doc_id, rel_rank });
        }

        std::sort(ranked_docs.begin(), ranked_docs.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            if (a.rank != b.rank) return a.rank > b.rank;
            return a.doc_id < b.doc_id;
            });

        result.push_back(ranked_docs);
    }
    return result;
}