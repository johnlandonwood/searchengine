#ifndef SEARCH_ENGINE_HARRISON_WOOD_HASHTABLE_H
#define SEARCH_ENGINE_HARRISON_WOOD_HASHTABLE_H
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <iostream>
// Written by Landon Wood
// Hash table with separate chaining
using namespace std;

/// Written by Landon Wood.
/// Hash table with separate chaining.
template <typename T> class HashTable {
private:
    /// A vector of templated vectors where values are hashed to.
    vector<vector<T>> table;
    /// The number of buckets in the hash table.
    int numBuckets;
public:
    /// Default constructor - creates 10 buckets.
    HashTable() {
        numBuckets = 10;
        table = vector<vector<T>>(numBuckets);
    }
    /// Parameterized constructor.
    /// \param numBuckets Number of buckets the hash table will have.
    HashTable(int numBuckets) {
        this->numBuckets = numBuckets;
        table = vector<vector<T>>(numBuckets);
    }

    /// Removes all values in the hash table's inner vectors.
    void clear() { // Remove all the values in the inner vectors
        for (int i = 0; i < numBuckets; i++) {
            table[i].clear();
        }
    }

    /// Gets the hash index for a pair.
    /// \param data Templated value.
    /// \return An integer corresponding to the bucket the data will be mapped to.
    int getHashIndex(T data) {
        return pairHashFunction(data) % table.size();
    }

    /// A function to hash pairs.
    /// \param p Pair containing a string and set of strings.
    /// \return  An integer corresponding to the bucket the string will be mapped to.
    int pairHashFunction(pair<string, set<string>> p) {
        int seed = 131;
        unsigned long hash = 0;
        for (int i = 0; i < p.first.length(); i++) {
            hash = (hash * seed) + p.first[i];
        }
        return hash % numBuckets;
    }

    /// A function to hash strings.
    /// Taken from https://stackoverflow.com/questions/8317508/hash-function-for-a-string
    /// \param str The string to be hashed.
    /// \return An integer corresponding to the bucket the string will be mapped to.
    int stringHashFunction(string str) {
        int seed = 131;
        unsigned long hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = (hash * seed) + str[i];
        }
        return hash % numBuckets;
    }

    /// Generic templated hash function, using std::hash.
    /// \param data Templated value.
    /// \return An integer corresponding to the bucket the value will be mapped to.
    int hashFunction(T data) { // Generic templated hash function - does not work with pairs
        return std::hash<T>()(data);
    }

    /// Inserts a value in the hash table.
    /// \param data The value to be inserted.
    void insert(T data) {
        if (!this->exists(data)) {
            table[getHashIndex(data)].push_back(data);
        }
        else {
            cout << "Duplicate value entered to hash table insert, not inserting" << endl;
        }
    }

    /// Determines whether or not a value exists in the hash table.
    /// \param data Templated value.
    /// \return True if the value is found, false if not.
    bool exists(T data) {
        int index = getHashIndex(data);
        for (int i = 0; i < table[index].size(); i++) {
            if (table[index][i] == data) {
                return true;
            }
        }
        return false;
    }

    /// Determines whether or not a particular author exists in the hash table.
    /// \param author The author's last name.
    /// \return True if the author is in the hash table, false if not.
    bool authorExists(string author) { // Specifically for table of pairs - check if author is already present
        int index = stringHashFunction(author);
        for (int i = 0; i < table[index].size(); i++) {
            if (table[index][i].first == author) {
                return true;
            }
        }
        return false;
    }

    /// Finds the location where an author exists in the hash table.
    /// \param key An author's last name.
    /// \return The contents of the bucket where the key exists
    pair<string, set<string>>& operator[](string key) { // Specifically for table of pairs - return the bucket where the key exists
        int index = stringHashFunction(key);
        for (int i = 0; i < table[index].size(); i++) {
            if (table[index][i].first == key) {
                return table[index][i];
            }
        }
    }

    /// Gets the total number of values in the hash table.
    /// \return An integer containing the number of values in all buckets.
    int getTotalValues() {
        int ctr = 0;
        for (int i = 0; i < numBuckets; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                ctr++;
            }
        }
        return ctr;
    }

    /// Prints the contents of the hash table.
    void print() {
        for (int i = 0; i < table.size(); i++) {
            cout << i << ": ";
            for (const auto& it1: table[i]) {
                cout << it1.first << " -> ";
                for (auto it2 = it1.second.begin(); it2 != it1.second.end(); it2++) {
                    cout << *it2 << " ";
                }
            }
            cout << endl;
        }
    }

    /// Determines whether or not the hash table is completely empty.
    /// \return True if all buckets are completely empty, false if not.
    bool isEmpty() { // If no bucket has any values mapped to it, return true
        int emptyBuckets = 0;
        for (int i = 0; i < numBuckets; i++) {
            if (table[i].size() == 0) emptyBuckets++;
        }
        if (emptyBuckets == numBuckets) return true;
        return false;
    }

};

#endif //SEARCH_ENGINE_HARRISON_WOOD_HASHTABLE_H
