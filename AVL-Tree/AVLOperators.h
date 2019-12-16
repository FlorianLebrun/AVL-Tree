#ifndef __AVL_Tree_Operators__
#define __AVL_Tree_Operators__

#include <stdint.h>

/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*
* AVL Tree Operators
*
* Tooling for handling of AVL tree with node class 'TNode' containing the fields:
*   - left: TNode*
*   - right: TNode*
*   - height: integer
*   - compare: int compare(TKey key)
*
* All functions take the tree root in firast argument, and can return the new root.
*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/
template <class TNode>
class AVLOperators {

public:
  typedef TNode* Node;

  struct IComparable {
    virtual int compare(Node node) = 0;
  };
  struct IInsertable : IComparable {
    virtual Node create(Node overridden) = 0;
  };

  // Check Balance factor of sub tree
  static bool checkConsistency(Node root) {
    if (!root) return true;
    int height = getSubHeight(root) + 1;
    if (root->height != height) return false;
    int balance = getBalance(root);
    if (balance < -1 || balance > 1) return false;
    return checkConsistency(root->left) && checkConsistency(root->right);
  }

  static int count(Node root)
  {
    if (!root) return 0;
    int n = 1;
    n += count(root->left);
    n += count(root->right);
    return n;
  }

  static Node removeAtMinimum(Node root, Node& result) {
    if (root->left) {
      root->left = removeAtMinimum(root->left, result);
      return rebalance(root);
    }
    else {
      result = root;
      return root->right;
    }
  }

  static Node removeAtMaximum(Node root, Node& result) {
    if (root->right) {
      root->right = removeAtMaximum(root->right, result);
      return rebalance(root);
    }
    else {
      result = root;
      return root->left;
    }
  }

  static Node removeAt(Node root, IComparable* comparable, Node& result)
  {
    // Empty sub tree, nothing to remove
    if (root == 0) {
      result = 0;
      return 0;
    }

    // Remove key from sub tree
    int c = comparable->compare(root);
    if (c > 0) {
      root->right = removeAt(root->right, comparable, result);
      return rebalance(root);
    }
    else if (c < 0) {
      root->left = removeAt(root->left, comparable, result);
      return rebalance(root);
    }
    else {
      result = root;
      if (root->left && root->right) {
        Node new_root;
        root->right = removeAtMinimum(root->right, new_root);
        new_root->left = root->left;
        new_root->right = root->right;
        return rebalance(new_root);
      }
      else {
        return reinterpret_cast<Node>(uintptr_t(root->right) | uintptr_t(root->left));
      }
    }
  }

  static void findAt(Node root, IComparable* comparable, Node& result) {

    // Empty sub tree, nothing to remove
    if (root == 0) {
      result = 0;
      return;
    }

    // Find key from sub tree
    int c = comparable->compare(root);
    if (c > 0) {
      findAt(root->right, comparable, result);
    }
    else if (c < 0) {
      findAt(root->left, comparable, result);
    }
    else {
      result = root;
    }
  }

  static Node insertAt(Node root, IInsertable* insertable, Node& result) {

    // New node location reached
    if (root == 0) {
      if (result = insertable->create(0)) {
        result->height = 1;
        result->left = 0;
        result->right = 0;
      }
      return result;
    }

    // Perform the insertion
    int c = insertable->compare(root);
    if (c < 0) {
      root->left = insertAt(root->left, insertable, result);
      return rebalance(root);
    }
    else if (c > 0) {
      root->right = insertAt(root->right, insertable, result);
      return rebalance(root);
    }
    else {
      if (result = insertable->create(root)) {
        result->height = root->height;
        result->left = root->left;
        result->right = root->right;
        return result;
      }
      return root;
    }
  }

private:

  static int getSubHeight(Node node) {
    Node right = node->right;
    if (Node left = node->left) {
      if (right) {
        if (left->height > right->height) return left->height;
        else return right->height;
      }
      else return left->height;
    }
    else {
      if (right) return right->height;
      else return 0;
    }
  }
  static int getBalance(Node node) {
    int balance = node->left ? node->left->height : 0;
    if (node->right) return balance - node->right->height;
    else return balance;
  }
  static Node rightRotate(Node y) {
    Node x = y->left;

    // Perform rotation
    Node tmp = x->right;
    x->right = y;
    y->left = tmp;

    // Update heights
    y->height = getSubHeight(y) + 1;
    x->height = getSubHeight(x) + 1;

    // Return new root
    return x;
  }
  static Node leftRotate(Node x) {
    Node y = x->right;

    // Perform rotation
    Node tmp = y->left;
    y->left = x;
    x->right = tmp;

    // Update heights
    x->height = getSubHeight(x) + 1;
    y->height = getSubHeight(y) + 1;

    // Return new root
    return y;
  }
  static Node rebalance(Node node) {
    int balance = getBalance(node);
    if (balance < -1) {
      if (getBalance(node->right) <= 0) {
        return leftRotate(node);
      }
      else {
        node->right = rightRotate(node->right);
        return leftRotate(node);
      }
    }
    else if (balance > 1) {
      if (getBalance(node->left) >= 0) {
        return rightRotate(node);
      }
      else {
        node->left = leftRotate(node->left);
        return rightRotate(node);
      }
    }
    else {
      node->height = getSubHeight(node) + 1;
      return node;
    }
  }
};

#endif
