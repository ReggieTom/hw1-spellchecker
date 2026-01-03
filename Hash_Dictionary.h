#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <ostream>

using std::string;
using std::ostream;

class Dictionary {
private:
    // Hash table storing pointers to strings (Dictionary owns the strings).
    // Implemented with open addressing + double hashing.
    string** table;
    int tableSizeIndex;
    int tableSize;
    int numEntries;

    // Hash function from Figure 5.4 (Section 5.2).
    // Do not change the parameters or return type.
    static int hash(const string& key, int tableSize);

    void allocateTable(int sizeIndex);
    void rehash();

    int secondaryPrime() const;
    int findIndex(const string& key) const;      // index of key OR first empty slot in its probe sequence
    int findInsertIndex(const string& key) const;
    static void insertInternal(string* word, string** target, int targetSize, int targetSecondaryPrime);

public:
    Dictionary();
    ~Dictionary();

    // Disable copying (same as Part 1)
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;

    /* ===== Public interface (MUST NOT CHANGE) ===== */
    void insert(string* word);
    bool contains(const string& word) const;

    void print(ostream& out) const;
    void printStructure(ostream& out) const;
};

#endif
