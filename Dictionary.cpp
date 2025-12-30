/**************************************************************
The AVL_Dictionary.cpp
This file contains the AVL binary search tree functions. 

The .h file declares what functions exist.
The .cpp file defines how those functions work.
 **************************************************************/
#include "Dictionary.h"
#include <algorithm>
#include <iostream>

using namespace std;

/* ============================================================
   Constructors / Destructors
   ============================================================ */

Dictionary::Dictionary() {
    root = nullptr;
}

Dictionary::~Dictionary() {
    destroy(root);
}

/* ============================================================
   Helper functions
   ============================================================ */

int Dictionary::getHeight(Node* node) const {
    if (node == nullptr)
        return 0;
    return node->height;
}

int Dictionary::getBalance(Node* node) const {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

/* ============================================================
   Rotations
   ============================================================ */

Dictionary::Node* Dictionary::rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    // Rotate
    x->right = y;
    y->left = temp;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Dictionary::Node* Dictionary::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    // Rotate
    y->left = x;
    x->right = temp;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

/* ============================================================
   Insert (AVL logic)
   ============================================================ */

Dictionary::Node* Dictionary::insert(Node* node, string* word) {

    // Normal BST insert
    if (node == nullptr) {
        return new Node(word);
    }

    if (*word < *(node->word)) {
        node->left = insert(node->left, word);
    }
    else if (*word > *(node->word)) {
        node->right = insert(node->right, word);
    }
    else {
        // Duplicate word, ignore
        return node;
    }

    // Update height
    node->height = 1 + max(getHeight(node->left),
                            getHeight(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && *word < *(node->left->word))
        return rotateRight(node);

    // Right Right
    if (balance < -1 && *word > *(node->right->word))
        return rotateLeft(node);

    // Left Right
    if (balance > 1 && *word > *(node->left->word)) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && *word < *(node->right->word)) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Dictionary::insert(string* word) {
    root = insert(root, word);
}

/* ============================================================
   Lookup (same as BST)
   ============================================================ */

bool Dictionary::contains(Node* node, const string& word) const {
    if (node == nullptr)
        return false;

    if (word < *(node->word))
        return contains(node->left, word);
    else if (word > *(node->word))
        return contains(node->right, word);
    else
        return true;
}

bool Dictionary::contains(const string& word) const {
    return contains(root, word);
}

/* ============================================================
   Printing
   ============================================================ */

void Dictionary::printInOrder(Node* node, ostream& out) const {
    if (node == nullptr)
        return;

    printInOrder(node->left, out);
    out << *(node->word) << endl;
    printInOrder(node->right, out);
}

void Dictionary::print(ostream& out) const {
    printInOrder(root, out);
}

void Dictionary::printStructure(Node* node, int depth, ostream& out) const {
    if (node == nullptr)
        return;

    // Print right subtree first
    printStructure(node->right, depth + 1, out);

    for (int i = 0; i < depth; i++)
        out << "    ";

    out << *(node->word) << endl;

    printStructure(node->left, depth + 1, out);
}

void Dictionary::printStructure(ostream& out) const {
    printStructure(root, 0, out);
}

/* ============================================================
   Cleanup
   ============================================================ */

void Dictionary::destroy(Node* node) {
    if (node == nullptr)
        return;

    destroy(node->left);
    destroy(node->right);

    delete node->word;
    delete node;
}
