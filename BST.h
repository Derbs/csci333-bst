#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>
#include <list>

template <typename T>
class BST {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  void levelTraversal(std::list< Node<T>* >* parents, int level);
  int pow(int a, int p);
 public:
  BST<T>();
  ~BST<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
  void breadthPrint();
};


#endif
