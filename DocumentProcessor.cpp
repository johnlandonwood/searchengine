#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <locale>
#include <codecvt>
#include "DocumentProcessor.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include "include/olestem/stemming/english_stem.h"
using namespace std;
namespace rjs = rapidjson;
namespace fs = std::filesystem;
// Written by Landon Wood
// Suite of functions for processing JSON documents and the metadata .csv
// Uses RapidJSON and Oleander Stemming libraries

DocumentProcessor::DocumentProcessor() {
    string word;
    ifstream stopWordsFile;
    stopWordsFile.open("stopWords.txt");
    if (!stopWordsFile.is_open()) cout << "stopWords file was not opened" << endl;
    while (stopWordsFile >> word) { // Store a list of 636 unique stop words
        this->stopWords.insert(word);
    }
    stopWordsFile.close();
}

set<string> DocumentProcessor::parseJSONFile(const string& filename) { // Parse the given .JSON file and return a set of strings containing all its words
    rjs::Document document;
    ifstream file; // Place the text from file into a c_string, then parse
    file.open(filename);
    string temp;
    ostringstream ss;
    ss << file.rdbuf();
    temp = ss.str();
    file.close();
    const char* json = temp.c_str();
    document.Parse(json);
    if (document.HasParseError()) { // Error print snippet taken from RapidJSON documentation
        fprintf(stderr, "\nError(offset %u): %s\n", (unsigned)document.GetErrorOffset(), rjs::GetParseError_En(document.GetParseError()));
    }

    assert(document.HasMember("metadata"));     // Assert that the document has the desired members
    rjs::Value& metadata = document["metadata"];
    assert(document.HasMember("abstract"));
    assert(document.HasMember("body_text"));


    set<string> allWords; // This will store all words (after stemming) in both the abstract and body text
    string abstract;
    for (rjs::SizeType i = 0; i < document["abstract"].Size(); i++) { // Construct a string with all words in the JSON's abstract
        abstract += document["abstract"][i]["text"].GetString();
        abstract += " ";
    }
    string token;
    istringstream abstractIS(abstract);
    while (abstractIS.good()) { // Tokenize the abstract and stem its words
        abstractIS >> token;
        transform(token.begin(), token.end(), token.begin(),[](unsigned char c){ return tolower(c); }); // toLower snippet taken from an answer on https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
        wchar_t* UnicodeTextBuffer = new wchar_t[token.length()+1]; // Convert string to wstring, in order to use Oleander stemming algorithm. Taken from Oleander stemming documentation
        std::wmemset(UnicodeTextBuffer, 0, token.length()+1);
        std::mbstowcs(UnicodeTextBuffer, token.c_str(), token.length());
        wstring word = UnicodeTextBuffer;
        stemming::english_stem<> StemEnglish;
        StemEnglish(word);
        using convert_type = std::codecvt_utf8<wchar_t>; // Snippet for converting wstring back to string (so it may be added to the allWords set) taken from https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
        std::wstring_convert<convert_type, wchar_t> converter;
        std::string convertedWord = converter.to_bytes(word);
        if (stopWords.count(convertedWord) == 0 && !this->isNumberOrPunct(convertedWord)) { // If the current token is not a stop word, or not solely numbers/punctuation, add it to the final set.
            allWords.insert(convertedWord);
        }
    }

    string bodyText;
    for (rjs::SizeType i = 0; i < document["body_text"].Size(); i++) { // Construct a string with all words in the JSON's body text
        bodyText += document["body_text"][i]["text"].GetString();
        bodyText += " ";
    }
    istringstream bodyTextIS(bodyText);
    while (bodyTextIS.good()) { // Tokenize the body text and stem its words
        bodyTextIS >> token;
        transform(token.begin(), token.end(), token.begin(),[](unsigned char c){ return tolower(c); }); // toLower snippet taken from an answer on https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
        wchar_t* UnicodeTextBuffer = new wchar_t[token.length() +1 ]; // Convert string to wstring, in order to use Oleander stemming algorithm. Taken from Oleander stemming documentation
        std::wmemset(UnicodeTextBuffer, 0, token.length() + 1);
        std::mbstowcs(UnicodeTextBuffer, token.c_str(), token.length());
        wstring word = UnicodeTextBuffer;
        stemming::english_stem<> StemEnglish;
        StemEnglish(word);
        using convert_type = std::codecvt_utf8<wchar_t>; // Snippet for converting wstring back to string (so it may be added to the allWords set) taken from https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
        std::wstring_convert<convert_type, wchar_t> converter;
        std::string convertedWord = converter.to_bytes(word);
        if (stopWords.count(convertedWord) == 0 && !this->isNumberOrPunct(convertedWord)) { // If the current token is not a stop word, or not solely numbers/punctuation, add it to the final set.
            allWords.insert(convertedWord);
        }
    }
    return allWords;
}


string DocumentProcessor::getFilename(const string& filepath) { // Get the paper_id from JSON file
    rjs::Document document;
    ifstream file; // Place the text from file into a c_string, then parse
    file.open(filepath);
    string temp;
    ostringstream ss;
    ss << file.rdbuf();
    temp = ss.str();
    file.close();
    const char* json = temp.c_str();
    document.Parse(json);
    if (document.HasParseError()) { // Error print snippet taken from RapidJSON documentation
        fprintf(stderr, "\nError(offset %u): %s\n", (unsigned)document.GetErrorOffset(), rjs::GetParseError_En(document.GetParseError()));
    }
    assert(document.HasMember("paper_id"));
    if(document.HasMember("paper_id")) {
        string filename = document["paper_id"].GetString();
        return filename;
    }
    else {
        cout << "Paper ID does not exist" << endl;
    }
}

