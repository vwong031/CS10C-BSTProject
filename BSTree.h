#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "Node.h"
#include <iostream>
using namespace std;

class BSTree {
  public:
    /* Constructor & Destructor */
    BSTree(); // default constructor
    ~BSTree();
    /* Mutators */
    void insert(const string &);
    void remove(const string &);
    /* Accessors */
    bool search(const string &) const;
    string largest() const;
    string smallest() const; 
    int height(const string &) const; 
    /* Printing */
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
  private:
    Node *root;
    /* Constructor & Destructor */
    void deleteSubtree(Node *);
    /* Mutators */
    void remove(Node *, Node *);
    /* Accessors */
    Node* search(Node *, const string &, Node *&) const;
    // int leftHeight(Node*) const;
    // int rightHeight(Node*) const;
    Node* largest(Node *, Node *&) const;
    Node* smallest(Node *, Node *&) const;
    int getHeight(Node *) const;

    /* Printing */
    void preOrder(Node *) const;
    void inOrder(Node *) const;
    void postOrder(Node *) const;
};

#endif // __BSTREE_H__
