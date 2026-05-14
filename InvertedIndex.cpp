#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = input_docs;
    freq_dictionary.clear();

    std::vector<std::thread> threads;

    for (size_t i = 0; i < docs.size(); ++i) {
        threads.emplace_back([this, i]() {
            std::map<std::string, size_t> local_freq;
            std::stringstream ss(docs[i]);
            std::string word;

            while (ss >> word) {
                local_freq[word]++;
            }

            std::lock_guard<std::mutex> lock(index_mutex);
            for (const auto& [word, count] : local_freq) {
                freq_dictionary[word].push_back({ i, count });
            }
            });
    }

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    if (freq_dictionary.count(word)) {
        return freq_dictionary.at(word);
    }
    return {};
}