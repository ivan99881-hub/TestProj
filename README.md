# TestProj
Учебный проект.
Skillbox Search Engine
A high-performance, console-based local search engine written in C++17. The system indexes a set of text documents and provides ranked search results based on user queries using an inverted index and multi-threaded processing.

🚀 Features
Inverted Index: Accelerated search using a mapping of words to their document frequencies.

Multi-threaded Indexing: Efficient document processing using std::thread and std::mutex to handle large datasets.

Ranked Results: Calculates document relevance based on word frequency and normalizes results to a [0.0, 1.0] scale.

JSON Configuration: Flexible setup for file paths and search parameters via config.json and requests.json.

Unit Testing: Robust logic verification using the Google Test (GTest) framework.

🛠 Tech Stack
Language: C++17

Build System: CMake (3.15+)

Libraries:

nlohmann/json — For parsing and generating JSON files.

Google Test — For unit testing the core logic.

📂 Project Structure
include/ — Header files (ConverterJSON.h, InvertedIndex.h, SearchServer.h).

src/ — Source files and the main entry point.

resources/ — Folder containing text documents to be indexed.

tests/ — Unit tests for indexing and ranking logic.

⚙️ Installation & Build
Clone the repository:

Bash
git clone https://github.com/yourusername/SkillboxSearchEngine.git
cd SkillboxSearchEngine
Configure and Build:
Using CMake:

Bash
mkdir build
cd build
cmake ..
cmake --build .
Visual Studio Users:
Open the folder in Visual Studio, and it will automatically detect the CMakeLists.txt file.

🖥 Usage
Place your text files in the resources/ folder.

Configure config.json with the file paths and max_responses limit.

Add your search queries to requests.json.

Run the executable:

Bash
./SkillboxSearchEngine
Check answers.json for the ranked search results.

🧪 Running Tests
To verify the indexing and search logic, run the test executable:

Bash
./test_engine
Or use the Test Explorer in Visual Studio to run the GTest suite.
