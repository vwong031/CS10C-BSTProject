// Collaborated with: Valerie Wong, Kira Hammond
// https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/

/* Compile command:
   g++ Node.cpp main.cpp BSTree.cpp -Wall -Werror -Wuninitialized -o a.out
   */

#include "BSTree.h"

// ==========
// Constructor & Destructor
// ==========

BSTree::BSTree() {
  root = 0;
}

// https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/
void BSTree::deleteSubtree(Node *node) {
  if (!node) {
    return;
  }
  deleteSubtree(node->getLeft());
  deleteSubtree(node->getRight());
  delete node;
}

BSTree::~BSTree() {
  deleteSubtree(root);
  root = 0;
}


// ==========
//  Mutators
// ==========

/* "Insert an item into the binary search tree. Be sure to keep the
   binary search tree properties. When an item is first inserted into
   the tree the count should be set to 1. When adding a duplicate
   string (case sensitive), rather than adding another node, the count
   variable should just be incremented." */
void BSTree::insert(const string &newString) {
  Node *curr = 0; 
  Node *tmp = 0; 
  // Node *parent = 0;

  if (root == 0) {
    curr = new Node(newString); 
    root = curr; 
  }
  else {
    curr = root;
    while (curr != 0) {
      if (newString == curr->getKey()) {
        curr->incrementCount();
        return;
      } 
      else if (newString < curr->getKey()) {
        if (curr->getLeft() == 0) {
          tmp = new Node(newString); 
          curr->setLeft(tmp);
          tmp->setParent(curr);
          return;
        }
        else {
          // parent = curr; 
          curr = curr->getLeft();
          // Continue loop & search for leaf
        }
      }
      else {
        if (curr->getRight() == 0) {
          tmp = new Node(newString);
          curr->setRight(tmp);
          tmp->setParent(curr);
          return;
        }
        else {
          // parent = curr; 
          curr = curr->getRight();
          // Continue loop & search for leaf
        }
      }
    }
  }
}

/* "Remove a specified string from the tree. Be sure to maintain all
   binary search tree properties. If removing a node with a count
   greater than 1, just decrement the count, otherwise, if the count is
   simply 1, remove the node. You MUST follow the remove algorithm shown
   in the slides and discussed in class or else your program will not
   pass the test functions. When removing, if removing a leaf node,
   simply remove the leaf. Otherwise, if the node to remove has a left
   child, replace the node to remove with the largest string value that
   is smaller than the current string to remove (i.e. find the largest
   value in the left subtree of the node to remove). If the node has no
   left child, replace the node to remove with the smallest value larger
   than the current string to remove (i.e. find the smallest value in
   the right subtree of the node to remove)."
   
   Note: remove() must be written recursively!
   A helper can be added to overload this function.
   */
void BSTree::remove(Node *node, Node *parent) {
  /* This can probably be made cleaner, 
     so please feel free if you notice anything! */
  
  if (!node) {
    return;
  }
  
  Node *replacement;
  Node *parentOfReplacement;
  int i, initialCountOfReplacement;
  
  if (node->getCount() > 1) {
    node->decrementCount();
  } else if (!node->getLeft() && !node->getRight()) {
    // Node is leaf
    if (!parent) {
      // Node is root
      delete node;
      root = node = 0; 
    } else if (parent->getLeft() && *(parent->getLeft()) == *node) {
      parent->deleteLeft();
    } else {
      parent->deleteRight();
    }
  } else {
    if (node->getLeft()) {
      // Replace node with predecessor
      parentOfReplacement = node;
      replacement = largest(node->getLeft(), parentOfReplacement);
    } else {
      // Replace node with successor
      parentOfReplacement = node;
      replacement = smallest(node->getRight(), parentOfReplacement);
    }
    
    node->copyFrom(replacement);
    
    // Remove predecessor or successor
    initialCountOfReplacement = replacement->getCount();
    for (i = 0; i < initialCountOfReplacement; ++i) {
      remove(replacement, parentOfReplacement);
    }
  }
}

void BSTree::remove(const string &key) {
  Node *node;
  Node *parent = 0; // if node is found, its parent will be stored here
  node = search(root, key, parent);
  remove(node, parent);
}

// ==========
// Accessors
// ==========
Node* BSTree::largest(Node *node, Node *&parent) const {
  if (!node) {
    return 0;
  }
  Node *current = node;
  while (current->getRight()) {
    parent = current;
    current = current->getRight();
  }
  return current;
}

Node* BSTree::smallest(Node *node, Node *&parent) const {
  if (!node) {
    return 0;
  }
  Node *current = node;
  while (current->getLeft()) {
    parent = current;
    current = current->getLeft();
  }
  return current;
}

// ----------
//   Public
// ----------

/* "Search for a string in the binary search tree. It should return true
   if the string is in the tree, and false otherwise."
   */
bool BSTree::search(const string &key) const {
  Node *node;
  Node *discard = 0;
  node = search(root, key, discard);
  return node != 0;
}

