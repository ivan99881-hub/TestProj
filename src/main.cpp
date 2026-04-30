#include "SkillboxSearchEngine.h"

int main() {
    try {
        ConverterJSON converter;

        /** Load documents from config.json */
        auto docs = converter.GetTextDocuments();

        /** Create and update index */
        InvertedIndex index;
        index.UpdateDocumentBase(docs);

        /** Initialize search server and process requests */
        SearchServer server(index);
        auto requests = converter.GetRequests();
        auto result = server.search(requests);

        /** Save results to answers.json */
        converter.PutAnswers(result);

        std::cout << "Indexing and search completed successfully." << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}