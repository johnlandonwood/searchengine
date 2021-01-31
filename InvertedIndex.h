#ifndef SEARCH_ENGINE_HARRISON_WOOD_INVERTEDINDEX_H
#define SEARCH_ENGINE_HARRISON_WOOD_INVERTEDINDEX_H
#include "InvertedIndexEntry.h"
#include "AVLTree.h"
//written by Maria Harrison
//Inverted Index class that adds InvertedIndexEntry object to the InvertedIndex
//which is structured as an AVLTree

/// Written by Maria Harrison.
/// Inverted index class that adds InvertedIndexEntry object to the InvertedIndex, which is structured as an AVL tree.
class InvertedIndex{
private:
    AVLTree<InvertedIndexEntry, string> invertedIndexTree;
    int numOfNodes;
public:

    /// Default constructor
    InvertedIndex();

    //add word with document
    /// Adds a word to the inverted index with its associated document
    /// \param word Word to be added
    /// \param document Document to be added
    void addWord(string word, string document);

    //return true if word is in index
    /// Checks if a word is in the inverted index
    /// \param word Word to be checked
    /// \return True if the word exists in the index, false if not
    bool wordInIndex(string word);

    /// Gets the documents associated with a word
    /// \param word A word in the index
    /// \return A vector of pairs containing the documents the word appears in, and an integer for the number of times that word appears in the document
    vector<pair<string, int>> getDocs(string word);

    /// Gets the number of nodes in the AVL tree
    /// \return An integer for the number of nodes in the tree
    int getNumOfNodes();

    /// Finds the top 50 most frequent words in the InvertedIndex
    /// \return A vector of strings containing the top 50 most frequent words
    vector<string> getTop50Words();

    /// Deletes all words in the index
    void deleteIndex();

};

#endif //SEARCH_ENGINE_HARRISON_WOOD_INVERTEDINDEX_H

