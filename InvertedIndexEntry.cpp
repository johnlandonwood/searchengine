#include "InvertedIndexEntry.h"
#include <iostream>
//written by Maria Harrison

InvertedIndexEntry::InvertedIndexEntry(){
    word = "";
}

InvertedIndexEntry::InvertedIndexEntry(const std::string &input) {
    word = input;
}

string InvertedIndexEntry::getWord() {
    return word;
}

vector<pair<string, int>> InvertedIndexEntry::getDocs() {
    return documents;
}

void InvertedIndexEntry::addDoc(std::string document) {
    documents.push_back(make_pair(document,1));
}

void InvertedIndexEntry::printDocs() {
    for(int i = 0; i < documents.size(); i++){
        cout << documents[i].first << " num: ";
        cout << documents[i].second << endl;
    }
}

bool InvertedIndexEntry::docInEntry(string document) {
    for(int i = 0; i < documents.size(); i++){
        if(documents[i].first == document){
            return true;
        }
    }
    return false;
}

void InvertedIndexEntry::increaseDoc(string document) {
    int loc = 0;
    for(int i = 0; i < documents.size();i++){
        if(documents[i].first == document){
            loc = i;
        }
    }

    int num = documents[loc].second++;
    documents[loc].second = num;
}
int InvertedIndexEntry::getWordFrequency() {
    int count = 0;
    for (int i = 0; i < documents.size(); i++) {
        count += documents[i].second;
    }
    return count;
}