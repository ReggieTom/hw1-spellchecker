// Dictionary.cpp
#include "Dictionary.h"
 
#include <ostream>
#include <string>
 
Dictionary::Dictionary() = default;
 
Dictionary::~Dictionary() {
    destroy(root);
    root = nullptr;
}
 
void Dictionary::insert(std::string* wordPtr) {
    if (wordPtr == nullptr) return;
    insert(root, wordPtr);
}
 
bool Dictionary::contains(const std::string& word) const {
    return contains(root, word);
}
 
void Dictionary::printInOrder(std::ostream& out) const {
    printInOrder(root, out);
}
 
void Dictionary::printStructure(std::ostream& out) const {
    printStructure(root, out, 0);
}
 
void Dictionary::destroy(Node* n) {
    if (!n) return;
    destroy(n->left);
    destroy(n->right);
    // Dictionary owns the inserted word pointers.
    delete n->word;
    delete n;
}
 
void Dictionary::insert(Node*& n, std::string* wordPtr) {
    if (!n) {
        n = new Node(wordPtr);
        return;
    }
 
    const std::string& value = *wordPtr;
    const std::string& nodeValue = *(n->word);
 
    if (value == nodeValue) {
        // Duplicate by string value: we own the incoming pointer, so free it.
        delete wordPtr;
        return; // duplicate by string value => do nothing
    }
 
    if (value < nodeValue) {
        insert(n->left, wordPtr);
    } else {
        insert(n->right, wordPtr);
    }
}
 
bool Dictionary::contains(const Node* n, const std::string& word) {
    if (!n) return false;
 
    const std::string& nodeValue = *(n->word);
 
    if (word == nodeValue) return true;
    if (word < nodeValue) return contains(n->left, word);
    return contains(n->right, word);
}
 
void Dictionary::printInOrder(const Node* n, std::ostream& out) {
    if (!n) return;
    printInOrder(n->left, out);
    out << *(n->word) << '\n';
    printInOrder(n->right, out);
}
 
void Dictionary::printStructure(const Node* n, std::ostream& out, int depth) {
    if (!n) return;
 
    // print right subtree first so the tree appears rotated left
    printStructure(n->right, out, depth + 1);
 
    for (int i = 0; i < depth; ++i) out << "  ";
    out << *(n->word) << '\n';
 
    printStructure(n->left, out, depth + 1);
}