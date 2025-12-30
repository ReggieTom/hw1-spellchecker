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

// HELPER FUNCTION TO REMOVE PUNCTUATION:
string normalize(string word);
string normalize(string word) {
    while (!word.empty() && ispunct(word.back())) {
        word.pop_back(); //pop the last char punctuation
    }
    return word;
}
//Ensures the correct three filenames are run:
int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: ./spellcheck dict.txt text.txt dictout.txt\n";
        return 1;
    }
    //READ WORDS IN FILE:
    ifstream in(argv[1]); //ifstream in("smallDict.txt");
    if (!in) {
        cout << "Could not open smallDict.txt\n";
        return 1; 
    }
    Dictionary dict; // build a dictionary from the word list. 
    string word; // find the correct words:
    char c; 
    while (in.get(c)) {   
        if (isalpha(c)) {
            word += static_cast<char>(tolower(c));
        } else {
            // NON-LETTER = Word Ends
            if (!word.empty()) {
                string new_word = normalize(word); // each word gets own memory
                if (!dict.contains(new_word)) {
                    dict.insert(new string(new_word));
                }
            } word.clear(); 
        } 
    }
    // POTENTIAL MISPELLED WORDS FILE:
    ifstream textFile(argv[2]); //ifstream textFile("test1.txt");
    if (!textFile) {
        cout << "Could not open test1.txt\n";
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
        stringstream lineStream(lineText);
        string word;
        while (lineStream >> word) {
       for (size_t i = 0; i < word.size(); ++i) {
         word[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(word[i])));
        }
        word = normalize(word);
        if (word.empty()) continue;
        if (!dict.contains(word)) {
            vector<string> suggestions = generateSuggestions(word, dict);
            printMisspelling(word, lineNum, suggestions);
        }
    }
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
    */\
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
    cout << "Line " << lineNum << ": " << word << " is misspelled";

    if (!suggestions.empty()) {
        cout << " (suggestions: ";
        for (size_t i = 0; i < suggestions.size(); i++) {
            cout << suggestions[i];
            if (i + 1 < suggestions.size())
                cout << ", ";
        }
        cout << ")";
    }

    cout << endl;
}
