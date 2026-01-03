#include "Dictionary.h"
#include <algorithm>
#include <vector>

using std::vector;

namespace {
// Table sizes (primes) and corresponding secondary primes for double hashing.
constexpr int TABLE_SIZES[] = {
    101, 211, 431, 863, 1733, 3469, 6947, 13901, 27803, 55609, 111227, 222461, 444929, 889871
};
constexpr int SECONDARY_PRIMES[] = {
    97, 199, 421, 859, 1723, 3467, 6917, 13883, 27799, 55603, 111217, 222437, 444901, 889829
};
constexpr int NUM_SIZES = static_cast<int>(sizeof(TABLE_SIZES) / sizeof(TABLE_SIZES[0]));
} // namespace

/* ============================================================
   Constructors / Destructors
   ============================================================ */

Dictionary::Dictionary() : table(nullptr), tableSizeIndex(0), tableSize(0), numEntries(0) {
    allocateTable(0);
}

Dictionary::~Dictionary() {
    if (table != nullptr) {
        for (int i = 0; i < tableSize; ++i) {
            delete table[i];
            table[i] = nullptr;
        }
        delete[] table;
        table = nullptr;
    }
}

/* ============================================================
   Hashing helpers
   ============================================================ */

int Dictionary::hash(const string& key, int tableSizeParam) {
    // Figure 5.4 (Weiss): polynomial rolling hash (base 37)
    unsigned long hashVal = 0;
    for (char ch : key) {
        hashVal = 37 * hashVal + static_cast<unsigned long>(ch);
    }
    hashVal %= static_cast<unsigned long>(tableSizeParam);
    return static_cast<int>(hashVal);
}

int Dictionary::secondaryPrime() const {
    return SECONDARY_PRIMES[tableSizeIndex];
}

void Dictionary::allocateTable(int sizeIndex) {
    if (sizeIndex < 0) sizeIndex = 0;
    if (sizeIndex >= NUM_SIZES) sizeIndex = NUM_SIZES - 1;

    tableSizeIndex = sizeIndex;
    tableSize = TABLE_SIZES[tableSizeIndex];
    numEntries = 0;

    table = new string*[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

int Dictionary::findIndex(const string& key) const {
    const int idx1 = hash(key, tableSize);

    // Secondary hash function formula (double hashing):
    // h2(x) = R - (h(x) mod R)  where R is a prime < tableSize.
    // We compute (h(x) mod R) via hash(key, R), since the hash function already mods.
    const int step = secondaryPrime() - hash(key, secondaryPrime());

    int idx = idx1;
    for (int probes = 0; probes < tableSize; ++probes) {
        if (table[idx] == nullptr) return idx;
        if (*(table[idx]) == key) return idx;
        idx += step;
        if (idx >= tableSize) idx %= tableSize;
    }
    return idx1; // should never happen with load factor <= 0.5
}

int Dictionary::findInsertIndex(const string& key) const {
    // Caller ensures key is not already present.
    const int idx1 = hash(key, tableSize);
    const int step = secondaryPrime() - hash(key, secondaryPrime());

    int idx = idx1;
    for (int probes = 0; probes < tableSize; ++probes) {
        if (table[idx] == nullptr) return idx;
        idx += step;
        if (idx >= tableSize) idx %= tableSize;
    }
    return idx1;
}

void Dictionary::insertInternal(string* word, string** target, int targetSize, int targetSecondaryPrime) {
    const string& key = *word;
    const int idx1 = hash(key, targetSize);
    const int step = targetSecondaryPrime - hash(key, targetSecondaryPrime);

    int idx = idx1;
    for (int probes = 0; probes < targetSize; ++probes) {
        if (target[idx] == nullptr) {
            target[idx] = word;
            return;
        }
        idx += step;
        if (idx >= targetSize) idx %= targetSize;
    }
    // Should never happen given we rehash at 50% load factor.
}

void Dictionary::rehash() {
    const int oldSize = tableSize;
    string** oldTable = table;

    int newIndex = tableSizeIndex + 1;
    if (newIndex >= NUM_SIZES) newIndex = NUM_SIZES - 1;

    // Allocate new table
    table = nullptr;
    allocateTable(newIndex);

    const int newSecondary = secondaryPrime();

    // Move pointers (do not copy strings)
    for (int i = 0; i < oldSize; ++i) {
        if (oldTable[i] != nullptr) {
            insertInternal(oldTable[i], table, tableSize, newSecondary);
            ++numEntries;
            oldTable[i] = nullptr;
        }
    }

    delete[] oldTable;
}

/* ============================================================
   Public interface
   ============================================================ */

void Dictionary::insert(string* word) {
    if (word == nullptr) return;

    // Ignore duplicates; Dictionary owns inserted strings, so delete to avoid leaks.
    if (contains(*word)) {
        delete word;
        return;
    }

    // Rehash when adding would push us above 50% full.
    if ((numEntries + 1) * 2 > tableSize) {
        rehash();
    }

    const int idx = findInsertIndex(*word);
    table[idx] = word;
    ++numEntries;
}

bool Dictionary::contains(const string& word) const {
    const int idx = findIndex(word);
    return table[idx] != nullptr && *(table[idx]) == word;
}

void Dictionary::print(ostream& out) const {
    // Print dictionary in sorted order (by string value), without copying strings.
    vector<string*> words;
    words.reserve(static_cast<size_t>(numEntries));
    for (int i = 0; i < tableSize; ++i) {
        if (table[i] != nullptr) words.push_back(table[i]);
    }
    std::sort(words.begin(), words.end(),
              [](const string* a, const string* b) { return *a < *b; });

    for (const string* s : words) {
        out << *s << '\n';
    }
}

void Dictionary::printStructure(ostream& out) const {
    // Print every index; print only the key stored at that index (if any).
    for (int i = 0; i < tableSize; ++i) {
        out << i << ":";
        if (table[i] != nullptr) {
            out << " " << *(table[i]);
        }
        out << '\n';
    }
}
