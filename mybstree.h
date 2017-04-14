//Joshua Pondrom
//1510 Data Structures
//

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
    MyBSTree(Node<T> proot = NULL, int psize = 0){
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
      Node<T>* temp = root;
      int theight = 1;
      while(temp->left != NULL){
        theight++;
	temp = temp->left;
      }
      return theight;
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
    int mfind(const T& x, Node<T>* curr){
      if(curr->data == x)
        return 1;
      return 1 + mfind(x,curr->left);
      return 1 + mfind(x,curr->right);
      return -1 * height();
    }
    
    void clear(){mclear(root);}
    void mclear(Node<T>* curr){
      if(curr.isChild()){
        delete curr;
	return;
      }
      mclear(curr->left);
      mclear(curr->right);
      delete curr;
    }
    
    void insert(const T& x){minsert(x,root);}
    void minsert(const T& x, Node<T>* curr){
      if(curr == NULL){
        root = new Node<T>(x);
	return;
      }
      if(curr->data == x){
        return;
      }
      if(curr->data > x){
        minsert(x, curr->left);
      }
      if(curr->data < x){
        minsert(x,curr->right);
      }
    }
    
    void remove(const T& x){mremove(x,root);}
    void mremove(const T& x, Node<T>* curr){
      if(x == root){}
    }

    void printPreOrder() const {mprintPreOrder(root);}
    void mprintPreOrder(Node<T>* curr){
      if(curr->isChild())
        return;
      cout << curr->data;
      mprint(curr->left);
      mprint(curr->right);
    }

    void printPostOrder() const {mprintPostOrder(root);}
    void mprintPostOrder(Node<T>* curr){
      if(curr->isChild())
        return;
      mprint(curr->left);
      mprint(curr->right);
      cout << curr->data;
    }

    void print() const {mprint(root);}
    void mprint(Node<T>& curr){
      if(curr->isChild())
        return;
      mprint(curr->left);
      cout << curr->data;
      mprint(curr->right);
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
