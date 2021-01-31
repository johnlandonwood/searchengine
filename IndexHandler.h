#ifndef SEARCH_ENGINE_INDEXHANDLER_H
#define SEARCH_ENGINE_INDEXHANDLER_H
#include "InvertedIndex.h"
#include "QueryProcessor.h"
#include "HashTable.h"
// Written by Landon Wood

/// Written by Landon Wood.
/// The IndexHandler instantiates only one instance of the AVLTree inverted index and the authors hash table.
/// It is responsible for reading and writing to the index and hash table, searching the index/hash table based on search queries, and storing some data for relevancy ranking.
class IndexHandler {
private:
    /// The inverted index, implemented as an AVL tree.
    InvertedIndex index;
    /// The authors hash table, storing all authors and the documents they appear in.
    HashTable<pair<string, set<string>>> authorsHashTable;
    /// A vector containing a filename and how many words appear in that file.
    vector<pair<string, int>> fileWordCount;
public:
    /// Constructor.
    IndexHandler();
    /// Adds a word to the InvertedIndex.
    /// \param word Word from .json document.
    /// \param document Filename of the above .json document.
    void addWord(string word, string document);
    /// Instantiate a QueryProcessor object, run the query processing function, and return the query's results
    /// \param word The query as entered by the user.
    /// \param numOfDocs The total number of files indexed; used in TF-IDF ranking within QueryProcessor.
    /// \return A vector of pairs containing the top 15 files from a query.
    vector<pair<string, int>> processQuery(string word, int numOfDocs);
    /// Adds an author and the documents they appear in to the hash table.
    /// \param authorsAndDocs A pair containing the author's name and all files they appear in.
    void addAuthor(pair<string, set<string>> authorsAndDocs);
    /// Returns the InvertedIndex.
    InvertedIndex getIndex();
    /// Returns the authors hash table.
    HashTable<pair<string, set<string>>>& getHashTable();
    /// Store the number of words that appear in a certain file, to be used for TF-IDF ranking
    /// \param filename The filename of a .json file.
    /// \param numWords The number of words that appear in the file's abstract and body text.
    void addFile(const string& filename, int numWords);
    /// Populates the inverted index with words from a saved persistence file.
    /// \param wordPersistenceFile The saved word persistence file, containing all words from the engine's previous execution.
    void loadWordPersistence(ifstream& wordPersistenceFile);
    /// Populates the author hash table with authors from a saved persistence file.
    /// \param authorPersistenceFile The saved author persistence file, containing all author names and documents from the engine's previous execution.
    void loadAuthorPersistence(ifstream& authorPersistenceFile);
    /// Gets the top 50 most frequent words in the InvertedIndex.
    /// \return A vector of strings containing the top 50 most frequent words in the InvertedIndex.
    vector<string> getTop50FrequentWords();
    /// Clears the InvertedIndex AVLTree.
    void clearIndex();

};

#endif //SEARCH_ENGINE_INDEXHANDLER_H
