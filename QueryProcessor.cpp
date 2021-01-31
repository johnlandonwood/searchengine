#include <locale>
#include <codecvt>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include "include/olestem/stemming/english_stem.h"
#include "QueryProcessor.h"
//written by Maria Harrison
QueryProcessor::QueryProcessor() {
    query = "";
}

QueryProcessor::QueryProcessor(string input, int numOfDocs) {
    query = input;
    totalDocsIndexed = numOfDocs;
}

vector<pair<string,int>> QueryProcessor::run(InvertedIndex InvertedIndex, HashTable<pair<string, set<string>>> hashTable, const vector<pair<string, int>>& fileWordCount) {
    bool ANDon = false;
    bool ORon = false;
    bool NOTon = false;
    bool AUTHORon = false;
    bool ANDtrue = false;
    bool ORtrue = false;
    bool NOTtrue = false;
    bool AUTHORtrue = false;
    bool WORDtrue = false;
    string oneword = "";
    string action = "";
    set<string> ANDwords;
    set<string> ORwords;
    set<string> NOTwords;
    string author = "";
    for (int i = 0; i < query.size(); i++) {
        if(i == query.size() - 1){ //last letter in query
            action += query[i];
            //action is AND
            if (action == "AND") {
                ANDon = true;
                ANDtrue = true;
                ORon = false;
                NOTon = false;
                AUTHORon = false;
            }
                //action is OR
            else if (action == "OR") {
                ORon = true;
                ORtrue = true;
                ANDon = false;
                NOTon = false;
                AUTHORon = false;
            }
                //action is NOT
            else if (action == "NOT") {
                NOTon = true;
                NOTtrue = true;
                ANDon = false;
                ORon = false;
                AUTHORon = false;
            }
                //action is AUTHOR
            else if (action == "AUTHOR") {
                AUTHORon = true;
                AUTHORtrue = true;
                ANDon = false;
                ORon = false;
                NOTon = false;
            } else { //action is a word
                if (ANDon == true) {
                    ANDwords.insert(action);
                    action = "";
                } else if (ORon == true) {
                    ORwords.insert(action);
                    action = "";
                } else if (NOTon == true) {
                    NOTwords.insert(action);
                    action = "";
                } else if (AUTHORon == true) {
                    author = action;
                    action = "";
                } else { //only one word
                    WORDtrue = true;
                    oneword = action;
                    action = "";
                }
            }
        }
        else if (query[i] == ' ') {
            //action is AND
            if (action == "AND") {
                ANDon = true;
                ANDtrue = true;
                ORon = false;
                NOTon = false;
                AUTHORon = false;
                action = "";
            }
                //action is OR
            else if (action == "OR") {
                ORon = true;
                ORtrue = true;
                ANDon = false;
                NOTon = false;
                AUTHORon = false;
                action = "";
            }
                //action is NOT
            else if (action == "NOT") {
                NOTon = true;
                NOTtrue = true;
                ANDon = false;
                ORon = false;
                AUTHORon = false;
                action = "";
            }
                //action is AUTHOR
            else if (action == "AUTHOR") {
                AUTHORon = true;
                AUTHORtrue = true;
                ANDon = false;
                ORon = false;
                NOTon = false;
                action = "";
            } else { //action is a word
                if (ANDon == true) {
                    ANDwords.insert(action);
                    action = "";
                } else if (ORon == true) {
                    ORwords.insert(action);
                    action = "";
                } else if (NOTon == true) {
                    NOTwords.insert(action);
                    action = "";
                } else if (AUTHORon == true) {
                    author = action;
                    action = "";
                } else { //only one word
                    WORDtrue = true;
                    oneword = action;
                    action = "";
                }
            }
        } else { //construct the word
            action += query[i];
        }
    }

    set<string> stemmedANDwords;
    if(ANDtrue == true){ //stem words in AND set
        for (const auto& it: ANDwords) {
            string temp = it;
            transform(temp.begin(), temp.end(), temp.begin(),[](unsigned char c){ return tolower(c); });
            wchar_t* UnicodeTextBuffer = new wchar_t[temp.length()+1];
            std::wmemset(UnicodeTextBuffer, 0, temp.length()+1);
            std::mbstowcs(UnicodeTextBuffer, temp.c_str(), temp.length());
            wstring word = UnicodeTextBuffer;
            stemming::english_stem<> StemEnglish;
            StemEnglish(word);
            using convert_type = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_type, wchar_t> converter;
            std::string convertedword = converter.to_bytes(word);
            stemmedANDwords.insert(convertedword);
        }
    }

    set<string> stemmedORwords;
    if(ORtrue == true){ // stem words in OR set
        for (const auto& it: ORwords) {
            string temp = it;
            transform(temp.begin(), temp.end(), temp.begin(),[](unsigned char c){ return tolower(c); });
            wchar_t* UnicodeTextBuffer = new wchar_t[temp.length()+1];
            std::wmemset(UnicodeTextBuffer, 0, temp.length()+1);
            std::mbstowcs(UnicodeTextBuffer, temp.c_str(), temp.length());
            wstring word = UnicodeTextBuffer;
            stemming::english_stem<> StemEnglish;
            StemEnglish(word);
            using convert_type = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_type, wchar_t> converter;
            std::string convertedword = converter.to_bytes(word);
            stemmedORwords.insert(convertedword);
        }
    }

    set<string> stemmedNOTwords;
    if(NOTtrue == true){ //stem words in NOT set
        for (const auto& it: NOTwords) {
            string temp = it;
            transform(temp.begin(), temp.end(), temp.begin(),[](unsigned char c){ return tolower(c); });
            wchar_t* UnicodeTextBuffer = new wchar_t[temp.length()+1];
            std::wmemset(UnicodeTextBuffer, 0, temp.length()+1);
            std::mbstowcs(UnicodeTextBuffer, temp.c_str(), temp.length());
            wstring word = UnicodeTextBuffer;
            stemming::english_stem<> StemEnglish;
            StemEnglish(word);
            using convert_type = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_type, wchar_t> converter;
            std::string convertedword = converter.to_bytes(word);
            stemmedNOTwords.insert(convertedword);
        }
    }

    string convertedword = "";
    if(WORDtrue == true){ //stem the one word
        transform(oneword.begin(), oneword.end(), oneword.begin(),[](unsigned char c){ return tolower(c); });
        wchar_t* UnicodeTextBuffer = new wchar_t[oneword.length()+1];
        std::wmemset(UnicodeTextBuffer, 0, oneword.length()+1);
        std::mbstowcs(UnicodeTextBuffer, oneword.c_str(), oneword.length());
        wstring word = UnicodeTextBuffer;
        stemming::english_stem<> StemEnglish;
        StemEnglish(word);
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        convertedword = converter.to_bytes(word);
    }


    //if one word is entered into query
    //find the articles that contain that one word
    set<string> finalDocs;
    if(WORDtrue == true){
        if(InvertedIndex.wordInIndex(convertedword) == true){
            vector<pair<string, int>> documents =  InvertedIndex.getDocs(convertedword);
            for(int i = 0; i < documents.size(); i++){
                int tf = 0;
                int idf = 0;
                int tfidf = 0;
                if(fileExist(documents[i].first)){
                    int fileNum = getFilePosition(documents[i].first);
                    tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                    idf = log(totalDocsIndexed / documents.size());
                    tfidf = tf * idf;
                    documentWeights[fileNum].second += tfidf;
                }
                else{
                    tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                    idf = log(totalDocsIndexed / documents.size());
                    tfidf = tf * idf;
                    pair<string, int> tempPair = make_pair(documents[i].first, tfidf);
                    documentWeights.push_back(tempPair);
                }
                finalDocs.insert(documents[i].first);

            }
        }
        else {
            //cout << "Query word " << convertedword << " is not in index." << endl;
        }
    }

    if(ANDtrue == true){
        set<string>::iterator iterator = stemmedANDwords.begin();
        bool wordDoesNotExist = false;
        for (const auto& iter: stemmedANDwords) {
            if (InvertedIndex.wordInIndex(iter) == false) {
                wordDoesNotExist = true;
            }
        }
        if (wordDoesNotExist == false) {
            vector<pair<string,int>> documents = InvertedIndex.getDocs(*iterator);
            vector<string> result;
            for(int i = 0; i < documents.size(); i++){
                result.push_back(documents[i].first);
            }

            for(set<string>::iterator it = stemmedANDwords.begin(); it != stemmedANDwords.end(); it++){
                if (InvertedIndex.wordInIndex(*it) == false) {
                    wordDoesNotExist = true;
                    cout << *it << " is not in the index." << endl;
                    break;
                }
                else {
                    //grab documents from current word in set

                    vector<string> temp;
                    if(it != stemmedANDwords.begin()){
                        vector<pair<string, int>> documents = InvertedIndex.getDocs(*it);
                        for(int i = 0; i < documents.size(); i++){
                            temp.push_back(documents[i].first);
                            int tf = 0;
                            int idf = 0;
                            int tfidf = 0;
                            if(fileExist(documents[i].first)){
                                int fileNum = getFilePosition(documents[i].first);
                                tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                                idf = log(totalDocsIndexed / documents.size());
                                tfidf = tf * idf;
                                documentWeights[fileNum].second += tfidf;
                            }
                            else{
                                tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                                idf = log(totalDocsIndexed / documents.size());
                                tfidf = tf * idf;
                                pair<string, int> tempPair = make_pair(documents[i].first, tfidf);
                                documentWeights.push_back(tempPair);
                            }
                        }

                        std::sort(result.begin(), result.end());
                        std::sort(temp.begin(), temp.end());
                        std::vector<string>::iterator theIT;
                        theIT = std::set_intersection(result.begin(), result.end(), temp.begin(), temp.end(), result.begin());
                        result.resize(theIT-result.begin());
                    }
                }



            }

            for(int i = 0; i < result.size(); i++){
                finalDocs.insert(result[i]);
            }

        }


    }



    //iterate through OR words
    //add all documents to one set
    if(ORtrue == true){
        set<string> existingORwords;
        for (const auto& it: stemmedORwords) {
            if (InvertedIndex.wordInIndex(it) == true) existingORwords.insert(it);
        }
        for(set<string>::iterator it = existingORwords.begin(); it != existingORwords.end(); it++){
            vector<pair<string, int>> documents =  InvertedIndex.getDocs(*it);
            for(int i = 0; i < documents.size(); i++){
                finalDocs.insert(documents[i].first);
                int tf = 0;
                int idf = 0;
                int tfidf = 0;
                if(fileExist(documents[i].first)){
                    int fileNum = getFilePosition(documents[i].first);
                    tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                    idf = log(totalDocsIndexed / documents.size());
                    tfidf = tf * idf;
                    documentWeights[fileNum].second += tfidf;
                }
                else{
                    tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                    idf = log(totalDocsIndexed / documents.size());
                    tfidf = tf * idf;
                    pair<string, int> tempPair = make_pair(documents[i].first, tfidf);
                    documentWeights.push_back(tempPair);
                }
            }
        }
    }


    if(NOTtrue == true){
        set<string> existingNOTwords;
        for (const auto& it: stemmedNOTwords) {
            if (InvertedIndex.wordInIndex(it) == true) existingNOTwords.insert(it);
        }
        vector<string> result;
        for(set<string>::iterator it = finalDocs.begin(); it != finalDocs.end(); it++){
            result.push_back(*it);
        }

        for(set<string>::iterator it = existingNOTwords.begin(); it != existingNOTwords.end(); it++){
            //grab documents from current word in set
            vector<string> temp;
            vector<pair<string, int>> documents = InvertedIndex.getDocs(*it);
            for(int i = 0; i < documents.size(); i++) {
                int tf = 0;
                int idf = 0;
                int tfidf = 0;
                if(fileExist(documents[i].first)){
                    int fileNum = getFilePosition(documents[i].first);
                    tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                    idf = log(totalDocsIndexed / documents.size());
                    tfidf = tf * idf;
                    documentWeights[fileNum].second += tfidf;
                }
                else{
                    tf = documents[i].second / findFileWordCount(documents[i].first, fileWordCount);
                    idf = log(totalDocsIndexed / documents.size());
                    tfidf = tf * idf;
                    pair<string, int> tempPair = make_pair(documents[i].first, tfidf);
                    documentWeights.push_back(tempPair);
                }
                temp.push_back(documents[i].first);
            }

            std::sort(result.begin(), result.end());
            std::sort(temp.begin(), temp.end());
            std::vector<string>::iterator theIT;
            theIT = std::set_difference(result.begin(), result.end(), temp.begin(), temp.end(), result.begin());
            result.resize(theIT-result.begin());

        }
        finalDocs.clear();
        for(int i = 0; i < result.size(); i++) {
            finalDocs.insert(result[i]);
        }
    }

    if(AUTHORtrue == true){
        vector<string> result;
        for(set<string>::iterator it = finalDocs.begin(); it != finalDocs.end(); it++){
            result.push_back(*it);
        }
        if(hashTable.authorExists(author)){
            set<string> authorDocs = hashTable[author].second;
            vector<string> author;
            for(set<string>::iterator it = authorDocs.begin(); it != authorDocs.end(); it++){
                author.push_back(*it);
            }
            std::sort(result.begin(), result.end());
            std::sort(author.begin(), author.end());
            vector<string> thefinal;
            std::vector<string>::iterator it;
            it = std::set_intersection(author.begin(), author.end(), result.begin(), result.end(), result.begin());
            result.resize(it-result.begin());

            finalDocs.clear();
            for(int i = 0; i < result.size(); i++){
                finalDocs.insert(result[i]);
            }
        }
        else{
            //cout << "Query " << query << " cannot be found because author " << author << " does not exist." << endl;
            vector<pair<string,int>> empty;
            return empty;
        }
    }

    vector<pair<string,int>> resultDocs;
    for(int i = 0; i < documentWeights.size(); i++){
        for(set<string>:: iterator it = finalDocs.begin(); it != finalDocs.end(); it++){
            if(documentWeights[i].first == *it){
                resultDocs.push_back(documentWeights[i]);
            }
        }
    }


    //sort documents by relevancy ranking
    if (resultDocs.empty()) goto finish;
    for (int i = 0; i < resultDocs.size() - 1; i++) {
        for (int j = 0; j < resultDocs.size()-i-1; j++) {
            if (resultDocs[j].second < resultDocs[j+1].second)  {
                pair<string, int> temp = resultDocs[j];
                resultDocs[j] = resultDocs[j+1];
                resultDocs[j+1] = temp;
            }
        }
    }

    finish:
    vector<pair<string, int>> trimmedResultDocs;
    for (int i = 0; i < 15; i++) { // Hardcoded 15 will segfault?
        if (i == resultDocs.size()) break;
        trimmedResultDocs.push_back(resultDocs[i]);
    }

    return trimmedResultDocs;
}

int QueryProcessor::findFileWordCount(const string& filename, const vector<pair<string, int>>& fileWordCount) {
    int wordCount = 0;
    for (int i = 0; i < fileWordCount.size(); i++) {
        if (fileWordCount[i].first == filename) {
            wordCount = fileWordCount[i].second;
            return wordCount;
        }
    }
    return -1;
}

bool QueryProcessor::fileExist(string filename) {
    bool fileExist = false;
    for(int i = 0; i < documentWeights.size(); i++){
        if(documentWeights[i].first == filename){
            return true;
        }
    }
    return false;
}

int QueryProcessor::getFilePosition(string filename) {
    int num = 0;
    for(int i = 0; i < documentWeights.size(); i++){
        if(documentWeights[i].first == filename){
            num = i;
        }
    }
    return num;
}
