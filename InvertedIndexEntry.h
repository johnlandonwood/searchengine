#ifndef SEARCH_ENGINE_HARRISON_WOOD_INVERTEDINDEXENTRY_H
#define SEARCH_ENGINE_HARRISON_WOOD_INVERTEDINDEXENTRY_H
#include <string>
#include <set>
#include <vector>
//written by Maria Harrison
//InvertedIndexEntry class which contains a word and a set of strings as private data members

using namespace std;
/// Written by Maria Harrison.
/// InvertedIndexEntry represents an entry in the InvertedIndex, containing a word and set of strings for all documents the word appears in
class InvertedIndexEntry{
private:
    string word;
    vector<pair <string, int>> documents;
public:

    //default constructor
    /// Default constructor
    InvertedIndexEntry();

    //single argument constructor
    /// Parameterized constructor
    /// \param input Word from file
    InvertedIndexEntry(const string& input);

    //return index word
    /// Gets the InvertedIndexEntry's word
    /// \return A string containing the word
    string getWord();

    //return set of documents
    /// Gets the InvertedIndexEntry's documents
    /// \return A vector of pairs, containing a filename and the number of times the word appears in that document
    vector<pair<string, int>> getDocs();

    //add document
    /// Adds a document to the InvertedIndexEntry's documents vector
    /// \param document The filename to be added
    void addDoc(string document);

    //print documents
    /// Prints all documents in the InvertedIndexEntry's documents vector
    void printDocs();

    /// Checks if a document is associated with the entry's word
    /// \param document Document to be checked
    /// \return True if the document is in the entry's vector, false if not
    bool docInEntry(string document);

    /// Finds the document in the entry's vector, and increases that document's integer by one
    /// \param document The document whose counter will be incremented
    void increaseDoc(string document);

    /// Gets the total number of times a word appears in all documents
    /// \return An integer for the word's frequency in all documents
    int getWordFrequency();
};
#endif //SEARCH_ENGINE_HARRISON_WOOD_INVERTEDINDEXENTRY_H

