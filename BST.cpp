#include "BST.h"
#include <iostream>

#include <list>

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>** curr = &root; 
  while(*curr!=0 && (*curr)->getValue()!=v) {
    if(v<(*curr)->getValue()) {
      curr = &(*curr)->getLeftChild();
    }
    else if (v>(*curr)->getValue()) {
      curr = &(*curr)->getRightChild();
    }
  }
  if(*curr!=0) {
    Node<T>* nodeToRemove = *curr;
    if(nodeToRemove->getRightChild() == 0 && nodeToRemove->getLeftChild() == 0) {
      *curr = 0;
    }
    else if(nodeToRemove->getRightChild() == 0) {
      *curr = (*curr)->getLeftChild();  //and we're done (no right children, so no ios)
    }
    else if(nodeToRemove->getLeftChild() == 0) {
      *curr = (*curr)->getRightChild(); //and we're done (we don't need the ios)
    }
    else {
      Node<T>* ios = nodeToRemove->getRightChild();
      while(ios->getLeftChild()!=0) {
        ios = ios->getLeftChild();
      }
      ios->setLeftChild(*(nodeToRemove->getLeftChild()));
      *curr = (*curr)->getRightChild();
    }
    delete nodeToRemove;
  }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void BST<T>::breadthPrint() {
  std::list< Node<T>* >* topLevel = new std::list< Node<T>* >();
  topLevel->push_back(root);
  levelTraversal(topLevel,0);
}

template <typename T>
int BST<T>::pow(int a, int p) {
  if(p == 0) return 1;
  else return a*pow(a, p-1);
}

template <typename T>
void BST<T>::levelTraversal(std::list< Node<T>* >* parents, int level) {
  bool keepGoing = false;
  std::list< Node<T>* >* holder = new std::list< Node<T>* >();
  
  for(int i = 0; i<pow(2,level); i++) {
    Node<T>* temp = parents->front();
    parents->pop_front(); 
    if(temp==0) {
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout<<" -0- ";
    }
    else if(temp->getLeftChild() == 0 && temp->getRightChild() == 0) {
      //do nothing
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout<<" "<<temp->getValue()<<" ";
    }
    else if(temp->getLeftChild() == 0) {
      holder->push_back((Node<T>*)0);
      holder->push_back(temp->getRightChild());
      std::cout<<" "<<temp->getValue()<<" ";
      keepGoing = true;
    }
    else if(temp->getRightChild() == 0) {
      holder->push_back(temp->getLeftChild());
      holder->push_back((Node<T>*)0);
      std::cout<<" "<<temp->getValue()<<" ";
      keepGoing = true;
    }
    else {
      holder->push_back(temp->getLeftChild());
      holder->push_back(temp->getRightChild());
      std::cout<<" "<<temp->getValue()<<" ";
      keepGoing = true;
    }
  }
  if(keepGoing) {
    delete parents;
    std::cout<<std::endl; 
    levelTraversal(holder, level+1);
  }
  else {
    std::cout<<std::endl;
  } 
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
