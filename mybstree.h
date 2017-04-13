//Joshua Pondrom
//1510 Data Structures
//

#include <climits>

template < typename T >
class Node{
  private:
    T data;
    Node* left;
    Node* right;
  public:
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
class MyBSTree:public AbstractBSTree{
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
      try{
        if(root == NULL)
	 throw Oops("OOPS! : Tree is empty!!");
      }
      while(temp->right != NULL){temp = temp->right;}
      return right->data;
    }
    
    const T& getMin() const throw(Oops){
      Node<T>* temp = root;
      try{
        if(root == NULL)
	 throw Oops("OOPS! : Tree is empty!!");
      }
      while(temp->left != NULL){temp = temp->left;}
      return temp->data;
    }

    int find(const T& x) const{return mfind(x)}
    int mfind(const T& x, Node<T>* curr = root){
      if(curr->data == x)
        return 1;
      return 1 + mfind(x,curr->left);
      return 1 + mfind(x,curr->right);
      return -1 * height();
    }
};
