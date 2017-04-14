//Joshua Pondrom
//1510 Data Structures
//

#ifndef MYBSTREE_H
#define MYBSTREE_H

#include <climits>
#include "abstractbstree.h"

template < typename T >
class Node{
  public:
    T data;
    Node* left;
    Node* right;
    Node(T pdata = 0, Node* pleft = NULL, Node* pright = NULL){
      data = pdata;
      left = pleft;
      right = pright;
    }
    bool isChild(){
      if(left == NULL && right == NULL)
        return true;
      return false;
    }
};

template< typename T >
class MyBSTree:public AbstractBSTree<T>{
  private:
    Node<T>* root;
    int tsize;
  public:
    MyBSTree(Node<T>* proot = NULL, int psize = 0){
      root = proot;
      tsize = psize;
    }

    int size() const{
      return tsize;
    }

    bool isEmpty() const{
      if(root == NULL)
        return true;
      return false;
    }
     
    int height() const{
      if(root == NULL)
        return 0;
      return mheight(root);
    }
    int mheight(Node<T>* curr) const{
      if(curr == NULL)
        return 0;
      if(mheight(curr->left) > mheight(curr->right))
        return 1 + mheight(curr->left);
      else
        return 1 + mheight(curr->right);
    }
    
    const T& getMax() const throw(Oops){
      Node<T>* temp = root;
        if(root == NULL)
	 throw Oops("OOPS! : Tree is empty!!");
      while(temp->right != NULL){temp = temp->right;}
      return temp->data;
    }
    
    const T& getMin() const throw(Oops){
      Node<T>* temp = root;
        if(root == NULL)
	 throw Oops("OOPS! : Tree is empty!!");
      while(temp->left != NULL){temp = temp->left;}
      return temp->data;
    }

    int find(const T& x) const{return mfind(x, root);}
    int mfind(const T& x, Node<T>* curr) const{
      if(curr->data == x)
        return 1;
      if(curr->left != NULL)
        return 1 + mfind(x,curr->left);
      if(curr->right != NULL)
       return 1 + mfind(x,curr->right);
      //return -1 * height();
      return 0;
    }
    
    void clear(){mclear(root);}
    void mclear(Node<T>* curr){
      if(curr->isChild()){
        delete curr;
	return;
      }
      mclear(curr->left);
      mclear(curr->right);
      delete curr;
    }
    
    void insert(const T& x){
      tsize++;
      if(root != NULL)
        minsert(x,root);
      else
        root = new Node<T>(x);
    }
    void minsert(const T& x, Node<T>* curr){
      if(curr->data == x){
        tsize--;
        return;
      }
      if(curr->data > x){
        if(curr->left == NULL)
	  curr->left = new Node<T>(x);
	else
          minsert(x, curr->left);
      }
      if(curr->data < x){
        if(curr->right == NULL)
          curr->right = new Node<T>(x);
	else
	  minsert(x, curr->right);
      }
    }
    
    void remove(const T& x){mremove(x,root);}
    void mremove(const T& x, Node<T>* curr){
    }

    void printPreOrder() const {mprintPreOrder(root);}
    void mprintPreOrder(Node<T>* curr) const{
      if(curr != NULL){
        cout << curr->data << ' ';
        mprint(curr->left);
        mprint(curr->right);
      }
    }

    void printPostOrder() const {mprintPostOrder(root);}
    void mprintPostOrder(Node<T>* curr) const{
      if(curr != NULL){
        mprint(curr->left);
        mprint(curr->right);
        cout << curr->data << ' ';
      }
    }

    void print() const {prettyPrint(root, 0);}
    void mprint(Node<T>* curr) const{
      if(curr != NULL){
        mprint(curr->left);
        cout << curr->data << ' ';
        mprint(curr->right);
      }
    }

    void prettyPrint (const Node<T>* t, const int pad) const {
      string s(pad, ' ');
      if ( t == NULL)
        cout << endl;
      else{
        prettyPrint(t->right, pad+4);
	cout << s << t->data << endl;
	prettyPrint(t->left, pad+4);
      }
    }
};

#endif
