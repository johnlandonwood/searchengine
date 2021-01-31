#ifndef SEARCH_ENGINE_DOCUMENTPROCESSOR_H
#define SEARCH_ENGINE_DOCUMENTPROCESSOR_H
#include <set>
#include <string>
#include "InvertedIndex.h"
using namespace std;
// Written by Landon Wood

/// Written by Landon Wood.
/// Suite of functions for processing JSON documents and the metadata .csv.
/// Uses RapidJSON and Oleander Stemming libraries.
class DocumentProcessor {

private:
    /// A set of strings containing 636 English stop words.
    set<string> stopWords;
public:
    /// Constructor - loads stop words
    DocumentProcessor();
    /// Parses a .json file using RapidJSON and Oleander stemming library to stem words. Does not add any stop words to the index.
    /// \param filename The full filepath of a .json file, e.g. "C:\Users\Owner\Desktop\Downloads\SMU\Sophomore\Data_Structures\Projects\Final\cs2341_data\00a00d0edc750db4a0c299dd1ec0c6871f5a4f24.json
    /// \return A set of strings containing all words found in the document's abstract and body text.
    set<string> parseJSONFile(const string& filename);
    /// Determines if a word is entirely numbers or punctuation characters.
    /// \param str Word to potentially be added to InvertedIndex.
    /// \return True if str is entirely numeric/punctuation characters, false if not.
    bool isNumberOrPunct(const string& str);
    /// Gets the filepath's paper_id member.
    /// \param filepath The full filepath of a .json file.
    /// \return The document's member at document["paper_id"].
    string getFilename(const string& filepath);
    /// Gets the authors found in a .json file.
    /// \param filename The full filepath of a .json file.
    /// \return A set of strings containing the last names of all authors found in the document's metadata["authors"].
    set<string> getAuthors(const string& filename);
    /// Opens the metadata .csv file and checks if the file contains full text or not.
    /// \param filename The full filepath of a .json file.
    /// \return True if the file contains full text, false if not.
    bool isFullTextFile(const string& filename);
    /// Prints the file's title and all authors' first and last names.
    /// \param filename The full filepath of a .json file.
    void printInformation(const string& filename);
    /// Prints the first 300 words found in a file's body text.
    /// \param filename The full filepath of a .json file.
    void printFirst300(const string& filename);
};

#endif //SEARCH_ENGINE_DOCUMENTPROCESSOR_H
