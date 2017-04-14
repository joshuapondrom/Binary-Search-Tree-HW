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
    void nremove(Node<T>* prev = NULL, bool isLeft = true){
      cout << "removing node" << endl;
      if(isChild()){
        if(prev != NULL){
	  if(isLeft) prev->left = NULL;
	  if(!isLeft) prev->right = NULL;
	}
        delete this;
	return;
      }
      Node<T>* temp = this;
      Node<T>* temp2 = this;
      if(left != NULL){
        if(temp->right != NULL){
	  temp= temp->right;
          while(temp->right != NULL){
	    temp2 = temp2->right;
	    temp = temp->right;
	  }
	}
	temp2->right = NULL;
	this->data = temp->data;
	delete temp;
      cout << "deleted node" << endl;
	return;
      }
      if(right != NULL){
        if(temp->left != NULL){
	  temp= temp->left;
          while(temp->left != NULL){
	    temp2 = temp2->right;
	    temp = temp->left;
	  }
	}
	temp2->left = NULL;
	this->data = temp->data;
	delete temp;
      cout << "deleted node" << endl;
	return;
      }
      cout << "end of node" << endl;
    }

};

template< typename T >
class MyBSTree:public AbstractBSTree<T>{
  private:
    Node<T>* root;
    int tsize;
  public:
    ~MyBSTree(){clear();}
    MyBSTree(Node<T>* proot = NULL, int psize = 0){
      root = proot;
      tsize = psize;
    }
    
    Node<T>* clone(const Node<T>* curr){
      if(curr == NULL)
        return NULL;
      else
        return new Node<T>(curr->data, clone(curr->left),clone(curr->right));
    }

    MyBSTree(MyBSTree &passed){
      if(passed.getRoot() == NULL)
        root = NULL;
      else
        copycon(this->root, passed.getRoot());
    }

    void copycon(Node<T>* &nroot, Node<T>* oroot){
      if(oroot == NULL)
        nroot = NULL;
      else{
        nroot = new Node<T>(oroot->data);
	copycon(nroot->left,oroot->left);
	copycon(nroot->right,oroot->right);
      }
    }

    const MyBSTree<T>& operator=(const MyBSTree& passed){
      if(this != &passed){
        this->clear();
	root= clone(passed.root);
	tsize = passed.tsize;
      }
      return *this;
    }

    Node<T>* getRoot() const{return root;}
    
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

    int find(const T& x) const{
      bool found = false;
      mfind(x, root,found);
      if(found)
        return mfind(x,root,found);
      if(!found)
        return -1 * mfind(x,root,found);
    }
    int mfind(const T& x, Node<T>* curr, bool &found = false) const{
      if(curr != NULL){
        if(x == curr->data){
	  found = true;
	  return 1;
	}
	if(x < curr->data)
	  return 1 + mfind(x,curr->left,found);
	else
	  return 1 + mfind(x,curr->right,found);
      }
      return 1;
    }
    
    void clear(){mclear(root);}
    void mclear(Node<T>* curr){
      if(curr == NULL)
        return;
      if(curr->isChild()){
        delete curr;
	return;
      }
      mclear(curr->left);
      mclear(curr->right);
      delete curr;
      root = NULL;
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
    
    T getMax(Node<T>* curr){
      while(curr->right != NULL)
        curr = curr->right;
      return curr->data;
    }

    void remove(const T& x){remove(x, root);}//mremove(x, root, NULL);}
    void remove(const T& x, Node<T>* &t){
      if(t == NULL)
        return;
      if(x > t->data)
        remove(x, t->right);
      else if(x < t->data)
        remove(x, t->left);
      else if(x == t->data){
        if(t->left != NULL && t->right != NULL){
	  t->data = getMax(t->left);
	  remove(t->data, t->left);
	}
	else{
	  Node<T>* temp = t;
	  t = t->left;
	  if(t == NULL)
	    t = temp -> right;
	  delete temp;
	}
      }
    }

    void mremove(const T& x, Node<T>* curr, Node<T>* prev, bool left = true){
      if(curr == NULL)
        return;
      if(x == curr->data){
        curr->nremove(prev, left);
	return;
      }
      if(x < curr->data){
        mremove(x,curr->left,curr, true);
      }
      mremove(x,curr->right,curr, false);
    }

    void printPreOrder() const {mprintPreOrder(root);}
    void mprintPreOrder(Node<T>* curr) const{
      if(curr != NULL){
        cout << curr->data << ' ';
        mprintPreOrder(curr->left);
        mprintPreOrder(curr->right);
      }
    }

    void printPostOrder() const {mprintPostOrder(root);}
    void mprintPostOrder(Node<T>* curr) const{
      if(curr != NULL){
        mprintPostOrder(curr->left);
        mprintPostOrder(curr->right);
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
