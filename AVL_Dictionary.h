/*
AVL Binary Search Tree: 

This file uses the Dictionary class implemented as an AVL tree.
An AVL tree is a type of binary search tree that keeps itself
balanced to ensure fast searching.

In a regular binary search tree, inserting words in certain
orders can cause the tree to become unbalanced, which makes
searching slower.

An AVL tree fixes this problem by rebalancing the tree after
every insertion. This keeps the tree from becoming too tall
on one side.

For an AVL tree, the heights of the left and right subtrees
at any node can differ by at most one. This balance rule
guarantees that searching the tree remains efficient.
*/


#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <ostream>

using std::string;
using std::ostream;

class Dictionary {
private:
    struct Node {
        string* word;
        Node* left;
        Node* right;
        int height;

        Node(string* w)
            : word(w), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    /* ===== Helper functions ===== */
    Node* insert(Node* node, string* word);
    bool contains(Node* node, const string& word) const;

    void printInOrder(Node* node, ostream& out) const;
    void printStructure(Node* node, int depth, ostream& out) const;

    int getHeight(Node* node) const;
    int getBalance(Node* node) const;

    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* y);

    void destroy(Node* node);

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
