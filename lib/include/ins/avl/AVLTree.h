#pragma once
#include "./AVLOperators.h"
#include <string>

namespace ins {
   
class AVLTree
{
public:

  struct Node;
  struct Handler;
  typedef AVLOperators<Node, Handler> AVL;
  
  struct Handler {
    static Node*& left(Node* node) {return (Node*&)node->__0;}
    static Node*& right(Node* node) {return (Node*&)node->__1;}
    static char& height(Node* node) {return node->__2;}
  };
  
  struct Node {
    void* __0;
    void* __1;
    char __2;
    int key;
    Node(int d) {
      this->key = d;
    }
    std::string toString() {
      char s[64];
      _itoa_s(this->key, s, sizeof(s), 10);
      return s;
    }
  };

  struct Key : AVL::IInsertable {
    int key;
    Key(int _key) : key(_key) {
    }
    virtual int compare(Node* node) override {
      return key - node->key;
    };
    virtual Node* create(Node* overridden) override {
      return overridden ? 0 : new Node(key);
    };
  };

  AVLTree() {
    this->root = 0;
  }
  Node* find(int key) {
    Node* result;
    AVL::findAt(this->root, &Key(key), result);
    return result;
  }
  Node* insert(int key) {
    Node* result;
    this->root = AVL::insertAt(this->root, &Key(key), result);
    return result;
  }
  bool remove(int key) {
    Node* result;
    this->root = AVL::removeAt(this->root, &Key(key), result);
    if (result) {
      delete result;
      return true;
    }
    return false;
  }
  bool removeUpper(int key) {
     Node* result;
     this->root = AVL::removeUpper(this->root, &Key(key), result);
     if (result) {
        delete result;
        return true;
     }
     return false;
  }
  void printValues() {
    for(Node* node : AVL::enumerator(this->root)) {
      printf("%s\n", node->toString().c_str());
    }
  }
  void printTree() {
    this->printNode(this->root);
    int count = AVL::count(this->root);
    printf("height = %d\n", Handler::height(this->root));
    printf("count = %d\n", count);
  }

private:
  Node* root;

  int printNode(Node* node, int level = 0)
  {
    int count = 0;
    if (node != 0) {
      count += printNode(Handler::left(node), level + 1);
      for (int i = 0; i < level; i++) printf("-");
      printf("- %s\n", node->toString().c_str());
      count += printNode(Handler::right(node), level + 1);
      count++;
    }
    return count;
  }
};

}