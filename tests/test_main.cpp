#include "InvertedIndex.h"
#include "SearchServer.h"
#include <gtest/gtest.h>

/**
 * @brief Utility function to run tests for InvertedIndex
 */
void TestInvertedIndexFunctionality(
    const std::vector<std::string>& docs,
    const std::vector<std::string>& requests,
    const std::vector<std::vector<Entry>>& expected
) {
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    std::vector<std::vector<Entry>> result;
    for (auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}

/**
 * @brief Test basic indexing with simple sentences
 */
TEST(TestCaseInvertedIndex, TestBasic) {
    const std::vector<std::string> docs = {
        "london is the capital of great britain",
        "big ben is the nickname for the great bell"
    };
    const std::vector<std::string> requests = { "london", "the" };
    const std::vector<std::vector<Entry>> expected = {
        {{0, 1}},
        {{0, 1}, {1, 2}}
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

/**
 * @brief Test missing word handling
 */
TEST(TestCaseInvertedIndex, TestMissingWord) {
    const std::vector<std::string> docs = {
        "a b c d e f g h i j k l",
        "statement"
    };
    const std::vector<std::string> requests = { "m", "statement" };
    const std::vector<std::vector<Entry>> expected = {
        {},
        {{1, 1}}
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseSearchServer, TestSimple) {
    const std::vector<std::string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const std::vector<std::string> request = { "milk water", "sugar" };
    const std::vector<std::vector<RelativeIndex>> expected = {
        {
            {2, 1.0f},
            {0, 0.7f},
            {1, 0.3f}
        },
        {}
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);

    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i].size(), expected[i].size());
        for (size_t j = 0; j < result[i].size(); ++j) {
            EXPECT_EQ(result[i][j].doc_id, expected[i][j].doc_id);
            EXPECT_NEAR(result[i][j].rank, expected[i][j].rank, 0.01f);
        }
    }
}