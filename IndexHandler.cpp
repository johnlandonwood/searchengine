#include <fstream>
#include "IndexHandler.h"
// Written by Landon Wood
// The IndexHandler instantiates only one instance of the AVLTree inverted index and the authors hash table
// It is responsible for reading and writing to the index and hash table,
// searching the index/hash table based on search queries,
// and storing some data for relevancy ranking.

IndexHandler::IndexHandler() {}

void IndexHandler::addWord(string word, string document) { // Add a word to the InvertedIndex
    index.addWord(word, document);
}

void IndexHandler::addAuthor(pair<string, set<string>> authorsAndDocs) { // Add an author to the hash table
    authorsHashTable.insert(authorsAndDocs);
}

vector<pair<string, int>> IndexHandler::processQuery(string query, int numOfDocs) { // Instantiate a QueryProcessor object, run the query processing function, and return the query's results
    vector<pair<string, int>> resultDocs;
    QueryProcessor QP(query, numOfDocs);
    resultDocs = QP.run(index, authorsHashTable, fileWordCount);
    return resultDocs;
}

InvertedIndex IndexHandler::getIndex() {
    return this->index;
}

HashTable<pair<string, set<string>>>& IndexHandler::getHashTable() {
    return this->authorsHashTable;
}

void IndexHandler::addFile(const string& filename, int numWords) { // Store the number of words that appear in a certain file, to be used for TF-IDF ranking
    pair<string, int> tempPair = make_pair(filename, numWords);
    this->fileWordCount.push_back(tempPair);
}

void IndexHandler::loadWordPersistence(ifstream& wordPersistenceFile) { // Load the saved word persistence file
    string line;
    int start = 0;
    while (getline(wordPersistenceFile, line)) {
        start = 0;
        string word;
        string filename;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                word = line.substr(start, i - start);
                start = i + 1;
                filename = line.substr(start, std::string::npos);
            }
        }
        this->index.addWord(word, filename);
    }
}

void IndexHandler::loadAuthorPersistence(ifstream& authorPersistenceFile) { // Load the saved author persistence file
    string line;
    int start = 0;
    while (getline(authorPersistenceFile, line)) {
        start = 0;
        string author;
        string filename;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                author = line.substr(start, i - start);
                start = i + 1;
                filename = line.substr(start, std::string::npos);
            }
        }
        if (!this->authorsHashTable.authorExists(author)) {
            set<string> files;
            files.insert(filename);
            pair<string, set<string>> tempPair = make_pair(author, files);
            authorsHashTable.insert(tempPair);
        }
        else {
            authorsHashTable[author].second.insert(filename);
        }
    }
}

vector<string> IndexHandler::getTop50FrequentWords() {
    return index.getTop50Words();
}

void IndexHandler::clearIndex() { // Clears the InvertedIndex AVLTree
    index.deleteIndex();
}