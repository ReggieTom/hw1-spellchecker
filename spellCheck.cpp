//INCLUDE IMPORTS:
#include <fstream> //files
#include <iostream> //terminal
#include <sstream>
#include <string>
#include <cctype> //Gives char imports like isalpha(). 
#include "Dictionary.h"
#include <vector>
#include <algorithm>   // required for swap
using namespace std; 

//FUNCTION DECLARATION:
vector<string> generateSuggestions(const string& word, const Dictionary& dict);
void printMisspelling(string word, int lineNum, vector<string> suggestions);

// Helper: treat anything non-letter as a separator, consistent with dictionary loading.
static inline bool isLetter(unsigned char ch) {
    return std::isalpha(ch) != 0;
}

int main(int argc, char* argv[]) {
    //Ensures the correct three filenames are run:
    if (argc < 4) {
        cerr << "Usage: ./spellcheck dict.txt text.txt dictout.txt\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) {
        cerr << "Could not open dictionary file: " << argv[1] << "\n";
        return 1; 
    }
    Dictionary dict; // build a dictionary from the word list. 
    string word; // find the correct words:
    char c; 
    auto flushDictWord = [&]() {
        if (word.empty()) return;
        if (!dict.contains(word)) {
            dict.insert(new string(word));
        }
        word.clear();
    };
    while (in.get(c)) {
        const unsigned char uc = static_cast<unsigned char>(c);
        if (isLetter(uc)) {
            word += static_cast<char>(std::tolower(uc));
        } else {
            // NON-LETTER = Word Ends
            flushDictWord();
        }
    }
    // Handle trailing word at EOF.
    flushDictWord();

    // POTENTIAL MISPELLED WORDS FILE:
    ifstream textFile(argv[2]);
    if (!textFile) {
        cerr << "Could not open text file: " << argv[2] << "\n";
        return 1;
    }
    /*
    FORMAT OF MISPELLED WORD:
        saed on line 5
    Suggested corrections:
        saved    sad

    remirmand on line 6
    No suggestions found
    */

    string lineText;
    int lineNum = 1;

    while (getline(textFile, lineText)) {
        string current;
        auto flushTextWord = [&]() {
            if (current.empty()) return;
            if (!dict.contains(current)) {
                vector<string> suggestions = generateSuggestions(current, dict);
                printMisspelling(current, lineNum, suggestions);
            }
            current.clear();
        };

        for (char ch : lineText) {
            const unsigned char uc = static_cast<unsigned char>(ch);
            if (isLetter(uc)) {
                current += static_cast<char>(std::tolower(uc));
            } else {
                flushTextWord();
            }
        }
        flushTextWord();
        lineNum++;
    }
    //OUTPUT THE DATA STRUCUTRE:
    ofstream out(argv[3]);
    if (!out) {
        cerr << " Error Opening Output File \n";
        return 1; 
    } 
    dict.printStructure(out);
    out.close();

    return 0; //Program Sucessful
} // END MAIN BRACKET

/* --------------------------
HOW TO GENERATE SUGGESTIONS:
As suggested corrections, list any words in the dictionary that are obtainable by applying any of the following rules (one at a time):
	•	Add one letter to the word (at any position)
	•	Remove one letter from the word
	•	Exchange adjacent characters
    */

vector<string> generateSuggestions(const string& word, const Dictionary& dict) {
    vector<string> out;
 
    const auto n = word.size();
 
    // 1) remove one letter
    for (size_t i = 0; i < n; ++i) {
        string s = word.substr(0, i) + word.substr(i + 1);
        if (dict.contains(s)) out.push_back(std::move(s));
    }
 
    // 2) add one letter (including at the end)
    for (size_t i = 0; i <= n; ++i) {
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            string s = word;
            s.insert(i, 1, ch);
            if (dict.contains(s)) out.push_back(std::move(s));
        }
    }
 
    // 3) swap adjacent letters
    for (size_t i = 1; i < n; ++i) {
        string s = word;
        std::swap(s[i - 1], s[i]);
        if (dict.contains(s)) out.push_back(std::move(s));
    }
 
    // optional: remove duplicates + keep sorted output
    std::sort(out.begin(), out.end());
    out.erase(std::unique(out.begin(), out.end()), out.end());
 
    return out;
}

void printMisspelling(string word, int lineNum, vector<string> suggestions) {
    cout << word << " on line " << lineNum << "\n";
    if (suggestions.empty()) {
        cout << "No suggestions found\n\n";
        return;
    }
    cout << "Suggested corrections:\n";
    cout << "    ";
    for (size_t i = 0; i < suggestions.size(); ++i) {
        if (i) cout << "    ";
        cout << suggestions[i];
    }
    cout << "\n\n";
}