#ifndef SEARCH_ENGINE_QUERYPROCESSOR_H
#define SEARCH_ENGINE_QUERYPROCESSOR_H
#include <string>
#include "InvertedIndex.h"
#include "HashTable.h"
//written by Maria Harrison
using namespace std;

/// Written by Maria Harrison.
/// Parses queries entered by the user in UserInterface and ranks the results using TF-IDF
class QueryProcessor{
private:
    string query;
    int totalDocsIndexed;
    vector<pair<string,int>> documentWeights;
public:
    //overload constructor
    /// Default constructor
    QueryProcessor();

    //constructor with two parameters
    /// Parameterized constructor
    /// \param input The query entered by the user
    /// \param numOfDocs The total number of documents indexed by the engine
    QueryProcessor(string input, int numOfDocs);

    //process the query
    /// Processes a query entered by the user.
    /// \param InvertedIndex The engine's inverted index
    /// \param hashTable The engine's author hash table
    /// \param fileWordCount A vector of pairs containing all the documents and their associated word count
    /// \return A vector of pairs containing up to the 15 most relevant documents based on the user's query
    vector<pair<string, int>> run(InvertedIndex InvertedIndex, HashTable<pair<string, set<string>>> hashTable, const vector<pair<string, int>>& fileWordCount);

    //get num of words in a file
    /// Gets the word count of a specific document
    /// \param filename The document
    /// \param fileWordCount A vector of pairs containing all the documents and their associated word count
    /// \return The document's word count
    int findFileWordCount(const string &filename, const vector<pair<string, int>> &fileWordCount);

    /// Checks if a file is in the documentWeights vector
    /// \param filename The file's name to be checked
    /// \return True if the file exists in the documentWeights vector, false if not
    bool fileExist(string filename);

    /// Gets the position of a document in the documentWeights vector
    /// \param filename The file to be located
    /// \return An integer for the index where the document exists in the documentWeights vector
    int getFilePosition(string filename);
};

#endif //SEARCH_ENGINE_QUERYPROCESSOR_H

