#include "InvertedIndex.h"
//written by Maria Harrison

InvertedIndex::InvertedIndex() {
    numOfNodes = 0;
}


void InvertedIndex::addWord(std::string word, string document) {
    //check if word is already in avl tree
    if(wordInIndex(word) == true){
        //check if document exists
        if(invertedIndexTree.findNode(word).docInEntry(document) == false){
            //add document to set of documents in word node
            invertedIndexTree.findNode(word).addDoc(document);
        }
            //if document does exist increase number
        else{
            invertedIndexTree.findNode(word).increaseDoc(document);
        }
    }
    else{
        //word does not exist
        //create new index entry
        InvertedIndexEntry temp = InvertedIndexEntry(word);
        //add document to index entry
        temp.addDoc(document);
        invertedIndexTree.insert(temp, word);
        numOfNodes++;
    }
}

bool InvertedIndex::wordInIndex(string word) {
    if(invertedIndexTree.dataInTree(word) == true){
        return true;
    }
    else{
        return false;
    }
}

vector<pair<string, int>> InvertedIndex::getDocs(string word) {
    return invertedIndexTree.findNode(word).getDocs();
}

int InvertedIndex::getNumOfNodes() {
    return numOfNodes;
}

vector<string> InvertedIndex::getTop50Words() {
    vector<InvertedIndexEntry> allNodesInTree = invertedIndexTree.returnNodes();
    vector<pair<string, int>> top50Words;
    for (InvertedIndexEntry it: allNodesInTree) {
        pair<string, int> tempPair = make_pair(it.getWord(), it.getWordFrequency());
        top50Words.push_back(tempPair);
    }
    for (int i = 0; i < top50Words.size() - 1; i++) {
        for (int j = 0; j < top50Words.size()-i-1; j++) {
            if (top50Words[j].second < top50Words[j+1].second)  {
                pair<string, int> temp = top50Words[j];
                top50Words[j] = top50Words[j+1];
                top50Words[j+1] = temp;
            }
        }
    }

    vector<string> top50MostFrequentWords;
    for (int i = 0; i < 50; i++) {
        top50MostFrequentWords.push_back(top50Words[i].first);
    }
    return top50MostFrequentWords;
}

void InvertedIndex::deleteIndex(){
    invertedIndexTree.deleteTree();
    numOfNodes = 0;
}

