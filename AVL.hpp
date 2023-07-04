#ifndef __AVL_HPP_
#define __AVL_HPP_

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class AVL {
private:
  class Node {
    Node *parent, *left, *right;
    int height;
    string element;

  public:
    Node(const string& e, Node *parent, Node *left, Node *right);
    
    Node*  getParent() const;
    Node*  getLeft() const;
    Node*  getRight() const;
    string getElement() const;
    int    getHeight() const;
  
    void setLeft(Node *);
    void setRight(Node *);
    void setParent(Node *);
    void setElement(string e);
      
    bool isLeft() const;
    bool isRight() const;
    int  rightChildHeight() const;
    int  leftChildHeight() const;
    int  updateHeight();
    bool isBalanced();
  };
private:
  
  int   size;
  Node* root;
  
public:
    
    class Iterator {

      Node *curNode; 
      stack<Node*> stackOfNodes;
      
    public:
      Iterator();
      Iterator(Node*);
      void iterativePreorder();
      Iterator& operator++();
      Iterator operator++(int a);
      string operator*(); 
      bool operator!=(Iterator it);
      bool operator==(Iterator it);
      AVL::Node* getCurNode() const;

    };
    
  Iterator begin() const;  
  Iterator end() const;
  
  static const int MAX_HEIGHT_DIFF = 1;
  AVL();
  AVL(const AVL& );
  bool contains(string e);
  AVL::Node* insertNode(string data);
  AVL::Node *findNode(string str, AVL::Node *cur);
  void rebalance(AVL::Node *cur);
  AVL::Node *rebalanceSon(AVL::Node *cur);
  AVL::Node *reconstruct(AVL::Node *v, AVL::Node *w, AVL::Node *u);
  bool add(string e);
  bool rmv(string e);
  AVL::Node *removeNode(string data);
  void deleteNode(AVL::Node *cur);
  void print2DotFile(char *filename);
  void pre_order(std::ostream& out);
  void freeAVLtree();

  friend std::ostream& operator<<(std::ostream & out, const AVL& tree);  
  AVL& operator  =(const AVL& avl);
  AVL  operator  +(const AVL& avl);
  AVL& operator +=(const AVL& avl);
  AVL& operator +=(const string& e);
  AVL& operator -=(const string& e);
  AVL  operator  +(const string& e);
  AVL  operator  -(const string& e);
};

#endif

