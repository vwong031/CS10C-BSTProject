#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
using namespace std;

class Node {
  // protected:
  private:
    string key;
    Node *leftSubtree;
    Node *rightSubtree;
    Node *parent;  
    int count;
    int height;
  public:
    // TODO Is the ; needed (or good practice)
    // after the inline default constructor?
    // Node() : key(""), leftSubtree(0), rightSubtree(0), count(0) {}
    Node(string key) : key(key), leftSubtree(0), rightSubtree(0), parent(0), count(1), height(0) {};
    
    /* Accessors */
    string getKey() const;
    int getCount() const;
    Node* getLeft() const;
    Node* getRight() const;
    int getHeight() const; 
    
    /* Mutators */
    void copyFrom(Node *);
    void incrementCount();
    void decrementCount();
    void setLeft(Node*);
    void setRight(Node*);
    void deleteLeft();
    void deleteRight();
    void incrementHeight();
    void setParent(Node*);
    
    /* Comparators */
    bool operator==(const Node &);
    
    /* Printing */
    friend ostream& operator<<(ostream &, const Node &);
};

#endif // __NODE_H__
