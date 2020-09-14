#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
#include "Account.h"

using namespace std;

//------------------------------------------------------------------------------

//This file provides prototypes for a binary search tree. includes functions
//that perform operations ona tree as insert, retrieve empty, and display.
//data members are a Node struct for the data, right, and left, as well as
//the root and private methods to help in recursion.

//-----------------------------------------------------------------------------*-
class BSTree {

public:
    BSTree();  // constructor
    ~BSTree(); // destructor - calls makeEmpty to deallocate all memory
    
    // insert object into tree
    bool insert(Account*&);
    // retrieve object(parameter)
    bool retrieve(const Account&, Account*&) const;
    // make empty the current tree
    void makeEmpty();
    // displays the contents of a tree
    void display() const;
    // return true if the tree is empty
    bool isEmpty() const;

private:

    struct Node {
        Account* data;
        Node* right;
        Node* left;
    };

    Node* root;       // root of the tree
    
    //helper functions for recursion. Passing in the root to traverse;
    void makeEmptyHelper(Node*);
    void displayHelper(Node*) const;
    bool retrieveHelper(const Account&, Account*&, Node* cur) const;
};

#endif /* BSTREE_H */
