#ifndef SEARCH_ENGINE_USERINTERFACE_H
#define SEARCH_ENGINE_USERINTERFACE_H
#include <iostream>
#include <fstream>
#include "InvertedIndex.h"
#include "IndexHandler.h"

/// Written by Landon Wood.
/// User Interface to take in user input and communicate with search engine accordingly
class UserInterface {
private:
    /// IndexHandler class object.
    IndexHandler indexHandler;
    /// File to read the index's saved words from previous execution.
    ifstream savedWordPersistenceFile;
    /// File to read the hash table's saved authors from previous execution.
    ifstream savedAuthorPersistenceFile;
    /// File to read the UserInterface's saved stats from previous execution.
    ifstream savedStatsPersistenceFile;
    /// The total number of files the engine has indexed.
    int totalNumFilesIndexed;
    /// Average words added to the InvertedIndex per file indexed.
    float avgWordsIndexedPerFile;
    /// The total number of unique words indexed - essentially, the size of the InvertedIndex.
    int totalUniqueWordsIndexed;
    /// The total number of unique authors added to the hash table.
    int totalNumUniqueAuthors;
    /// A vector to store the 50 words which appear most frequently in the corpus.
    vector<string> top50FrequentWords;
public:
    /// Constructor - initializes blank statistics.
    UserInterface();
    /// Search Engine main control function - takes user input and communicates with search engine accordingly
    void run();
    /// Loads saved persistence file into UserInterface object.
    /// \param statsPersistenceFile Saved persistence file with statistics.
    void loadStatsPersistence(ifstream& input);
};


#endif //SEARCH_ENGINE_USERINTERFACE_H