/* Note to self from specs: search() must be written recursively! */
Node* BSTree::search(Node *node, const string &key, Node *&parent) const {
  if (!node) {
    return 0;
  }
  if (key == node->getKey()) {
    return node;
  } else if (key < node->getKey()) {
    parent = node; // set parent reference param to use in other functions

    /* Hey, Kira! Whenever you see this, can you explain to me why we have to 
    return this recursive statement instead of just calling it w/o the return? */
    
    /* Hi, there! We keep recursively calling search() till we find
       the base case above (either return 0 or return node).
       We don't want to lose 0 or node found, so each call passes
       the result back up until we get back here to the first function
       call. Then we return the node (or 0) back to the function
       that called this one (the search(key) version or sometimes a
       remove() function) so it can use the node for whatever it needs.
       Does that help?
       */
    return search(node->getLeft(), key, parent);
  } 
  else {
    parent = node; // set parent reference param to use in other functions
    return search(node->getRight(), key, parent);
  }
}

/* Return largest value in tree if any, else empty string */
string BSTree::largest() const {
  if (!root) {
    return "";
  }
  Node *node;
  Node *discard = 0;
  node = largest(root, discard);
  return node->getKey();
}

/* Return smallest value in tree if any, else empty string */
string BSTree::smallest() const {
  if (!root) {
    return "";
  }
  Node *node;
  Node *discard = 0;
  node = smallest(root, discard);
  return node->getKey();
}

/* "Compute and return the height of a particular string in the tree.
   The height of a leaf node is 0 (count the number of edges on the
   longest path). Return -1 if the string does not exist." */
int BSTree::height(const string &key) const {
  // int heightLeft = 0; 
  // int heightRight = 0;
  int height;
  // Node *curr = root;
  Node *parent = 0; 
  Node *node = 0; 

  node = search(root, key, parent);
  height = getHeight(node);

  return height; 
}

int BSTree::getHeight(Node *node) const {
  int leftHeight;
  int rightHeight; 

  if (!node) {
    return -1;
  }

  leftHeight = getHeight(node->getLeft());
  rightHeight = getHeight(node->getRight());
  return 1 + max(leftHeight, rightHeight);
}

// int BSTree::leftHeight(Node* node) const {
//   int height = 0;
//   Node *curr = node;

//   // cout << "curr: " << *curr << endl; 

//   // if leaf node, return height = 0
//   if (!curr->getLeft()) {
//     // cout << "curr->left is empty" << endl; 
//     // cout << "height should be 0: " << height << endl; 
//     return height;
//   }

//   curr = curr->getLeft();
//   ++height;
//   // cout << "left subtree found... curr is now: " << curr->getKey() << endl; 

//   // keep going until it is a leaf node
//   while (curr->getLeft() != 0 || curr->getRight() != 0) {
//     // cout << "curr not leaf node" << endl; 
//     while (curr->getLeft()) {
//       // cout << "traverse left subtree..." << endl;
//       curr = curr->getLeft(); 
//       // cout << "height: " << height << endl; 
//       ++height;
//       // cout << "new height: " << height << endl; 
//       // cout << endl; 
//     }
//     while (curr->getRight()) {
//       // cout << "traverse right subtree..." << endl; 
//       curr = curr->getRight();
//       // cout << "height: " << height << endl; 
//       ++height; 
//       // cout << "new height: " << height << endl; 
//     }
//   }

//   // cout << "returning height: " << height << endl; 
//   return height; 
// }

// int BSTree::rightHeight(Node* node) const {
//   int height = 0; 
//   Node *curr = node; 

//   // if leaf node, return height = 0
//   if (!curr->getRight()) {
//     // cout << "curr->right is empty" << endl; 
//     // cout << "height should be 0: " << height << endl; 
//     return height;
//   }

//   curr = curr->getRight();
//   ++height;
//   // cout << "right subtree found... curr is now: " << curr->getKey() << endl; 

//   while (curr->getLeft() != 0 || curr->getRight() != 0) {
//     // cout << "curr not leaf node" << endl; 
//     while (curr->getRight()) {
//       // cout << "traverse right subtree..." << endl; 
//        curr = curr->getRight();
//       // cout << "height: " << height << endl; 
//       ++height;
//       // cout << "new height: " << height << endl;
//     }
//     while (curr->getLeft()) {
//       // cout << "traverse left subtree..." << endl; 
//       curr = curr->getLeft();
//       // cout << "height: " << height << endl; 
//       ++height; 
//       // cout << "new height: " << height << endl; 
//     }
//   }

//   // cout << "returning height: " << height << endl; 
//   return height; 
// }

// ==========
//  Printing
// ==========

/* "Traverse and print the tree in preorder notation" */
void BSTree::preOrder(Node *node) const {
  if (!node) {
    return;
  }
  cout << *node << ", ";
  preOrder(node->getLeft());
  preOrder(node->getRight());
}

/* "Traverse and print the tree in inorder notation" */
void BSTree::inOrder(Node *node) const {
  if (!node) {
    return;
  }
  inOrder(node->getLeft());
  cout << *node << ", ";
  inOrder(node->getRight());
}

/* "Traverse and print the tree in postorder notation" */
void BSTree::postOrder(Node *node) const {
  if (!node) {
    return;
  }
  postOrder(node->getLeft());
  postOrder(node->getRight());
  cout << *node << ", ";
}

// ----------
//  Wrappers
// ----------
void BSTree::preOrder() const {
  preOrder(root);
  cout << endl;
}

void BSTree::inOrder() const {
  inOrder(root);
  cout << endl;
}

void BSTree::postOrder() const {
  postOrder(root);
  cout << endl;
}
