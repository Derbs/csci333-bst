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
int BST<T>::depth(Node<T>* root, int dpth, int maxDepth) {
  if(root != 0 && (root->getLeftChild()!=0 || root->getRightChild() != 0)) {
    int leftDepth = depth(root->getLeftChild(),dpth+1,maxDepth);
    int rightDepth = depth(root->getRightChild(),dpth+1,maxDepth);
    if(leftDepth > rightDepth)  return leftDepth; 
    else return rightDepth;
  }
  else {
    return dpth;
  }
  
}

template <typename T>
void BST<T>::levelTraversal(std::list< Node<T>* >* parents, int level) {
  bool keepGoing = false;
  int treeDepth = depth(root,0,0);
  int width = pow(2,treeDepth)*3;
  std::list< Node<T>* >* holder = new std::list< Node<T>* >();
//  std::cout<<"The full depth is::"<<treeDepth<<", the current depth is:: "<<level<<" and the width is::"<<width<<std::endl;
  //determine starting spacing
  int startSpace = width-1;
  for(int i = 0; i<level+1; i++) {
    startSpace = startSpace/2;
  }
  int numEls = pow(2,level);
  if(treeDepth != level) { 
    for(int i = 0; i<startSpace; i++) { std::cout<<" "; } //initial spacing before any elements.
  }
  for(int i = 0; i<numEls; i++) {
    Node<T>* temp = parents->front();
    parents->pop_front(); 
    if(temp==0) {
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout<<"-";
    }
    else if(temp->getLeftChild() == 0 && temp->getRightChild() == 0) {
      //do nothing
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout<<temp->getValue();
    }
    else if(temp->getLeftChild() == 0) {
      holder->push_back((Node<T>*)0);
      holder->push_back(temp->getRightChild());
      std::cout<<temp->getValue();
      keepGoing = true;
    }
    else if(temp->getRightChild() == 0) {
      holder->push_back(temp->getLeftChild());
      holder->push_back((Node<T>*)0);
      std::cout<<temp->getValue();
      keepGoing = true;
    }
    else {
      holder->push_back(temp->getLeftChild());
      holder->push_back(temp->getRightChild());
      std::cout<<temp->getValue();
      keepGoing = true;
    }
    if(!parents->empty()) {
      int spacing = (width/numEls)-1;
      if(spacing!=2) {
        for(int i = 0; i<spacing; i++) { std::cout<<" ";}
      }
      else {
        if(i%2==0) std::cout<<"   ";
        else std::cout<<" ";
      }
    }
  }
  if(keepGoing) {
    delete parents;  //don't need it anymore!

    int lines = (width/4)-1;  //the number of branches needed between this level and next level needed
    for(int i = 0; i<level; i++) { lines = lines/2; }  //lines are based on level. (half prvLevels)
    int inBetweenSpacing = 1;     //spacing in between slashes (branches) starts at 1.
    int spacing = (width/numEls)-1;  //spacing relates to width and the number of elements.  
    for(int i = 0; i<lines; i++) {   //for every single line we make for a branch...
      std::cout<<std::endl;          //lets start on a new line.
      spacing = spacing-2;            //spacing between a right branch and the next left branch decreases by 2 as you continue along.  
      startSpace = startSpace - 1;    //remember startSpace?  subtract 1 from it and then indent.
      for(int j = 0; j<startSpace; j++) {
        std::cout<<" ";   //creating starting space before any slashes
      }
      for(int j = 0; j<numEls; j++) {  //now lets create the branches.
        std::cout<<"/"; //initial backslash for el_j
        for(int m = 0; m<inBetweenSpacing; m++) {  
          std::cout<<" ";  //now, the spacing between the left and right branch for el_j
        }
        std::cout<<"\\"; //ending forward slash for el_j
        for(int n = 0; n<spacing; n++) {
          std::cout<<" ";  //spacing between el_j and el_j+1
        }
        
      }
      inBetweenSpacing = inBetweenSpacing+2;  //in between spacing increases by 2 as you go down.
    }
    std::cout<<std::endl;  //create a new line at the very very end of the branches for the next el.
    levelTraversal(holder, level+1);  //recursively go to the next level.  
  }
  else {
    std::cout<<std::endl;  //base case.  new line and finish it off.
  } 
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
