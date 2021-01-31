#include <iostream>
#include <string>
#include <set>
#include <filesystem>
#include "UserInterface.h"
#include "DocumentProcessor.h"
using namespace std;
namespace fs = std::filesystem;
// Written by Landon Wood
// User Interface to take in user input and communicate with search engine accordingly
// landon desktop data set: R"(C:\Users\Owner\Desktop\Downloads\SMU\Sophomore\Data_Structures\Projects\Final\cs2341_data)"
// landon desktop csv file: R"(C:\Users\Owner\Desktop\Downloads\SMU\Sophomore\Data_Structures\Projects\Final\metadata-cs2341.csv)"
// landon laptop data set: C:\cygwin64\home\landl\CS2341\cs2341_project_data\cs2341_data
// landon laptop csv file: C:\cygwin64\home\landl\CS2341\cs2341_project_data\metadata-cs2341.csv

UserInterface::UserInterface() {
    this->totalNumFilesIndexed = 0;
    this->avgWordsIndexedPerFile = 0.0;
    this->totalUniqueWordsIndexed = 0;
    this->totalNumUniqueAuthors = 0;
}

void UserInterface::run() {
    char input;
    cout << "Welcome to Maria and Landon's Search Engine." << endl;
    cout << "Press 1 to clear the index and author hash table" << endl;
    cout << "Press 2 to populate the index and author hash table from scratch, and create new persistence files" << endl;
    cout << "Press 3 to load the existing persistence files" << endl;
    cout << "Press 4 to enter a search query" << endl;
    cout << "Press 5 to output engine statistics" << endl;
    cout << "Press Q or q to quit." << endl;
    cout << "Enter input: ";
    while (cin >> input) {
        if (input == 'Q' || input == 'q') {
            return;
        }
        else if (input == '1') { // Clear index, author hash table, and saved engine statistics
            cout << "Clearing hash table and index..." << endl;
            this->indexHandler.getHashTable().clear();
            this->indexHandler.clearIndex();
            this->totalNumFilesIndexed = 0;
            this->avgWordsIndexedPerFile = 0.0;
            this->totalUniqueWordsIndexed = 0;
            this->totalNumUniqueAuthors = 0;
            this->top50FrequentWords.clear();
            cout << "Hash table and index cleared." << endl;
            cout << "Enter input: ";
        }
        else if (input == '2') { // Populate index and hash table from scratch and create new persistence files
            cout << "Populating index, author hash table, and persistence files..." << endl;
            ofstream newWordPersistenceFile; // Three persistence files - one for words, one for authors, and one for engine statistics
            newWordPersistenceFile.open("wordPersistenceFile.txt");
            ofstream newAuthorPersistenceFile;
            newAuthorPersistenceFile.open("authorPersistenceFile.txt");
            ofstream newStatsPersistenceFile;
            newStatsPersistenceFile.open("statsPersistenceFile.txt");
            DocumentProcessor DP; // Document processor object to parse JSON files
            fs::path filepath = R"(C:\Users\Owner\Desktop\Downloads\SMU\Sophomore\Data_Structures\Projects\Final\cs2341_data)";
            int ctr = 0;
            int tempTotalNumFilesIndexed = 0;
            float tempAvgWordsIndexedPerFile = 0.0;
            int tempWordsIndexedPerFile = 0;
            set<string> tempTop50FrequentWords;
            for (const auto& dirEntry: fs::directory_iterator(filepath)) { // Go through each file in the directory, adding words to index and authors to hash table
               // if (ctr == 1000) break;
                string filename = DP.getFilename(dirEntry.path());
                if (DP.isFullTextFile(filename)) { // If the file contains full text, parse it and add its words/authors to index/hash table
                    set<string> temp = DP.parseJSONFile(dirEntry.path());
                    this->indexHandler.addFile(filename, temp.size()); // To be used in TF-IDF ranking
                    tempWordsIndexedPerFile += temp.size();
                    for (const auto& it: temp) {
                        this->indexHandler.addWord(it, filename);
                        newWordPersistenceFile << it << "," << filename << '\n'; // Write new word and filename to word persistence file
                    }
                    tempTotalNumFilesIndexed++; // Increment the statistic for the total number of articles indexed
                    set<string> files;
                    temp = DP.getAuthors(dirEntry.path()); // Get the authors from current document
                    for (const auto& currAuthor: temp) { // Add authors in current document to the hash table if they don't already exist in it
                        if (!this->indexHandler.getHashTable().authorExists(currAuthor)) {
                            files.insert(filename);
                            pair<string, set<string>> tempPair = make_pair(currAuthor, files);
                            this->indexHandler.addAuthor(tempPair);
                            newAuthorPersistenceFile << currAuthor << "," << filename << '\n'; // Write new author and filename to author persistence file
                        }
                        else {
                            this->indexHandler.getHashTable()[currAuthor].second.insert(filename);
                            newAuthorPersistenceFile << currAuthor << "," << filename << '\n';
                        }
                    }
                }
                //ctr++;
            }

            // Finalize engine statistics and write them to stat persistence file
            this->totalNumFilesIndexed = tempTotalNumFilesIndexed;
            tempAvgWordsIndexedPerFile = (static_cast<float>(tempWordsIndexedPerFile) / static_cast<float>(tempTotalNumFilesIndexed));
            this->avgWordsIndexedPerFile = tempAvgWordsIndexedPerFile;
            this->totalUniqueWordsIndexed = this->indexHandler.getIndex().getNumOfNodes();
            this->totalNumUniqueAuthors = this->indexHandler.getHashTable().getTotalValues();
            this->top50FrequentWords = this->indexHandler.getTop50FrequentWords();

            newStatsPersistenceFile << this->totalNumFilesIndexed << '\n';
            newStatsPersistenceFile << this->avgWordsIndexedPerFile << '\n';
            newStatsPersistenceFile << this->totalUniqueWordsIndexed << '\n';
            newStatsPersistenceFile << this->totalNumUniqueAuthors << '\n';
            for (const auto& it: top50FrequentWords) {
                newStatsPersistenceFile << it << '\n';
            }

            newWordPersistenceFile.close();
            newAuthorPersistenceFile.close();
            newStatsPersistenceFile.close();
            cout << "Index, authors hash table, and persistence files populated." << endl;
            cout << "Enter input: ";
        }
        else if (input == '3') { // Load persistence files from memory
            bool persistenceLoaded = false;
            this->savedWordPersistenceFile.open("wordPersistenceFile.txt"); // Open the saved persistence files
            this->savedAuthorPersistenceFile.open("authorPersistenceFile.txt");
            this->savedStatsPersistenceFile.open("statsPersistenceFile.txt");
            if (this->savedWordPersistenceFile.is_open() && this->savedAuthorPersistenceFile.is_open() && this->savedStatsPersistenceFile.is_open()) {
                cout << "Populating index and author hash table with persistence files..." << endl;
                this->indexHandler.loadWordPersistence(this->savedWordPersistenceFile); // Add their words and authors to the index and hash table
                this->indexHandler.loadAuthorPersistence(this->savedAuthorPersistenceFile);
                this->loadStatsPersistence(this->savedStatsPersistenceFile); // Add stats to the user interface
                this->savedWordPersistenceFile.close();
                this->savedAuthorPersistenceFile.close();
                this->savedStatsPersistenceFile.close();
                persistenceLoaded = true;
            }
            if (persistenceLoaded) cout << "Index and author hash table populated from persistence files." << endl;
            else cout << "At least one of the three persistence files does not exist. Run option 2 to populate the index, hash table, and create new persistence files." << endl;
            cout << "Enter input: ";
        }
        else if (input == '4') { // Run query processor methods based on user input
            if (this->indexHandler.getIndex().getNumOfNodes() == 0 && this->indexHandler.getHashTable().isEmpty()) { // Don't allow the user to query an empty index / hash table
                cout << "The index and hash table are empty. Please run option 2 or 3 to populate them first." << endl;
            }
            else {
                string query;
                cout << "Enter search query: ";
                cin.ignore();
                getline(cin, query);
                vector<pair<string, int>> resultDocs = indexHandler.processQuery(query, totalNumFilesIndexed); // Find at most 15 documents based on the query, ordered by TF-IDF ranking
                if (resultDocs.empty()) { // If the query returns no documents, do nothing
                    cout << "No documents found matching query: " << query << endl;
                }
                else { // If the query result is not empty, output the documents and their relevant info
                    vector<string> resultDocFullPaths;
                    DocumentProcessor DP;
                    string fpath = R"(C:\Users\Owner\Desktop\Downloads\SMU\Sophomore\Data_Structures\Projects\Final\cs2341_data)";
                    fs::path filepath = R"(C:\Users\Owner\Desktop\Downloads\SMU\Sophomore\Data_Structures\Projects\Final\cs2341_data)";
                    cout << "Top " << resultDocs.size() << " most relevant documents:" << endl << endl;
                    for (int i = 0; i != resultDocs.size(); i++) { // Print out title and authors for each of the 15 docs
                        string fullPath = fpath; // Create a string representing the file's full path (not just paper ID) - necessary for printing 300 words
                        fullPath += "\\";
                        fullPath += resultDocs[i].first;
                        fullPath += ".json";
                        for (const auto& dirEntry: fs::directory_iterator(filepath)) {
                            if (resultDocs[i].first == DP.getFilename(dirEntry.path())) {
                                resultDocFullPaths.push_back(fullPath);
                                cout << i + 1 << ".\t";
                                DP.printInformation(dirEntry.path()); // Print the document's title and authors
                                break;
                            }
                        }
                    }
                    cout << endl <<  "Would you like to print the first 300 words of any of the above articles?" << endl;
                    cout << "Enter y for yes, or any other key for no: ";
                    cin >> input;
                    if (input == 'y') { // User can now print first 300 words of any document the query returned
                        int numDocument;
                        cout << "Enter a number 1 - " << resultDocs.size()<< " to specify which document: ";
                        inputOutOfBounds:
                        cin >> numDocument;
                        enterDoc:
                        if (numDocument < 1 || numDocument > resultDocs.size()) {
                            cout << "Your input is out of bounds. Please try again with a number 1 - " << resultDocs.size() << ": ";
                            goto inputOutOfBounds;
                        }
                        else {
                            cout << endl << "Document " << numDocument << " (" << resultDocs[numDocument - 1].first << ") first 300 words: " << endl;
                            DP.printFirst300(resultDocFullPaths[numDocument - 1]);
                            cout << "If you would like to print the first 300 words of another document, enter a number 1 - " << resultDocs.size() << " again. If not, enter 0: ";
                            cin >> numDocument;
                            if (numDocument == 0) {
                                goto option4End;
                            }
                            else goto enterDoc;
                        }
                    }
                }
            }
            option4End:
            cout << "Enter input: ";
        }
        else if (input == '5') { // Output the engine's current statistics
            if (this->totalNumFilesIndexed == 0 && this->avgWordsIndexedPerFile == 0.0 && this->totalUniqueWordsIndexed == 0 && this->totalNumUniqueAuthors == 0 && this->top50FrequentWords.empty()) {
                cout << "All statistics fields are empty. Please run option 2 or 3 before running option 5." << endl;
            }
            else {
                cout << "Total number of individual articles indexed: " << this->totalNumFilesIndexed << endl;
                cout << "Average number of words indexed per article (after stemming and stop word removal): " << this->avgWordsIndexedPerFile << endl;
                cout << "Total number of unique words indexed (after stemming and stop word removal): " << this->totalUniqueWordsIndexed << endl;
                cout << "Total number of unique authors: " << this->totalNumUniqueAuthors << endl;
                cout << "Top 50 most frequent words (after stemming and stop word removal): " << endl;
                int i = 1;
                for (const auto& it: top50FrequentWords) { //FIXME: change formatting to output 10 words on one line?
                    cout << i << ". " << it << " ";
                    i++;
                }
            }
            cout << endl;
            cout << "Enter input: ";
        }
        else {
            cout << "Invalid input entered." << endl;
            cout << "Press 1 to clear the index and author hash table" << endl;
            cout << "Press 2 to populate the index and author hash table from scratch, and create new persistence files" << endl;
            cout << "Press 3 to load the existing persistence files" << endl;
            cout << "Press 4 to enter a search query" << endl;
            cout << "Press 5 to output engine statistics" << endl;
            cout << "Press Q or q to quit." << endl;
            cout << "Enter input: ";
        }
    }
}

void UserInterface::loadStatsPersistence(ifstream &statsPersistenceFile) { // Load persistence file into UserInterface object
    string line;
    int ctr = 1;
    while(getline(statsPersistenceFile, line)) {
        if (isdigit(line[0])) {  // If the first character of the line is a digit, then it is one of the first four numerical statistics.
            if (ctr == 1) {
                this->totalNumFilesIndexed = stoi(line);
            }
            else if (ctr == 2) {
                this->avgWordsIndexedPerFile = stof(line);
            }
            else if (ctr == 3) {
                this->totalUniqueWordsIndexed = stoi(line);
            }
            else if (ctr == 4) {
                this->totalNumUniqueAuthors = stoi(line);
            }
        }
        else if (ctr > 4 && !line.empty()) { // Get the top 50 words in the file and add them to the vector<string>.
            this->top50FrequentWords.push_back(line);
        }
        ctr++;
    }
}