set<string> DocumentProcessor::getAuthors(const string &filename) { // Get the authors from JSON file
    rjs::Document document;
    ifstream file; // Place the text from file into a c_string, then parse
    file.open(filename);
    string temp;
    ostringstream ss;
    ss << file.rdbuf();
    temp = ss.str();
    file.close();
    const char* json = temp.c_str();
    document.Parse(json);
    if (document.HasParseError()) {
        fprintf(stderr, "\nError(offset %u): %s\n", (unsigned)document.GetErrorOffset(), rjs::GetParseError_En(document.GetParseError())); // Error print snippet taken from RapidJSON documentation
    }
    assert(document.HasMember("metadata"));
    rjs::Value& metadata = document["metadata"];
    assert(metadata.HasMember("authors"));
    set<string> authors;
    for (rjs::SizeType i = 0; i < metadata["authors"].Size(); i++) { // This loop only gets the last name of the author to be added to hash table
        string author = metadata["authors"][i]["last"].GetString();
        authors.insert(author);
    }

    return authors;
}

bool DocumentProcessor::isFullTextFile(const string& filename) { // Verify that a JSON file contains full text or not
    string CSVline;
    string desiredCSVline;
    ifstream inputcsv;
    inputcsv.open(R"(C:\Users\Owner\Desktop\Downloads\SMU\Sophomore\Data_Structures\Projects\Final\metadata-cs2341.csv)"); // Open the metadata .csv file
    if (!inputcsv.is_open()) cout << "inputCSV is not open" << endl;
    bool breakLoop = false;
    while (getline(inputcsv, CSVline)) {
        stringstream ss(CSVline);
        string token;
        while (getline(ss, token, ',')) { // Find the correct line with the paper ID we are checking
            if (token == filename) {
                desiredCSVline = CSVline;
                breakLoop = true;
                break;
            }
        }
        if(breakLoop) break;
    }

    stringstream ss2(desiredCSVline); // Tokenize the desired line
    string token2;
    while (getline(ss2, token2, ',')) {
        if (token2 == "noncomm_use_subset") { // If line contains this token, then the filename is not a full text file
            inputcsv.close();
            return false;
        }
    }
    inputcsv.close();
    return true;
}

void DocumentProcessor::printInformation(const string &filepath) { // Print out the file's title and authors
    rjs::Document document;
    ifstream file; // Place the text from file into a c_string, then parse
    file.open(filepath);
    string temp;
    ostringstream ss;
    ss << file.rdbuf();
    temp = ss.str();
    file.close();
    const char* json = temp.c_str();
    document.Parse(json);
    if (document.HasParseError()) {
        fprintf(stderr, "\nError(offset %u): %s\n", (unsigned)document.GetErrorOffset(), rjs::GetParseError_En(document.GetParseError())); // Error print snippet taken from RapidJSON documentation
    }

    assert(document.HasMember("paper_id")); // Assert that the document has the desired members
    rjs::Value& ID = document["paper_id"];
    assert(document.HasMember("metadata"));
    rjs::Value& metadata = document["metadata"];
    assert(metadata.HasMember("title"));
    assert(metadata.HasMember("authors"));


    string title = metadata["title"].GetString();
    set<string> authors;
    for (rjs::SizeType i = 0; i < metadata["authors"].Size(); i++) { // This loop only gets the last name of the author to be added to hash table
        string author = metadata["authors"][i]["first"].GetString();
        author += " ";
        author += metadata["authors"][i]["last"].GetString();
        authors.insert(author);
    }

    cout << ID.GetString() << endl;
    cout << "\tTitle: " << metadata["title"].GetString() << endl;
    cout << "\tAuthors: ";
    int authorSizeCtr = 0;
    for (const auto& it: authors) {
        authorSizeCtr++;
        if (authorSizeCtr == authors.size()) {
            cout << it;
        }
        else {
            cout << it << ", ";
        }
    }

    cout << endl;
}

void DocumentProcessor::printFirst300(const string &filename) { // Print the first 300 words in a file's body text
    rjs::Document document;
    ifstream file; // Place the text from file into a c_string, then parse
    file.open(filename);
    string temp;
    ostringstream ss;
    ss << file.rdbuf();
    temp = ss.str();
    file.close();
    const char* json = temp.c_str();
    document.Parse(json);
    if (document.HasParseError()) {
        fprintf(stderr, "\nError(offset %u): %s\n", (unsigned)document.GetErrorOffset(), rjs::GetParseError_En(document.GetParseError())); // Error print snippet taken from RapidJSON documentation
    }

    assert(document.HasMember("body_text"));

    string bodyText;
    for (rjs::SizeType i = 0; i < document["body_text"].Size(); i++) { // Construct a string with all words in the JSON's body text
        bodyText += document["body_text"][i]["text"].GetString();
        bodyText += " ";
    }

    string first300Words;
    istringstream bodyTextISS(bodyText);
    string token;
    int ctr = 0;
    while(bodyTextISS >> token) {
        if (ctr == 300) break;
        first300Words += token;
        first300Words += " ";
        ctr++;
    }
    cout << first300Words << endl << endl;

}

bool DocumentProcessor::isNumberOrPunct(const string& str) { // Check if a string is a number or punctuation. If it is, don't add it to the set of allWords
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it) || ispunct(*it)) ++it;
    return !str.empty() && it == str.end();
}


