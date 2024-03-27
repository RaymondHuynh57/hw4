#ifndef AVLBST_H
#define AVLBST_H




#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"




struct KeyError { };




/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();




    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);




    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;




protected:
    int8_t balance_;    // effectively a signed char
};




/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/




/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{




}




/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{




}




/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}




/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}




/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}




/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}




/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}




/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}








/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/








template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);




    // Add helper functions here
    void Insert_Fix(Node<Key, Value>* temp);
    void Remove_Fix(Node<Key, Value>* temp, int diff);
    void rotateLeftRemove(Node<Key, Value>* temp, Node<Key, Value>* C_Node, Node<Key, Value>* G_Node);
    void rotateRightRemove(Node<Key, Value>* temp, Node<Key, Value>* C_Node, Node<Key, Value>* G_Node);
    void rotateRight(Node<Key, Value>* temp);
    void rotateLeft(Node<Key, Value>* temp);
};




/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template <typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft(Node<Key, Value>* temp){

    Node<Key, Value>* parent = temp->getParent();
    Node<Key, Value>* grandparent = parent->getParent();
    //Need to detect if this rotate left is for parent child being left child of grandparent and n node is right child of parent
    if(temp == parent->getRight() && parent == grandparent->getLeft()){
        //std::cout << "LEFT TRIANGLE ROTATE LEFT" << std::endl;
        bool NodesLeftBelowPreTemp = false;
//-------------------------------------->
        Node<Key, Value>* LeftNodePreTemp = temp->getLeft();
        if(temp->getLeft() != nullptr){
            NodesLeftBelowPreTemp = true;
        }

        grandparent->setLeft(temp);
        temp->setParent(grandparent);
        temp->setLeft(parent);
        parent->setParent(temp);
        //If the bools are true, then connect the nodes to the specific bool name
        if(NodesLeftBelowPreTemp){  //If there is a node below left child of it, then make it become the right child of parent
            parent->setRight(LeftNodePreTemp);
            LeftNodePreTemp->setParent(parent);
        }else{
            parent->setRight(nullptr);
        } 
    }
    //NEED TO DO BALANCES AND STUFF
    //Need to detect if this rotate left is for parent child being the right node for the grandparent and the n node being the right of parent node
    if(temp == parent->getRight() && parent == grandparent->getRight()){
        //std::cout << "RIGHT SLANT ROTATE LEFT" << std::endl;
        if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() == 0){ //If b(n) == 0: b(p) = 0, b(g) = 0, b(n) = 0
            //std::cout << "DA BALANCE IS ZERO SO MAKE EVERYTHING ELSE ZERO" << std::endl;
            static_cast<AVLNode<Key, Value>*>(parent)->setBalance(0); //b(p) = 0
            static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(0);  //b(g) = 0
        }
        Node<Key, Value>* grandparent_parent;
        Node<Key, Value>* parent_left;
        bool parent_left_bool = false;  //Used to figure out if there is a left child node of parent

        if(parent->getLeft() != nullptr){
            parent_left_bool = true;
            parent_left = parent->getLeft();
         }
        if(BinarySearchTree<Key, Value>::root_ == grandparent){
            BinarySearchTree<Key, Value>::root_ = parent;
        }else{  //The else statement is for the node above grandparent to point at the parent node instead of the grandparent node
            grandparent_parent = grandparent->getParent();
            if(grandparent == grandparent_parent->getLeft()){
                //std::cout << "grandparent is on the left" << std::endl;
                grandparent_parent->setLeft(parent);
            }else if(grandparent == grandparent_parent->getRight()){
                //std::cout << "grandparent is on the right" << std::endl;
                grandparent_parent->setRight(parent);
            }
        }
        parent->setParent(grandparent->getParent());
        parent->setLeft(grandparent);

        grandparent->setParent(parent);
        if(parent_left_bool){
            grandparent->setRight(parent_left);
            parent_left->setParent(grandparent);
        }else{
            grandparent->setRight(nullptr);
        }
        if(parent_left_bool){
            grandparent->setRight(parent_left);
            parent_left->setParent(grandparent);
        }else{
            grandparent->setRight(nullptr);
        }
    }
}
template <typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight(Node<Key, Value>* temp){
    //std::cout << "ROTATE RIGHT HELPER FUNCTION" << std::endl;
   
    Node<Key, Value>* parent = temp->getParent();
    Node<Key, Value>* grandparent = parent->getParent();

    //Need to detect if this rotate right is for the right side where the parent node is the right child of grandparent and n is the left child of parent
    if(temp == parent->getLeft() && parent == grandparent->getRight()){
        //std::cout << "RIGHT TRIANGLE ROTATE RIGHT" << std::endl;
 
        bool NodesRightBelowPreTemp = false;
        Node<Key, Value>* RightNodePreTemp = temp->getRight();

        if(temp->getRight() != nullptr){
            NodesRightBelowPreTemp = true;
        }
        grandparent->setRight(temp);
        temp->setParent(grandparent);
        temp->setRight(parent);

        parent->setParent(temp);

        if(NodesRightBelowPreTemp){
            parent->setLeft(RightNodePreTemp);
            RightNodePreTemp->setParent(parent);
        }else{
            parent->setLeft(nullptr);
        }
    }
    //Need to detect if this rotate right is for the left side where the parent node is the left child of grandparent and n node is the left child of parent node and forms a triangle
    if(temp == parent->getLeft() && parent == grandparent->getLeft()){  //Zig Zig Left
        Node<Key, Value>* grandparent_parent;
        Node<Key, Value>* parent_right; //This is if their is a right child node of parent at the beginning of the operation
        bool parent_is_right = false;
        if(BinarySearchTree<Key, Value>::root_ == grandparent){
            BinarySearchTree<Key, Value>::root_ = parent;
        }else{  //The else statement is for the node above grandparent to point at the parent node instead of the grandparent node
            grandparent_parent = grandparent->getParent();
            if(grandparent == grandparent_parent->getLeft()){
                //std::cout << "grandparent is on the left" << std::endl;
                grandparent_parent->setLeft(parent);
            }else if(grandparent == grandparent_parent->getRight()){
                //std::cout << "grandparent is on the right" << std::endl;
                grandparent_parent->setRight(parent);
            }
        }
       
        if(parent->getRight() != nullptr){  //If the right child of the parent node is not nullptr, connect the parent_right node to it
            parent_is_right = true;
            parent_right = parent->getRight();
        }
        parent->setParent(grandparent->getParent());
        parent->setRight(grandparent);
       
        grandparent->setParent(parent);
        if(parent_is_right){  //If parent_is_right is true, that means that the right child of the original parent node location needs to be redirected
            grandparent->setLeft(parent_right);
            parent_right->setParent(grandparent);
        }else{
            grandparent->setLeft(nullptr);
        }
    }
}




template <typename Key, typename Value>
void AVLTree<Key, Value>::Insert_Fix(Node<Key, Value>* temp){
   
   
    Node<Key, Value>* parent = temp->getParent();
    Node<Key, Value>* grandparent = parent->getParent();
   
    int16_t n_balance = static_cast<int16_t>(static_cast<AVLNode<Key, Value>*>(temp)->getBalance());
    int16_t parent_balance = static_cast<int16_t>(static_cast<AVLNode<Key, Value>*>(parent)->getBalance());

    if((parent_balance >= -1 && parent_balance <= 1) && (n_balance >= -1 && n_balance <= 1)){ //PRECONDITION
        //std::cout << "PARENT and N IS IN BALANCE" << std::endl;
    }
    if(parent == nullptr || grandparent == nullptr){  //If nullptr, return
        return;
    }
    //If the parent Node is the left child of the grandparent Node
    if(parent == grandparent->getLeft()){
        //std::cout << "PARENT IS THE LEFT CHILD OF THE GRANDPARENT NODE" << std::endl;
        static_cast<AVLNode<Key, Value>*>(grandparent)->updateBalance(-1);  //b(g) -= 1
        if(static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() == 0){
            return;
        }else if(static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() == -1){
            //std::cout << "b(g) = -1 DUDE" << std::endl;
            Insert_Fix(parent);
        }else if(static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() == -2){
            if(temp == parent->getLeft()){ //Already detected if the parent is the left of grandparent
                rotateRight(temp);
                static_cast<AVLNode<Key, Value>*>(parent)->setBalance(0); //b(p) = 0
                static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(0);  //b(g) = 0
            }else if(temp == parent->getRight()){
                rotateLeft(temp);
                rotateRight(parent);
                if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() == -1){ //If b(n) == -1: b(p) = 0, b(g) = +1, b(n) = 0
                    static_cast<AVLNode<Key, Value>*>(parent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(1);
                    static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0);
                }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() == 0){ //If b(n) == 0: b(p) = 0, b(g) = 0, b(n) = 0
                    static_cast<AVLNode<Key, Value>*>(parent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0);
                }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() == 1){ //If b(n) == 1: b(p) = -1, b(g) = 0, b(n) = 0
                    static_cast<AVLNode<Key, Value>*>(parent)->setBalance(-1);
                    static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0);
                }
            }
           
           
        }
    }else if(parent == grandparent->getRight()){  //If the parent Node is the right child of grandparent Node
        //Right side of equal sign should be derived class most of the times
        //std::cout << "PARENT IS THE RIGHT CHILD OF THE GRANDPARENT NODE" << std::endl;
         static_cast<AVLNode<Key, Value>*>(grandparent)->updateBalance(1);  //b(g) += 1
        if(static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() == 0){
            return;
        }else if(static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() == 1){
            Insert_Fix(parent);
        }else if(static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() == 2){
            //std::cout << "ROTATE RIGHT" << std::endl;
            //std::cout << "ROTATE LEFT" << std::endl;
            //Need to detect to rotate right or to rotate left
            if(temp == parent->getRight()){ //Already detected if the parent is the left of grandparent
                //std::cout << "MUST ROTATE LEFT" << std::endl;
                rotateLeft(temp);
                static_cast<AVLNode<Key, Value>*>(parent)->setBalance(0); //b(p) = 0
                static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(0);  //b(g) = 0
            }else if(temp == parent->getLeft()){
                //std::cout << "MUST ROTATE RIGHT THEN ROTATE LEFT" << std::endl;
                rotateRight(temp);
                rotateLeft(parent);
                /*
                Case 3a: b(n) == 1 then b(p) = 0; b(g) = -1; b(n) = 0;
                – Case 3b: b(n) == 0 then b(p) = 0; b(g) = 0; b(n) = 0;
                – Case 3c: b(n) == -1 then b(p)= 1; b(g) = 0; b(n) = 0;
                */
                if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() == 1){ //If b(n) == -1: b(p) = 0, b(g) = +1, b(n) = 0
                    static_cast<AVLNode<Key, Value>*>(parent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(-1);
                    static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0);
                }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() == 0){ //If b(n) == 0: b(p) = 0, b(g) = 0, b(n) = 0
                    static_cast<AVLNode<Key, Value>*>(parent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0);
                }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() == -1){ //If b(n) == 1: b(p) = -1, b(g) = 0, b(n) = 0
                    static_cast<AVLNode<Key, Value>*>(parent)->setBalance(1);
                    static_cast<AVLNode<Key, Value>*>(grandparent)->setBalance(0);
                    static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0);
                }
            }
        }
    }
    //POST conditions
    //If -1 <= b(n) <= 1 and -1 <= b(p) <= 1 and -1 <= b(g) <= 1
    if((static_cast<AVLNode<Key, Value>*>(temp)->getBalance() >= -1 && static_cast<AVLNode<Key, Value>*>(temp)->getBalance() <= 1) && (static_cast<AVLNode<Key, Value>*>(parent)->getBalance() >= -1 && static_cast<AVLNode<Key, Value>*>(parent)->getBalance() <= 1) && (static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() >= -1 && static_cast<AVLNode<Key, Value>*>(grandparent)->getBalance() <= 1)){
        return;
    }




}
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //INSERT AND RECURSE FROM THE BOTTOM UP
    //When insert, n is the new node insert, p is the parent node, and g is the grandparent node
/*
    INSERT start
    If empty tree => set n as root, b(n) = 0, done!
• Else insert n (by walking the tree to a leaf, p, and
inserting the new node as its child), set balance
to 0, and look at its parent, p
– If b(p) was -1, then b(p) = 0. Done!
– If b(p) was +1, then b(p) = 0. Done!
– If b(p) was 0, then update b(p) and call insert-fix(p, n)
*/
    
    //MAIN NOTES
    //INSERT with while loop
    //Then go to helper function that will use insert fix
    //In the insert fix helper function, there will be another helper function that will be used to calculate the balance for a particular Node
  //To access data members of init accessible modifiable of parent class, need to put parent class and then ::
  if(BinarySearchTree<Key, Value>::root_ == nullptr){
      BinarySearchTree<Key, Value>::root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
      BinarySearchTree<Key, Value>::root_->setParent(nullptr);
      static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_)->setBalance(0);
  }else{
      Node<Key, Value>* temp = BinarySearchTree<Key, Value>::root_; //Connects from Node* to = Node*. Beg Left to Beg Left
      Node<Key, Value>* temp_two = temp;  //All temp and temp_two points to the derived class memory address

      bool left = false;
      bool right = false;
      while(temp != nullptr){
          temp_two = temp;
          if(new_item.first < temp->getKey()){
              //std::cout << "GO LEFT: " << new_item.first << " < " << temp->getKey() << std::endl;
              temp = temp->getLeft();
              left = true;
              right = false;
          }else if(new_item.first > temp->getKey()){
              //std::cout << "GO RIGHT: " << new_item.first << " > " << temp->getKey() << std::endl;
              left = false;
              right = true;
              temp = temp->getRight();
          }else if(new_item.first == temp->getKey()){
              temp->setValue(new_item.second);
              return;
          }
      }
     
      //getStuff for AVLNode returns AVLNode* due to getStuff() most likely going to be on the right side of the equal sign
      temp = new AVLNode<Key, Value>(new_item.first, new_item.second, static_cast<AVLNode<Key, Value>*>(temp_two)); //Converts the first part of the pointer for temp_two which is Node*<Key, Value>* temp_two
      if(left){
          temp_two->setLeft(temp);
          static_cast<AVLNode<Key, Value>*>(temp_two)->updateBalance(-1);
          if(static_cast<AVLNode<Key, Value>*>(temp_two)->getBalance() == -1){  //If after insert, it is 1 or -1, that means that there is no other child node other than the one we just inserted
              Insert_Fix(temp);
          }
      }else if(right){
          static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0);
          temp_two->setRight(temp);
          static_cast<AVLNode<Key, Value>*>(temp_two)->updateBalance(1);
          if(static_cast<AVLNode<Key, Value>*>(temp_two)->getBalance() == 1){  //If after insert, it is 1 or -1, that means that there is no other child node other than the one we just inserted
              Insert_Fix(temp);
          }
      }
  }
/*
      INSERT FOR LEFT from Grandparent
        Precondition: p and n are balanced: {-1,0,-1}
    • Postcondition: g, p, and n are balanced: {-1,0,-1}    RETURN I THINK
    • If p is null or parent(p) is null, return
    • Let g = parent(p)
    • Assume p is left child of g [For right child swap left/right, +/-]
    – b(g) += -1 // Update g's balance to new accurate value for now
    – Case 1: b(g) == 0, return
    – Case 2: b(g) == -1, insertFix(g, p) // recurse up
    – Case 3: b(g) == -2
    • If zig-zig then rotateRight(g); b(p) = b(g) = 0
    • If zig-zag then rotateLeft(p); rotateRight(g);
    – Case 3a: b(n) == -1 then b(p) = 0; b(g) = +1; b(n) = 0;
    – Case 3b: b(n) == 0 then b(p) = 0; b(g) = 0; b(n) = 0;
    – Case 3c: b(n) == +1 then b(p)= -1; b(g) = 0; b(n) = 0;
*/




/*
    INSERT FOR Right from Grandparent
     Precondition: p and n are balanced: {-1,0,-1}
    • Postcondition: g, p, and n are balanced: {-1,0,-1}    RETURN I THINK
    • If p is null or parent(p) is null, return
    • Let g = parent(p)
    • Assume p is right child of g [For left child swap left/right, +/-]
    //This is run when inserting new value
    – b(g) += 1 // Update g's balance to new accurate value for now
    – Case 1: b(g) == 0, return
    – Case 2: b(g) == 1, insertFix(g, p) // recurse up
    – Case 3: b(g) == 2
    • If zig-zig then rotateLeft(g); b(p) = b(g) = 0
    • If zig-zag then rotateRight rotateLeft(g);
    – Case 3a: b(n) == 1 then b(p) = 0; b(g) = -1; b(n) = 0;
    – Case 3b: b(n) == 0 then b(p) = 0; b(g) = 0; b(n) = 0;
    – Case 3c: b(n) == -1 then b(p)= 1; b(g) = 0; b(n) = 0;
*/

}




/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */


template <typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeftRemove(Node<Key, Value>* temp, Node<Key, Value>* C_Node, Node<Key, Value>* G_Node){
    //If it is slanted right, then rotate left
    if(C_Node == temp->getRight() && G_Node == C_Node->getRight()){
        //If root points to the temp node, then we need to make the root point to C Node
        if(BinarySearchTree<Key, Value>::root_ == temp){
            BinarySearchTree<Key, Value>::root_ = C_Node;
        }
        Node<Key, Value>* C_Node_Left;
       
        bool C_Node_Left_bool = false;
        if(C_Node->getLeft() != nullptr){ //If the left of C_Node has some Node
            C_Node_Left = C_Node->getLeft();
            C_Node_Left_bool = true;
        }
        
        Node<Key, Value>* parent = temp->getParent();
        C_Node->setParent(parent);
        if(parent != nullptr){  //Need to detect if parent is not nullptr just in case it is. For instance, if parent of temp is nullptr meaning that temp was originally the root node, can't set the parent node to its left or right or else it would lead to seg fault
            if(temp == parent->getLeft()){
                parent->setLeft(C_Node);
            }else if(temp == parent->getRight()){
                parent->setRight(C_Node);
            }
        }
        C_Node->setLeft(temp);
        if(C_Node_Left_bool){ //If C_Node_Left_bool is true, that means that we need to set the C_Node_Left somewhere on the entire AVL Tree left subtree
            temp->setRight(C_Node_Left);
            C_Node_Left->setParent(temp);
        }else{
            temp->setRight(nullptr);
        }
        temp->setParent(C_Node);


    }else if(C_Node == temp->getLeft() && G_Node == C_Node->getRight()){ //If C_Node is left child of n node and if G_Node is right child of C_Node
        
        Node<Key, Value>* G_Node_Left; 
        bool G_Node_Left_bool = false;
        if(G_Node->getLeft() != nullptr){
            G_Node_Left = G_Node->getLeft();
            G_Node_Left_bool = true;
        }
        G_Node->setParent(temp);
        G_Node->setLeft(C_Node);
        temp->setLeft(G_Node);
        C_Node->setParent(G_Node);

        if(C_Node->getRight() != nullptr){
            C_Node->getRight()->setParent(C_Node);
        }

        if(G_Node_Left_bool){
            C_Node->setRight(G_Node_Left);
            G_Node_Left->setParent(C_Node);
        }else{
            C_Node->setRight(nullptr);
        }
    }


}
template <typename Key, typename Value>
void AVLTree<Key, Value>::rotateRightRemove(Node<Key, Value>* temp, Node<Key, Value>* C_Node, Node<Key, Value>* G_Node){
    //This if is going to detect if it is a slant left and then rotate right
    if(C_Node == temp->getLeft() && G_Node == C_Node->getLeft()){
     //If root points to the temp node, then we need to make the root point to C Node
     //std::cout << "ROTATE RIGHT REMOVE IF CONDITION" << std::endl;
        if(BinarySearchTree<Key, Value>::root_ == temp){
            BinarySearchTree<Key, Value>::root_ = C_Node;
        }
        Node<Key, Value>* C_Node_Right;
       
        bool C_Node_Right_bool = false;
        if(C_Node->getRight() != nullptr){ //If the left of C_Node has some Node
            C_Node_Right = C_Node->getRight();
            C_Node_Right_bool = true;
        }
        Node<Key, Value>* parent = temp->getParent();
        C_Node->setParent(parent);
        if(parent != nullptr){  //Need to detect if parent is not nullptr just in case it is. For instance, if parent of temp is nullptr meaning that temp was originally the root node, can't set the parent node to its left or right or else it would lead to seg fault
            if(temp == parent->getLeft()){
                parent->setLeft(C_Node);
            }else if(temp == parent->getRight()){
                parent->setRight(C_Node);
            }
        }
        C_Node->setRight(temp);
         if(C_Node_Right_bool){ //If C_Node_Left_bool is true, that means that we need to set the C_Node_Left somewhere on the entire AVL Tree left subtree
            temp->setLeft(C_Node_Right);
            C_Node_Right->setParent(temp);
        }else{
            temp->setLeft(nullptr);
        }
        temp->setParent(C_Node);
    }else if(C_Node == temp->getRight() && G_Node == C_Node->getLeft()){ //If condition that will detect if the c node is to the right of the temp node and the g node is to to the left child of the c node which means we must rotate right
        //RIGHT TRIANGLE
        Node<Key, Value>* G_Node_Right; 
        bool G_Node_Right_bool = false;
        if(G_Node->getRight() != nullptr){
            G_Node_Right = G_Node->getRight();
            G_Node_Right_bool = true;
        }
        G_Node->setParent(temp);
        G_Node->setRight(C_Node);
        temp->setRight(G_Node);
        C_Node->setParent(G_Node);

        if(C_Node->getLeft() != nullptr){
            C_Node->getLeft()->setParent(C_Node);
        }

        if(G_Node_Right_bool){
            C_Node->setLeft(G_Node_Right);
            G_Node_Right->setParent(C_Node);
        }else{
            C_Node->setLeft(nullptr);
        }

    }
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::Remove_Fix(Node<Key, Value>* temp, int diff){
   //Remove_Fix Right Maybe
/*
If n is null, return
• Compute next recursive call's arguments now before altering the tree
– Let p = parent(n) and if p is not NULL let ndiff (nextdiff) = +1 if n is a left child and -1 otherwise
• Assume diff = -1 and follow the remainder of this approach, mirroring if diff = +1
• Case 1: b(n) + diff == -2
– [Perform the check for the mirror case where b(n) + diff == +2, flipping left/right and -1/+1]
– Let c = left(n), the smaller (I think) of the children
- Let g = left(c) for b(c) == -1 or b(c) == 0
– Case 1a: b(c) == -1 // zig-zig case
• rotateRight(n), b(n) = b(c) = 0, removeFix(p, ndiff)
– Case 1b: b(c) == 0 // zig-zig case
• rotateRight(n), b(n) = -1, b(c) = +1 // Done!
– Case 1c: b(c) == +1 // zig-zag case
• Let g = right(c)
• rotateLeft(c) then rotateRight(n)
• If b(g) was +1 then b(n) = 0, b(c) = -1, b(g) = 0
• If b(g) was 0 then b(n) = 0, b(c) = 0, b(g) = 0
• If b(g) was -1 then b(n) = +1, b(c) = 0, b(g) = 0
• removeFix(p, ndiff);
• Case 2: b(n) + diff == -1: then b(n) = -1; // Done!
• Case 3: b(n) + diff == 0: then b(n) = 0, removeFix(p, ndiff)
Note:
p = parent of n
n = current node
c = taller child of n
g = grandchild of n


*/
if(temp == nullptr){  //If n is null, return  //<-----------DIS IS DA PROBLEM
    return;
}


Node<Key, Value>* parent = temp->getParent();
int next_diff = 0;
//If parent is not nullptr
if(parent != nullptr){
    if(temp == parent->getLeft()){  //If temp is a left child node of parent
        next_diff += 1;
    }else if(temp == parent->getRight()){ //If temp is a right child node of parent
        next_diff -= 1;
    }
}
//THIS IS REMOVE RIGHT PART
if(diff == -1){
    //std::cout << "IT IS NEGATIVE ONE" << std::endl;
    if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() + diff == -2){ //Zig zig or zig zag
        //std::cout << "ZIG ZIG or ZIG ZAG STUFF: " << std::endl;
        static_cast<AVLNode<Key, Value>*>(temp)->setBalance(-2); //b(n) = -2  //<---------DIS IS DA PROBLEM
        //N
        //C
        //G
        //Since it removes right, you set C to the left child node
        Node<Key, Value>* C_Node = temp->getLeft();
        Node<Key, Value>* G_Node;
        //Need to detect if the c Node's balance is -1. If it is -1, then that means g is the left child node of C Node
        //If it is 0, that also means g is the left child node of C Node
        //If it is 1, that means that g is the right child of C Node
        if(static_cast<AVLNode<Key, Value>*>(C_Node)->getBalance() == -1){
            G_Node = C_Node->getLeft();
            //Now we need to rotate right from a left slant
            //std::cout << "ROTATE RIGHT" << std::endl;
            rotateRightRemove(temp, C_Node, G_Node);
            static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
            static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(0); //b(c) = 0
            Remove_Fix(parent, next_diff);
        }else if(static_cast<AVLNode<Key, Value>*>(C_Node)->getBalance() == 0){
            G_Node = C_Node->getLeft();
            //Now we need to rotate right from a left slant
            //std::cout << "ROTATE RIGHT" << std::endl;
            rotateRightRemove(temp, C_Node, G_Node);
            static_cast<AVLNode<Key, Value>*>(temp)->setBalance(-1); //b(n) = -1
            static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(1); //b(c) = 1
            return;
        }
        else if(static_cast<AVLNode<Key, Value>*>(C_Node)->getBalance() == 1){
            G_Node = C_Node->getRight();
            //Now we need to rotate left, and then rotate right from left triangle
            rotateLeftRemove(temp, C_Node, G_Node); //<-------------- ROTATE LEFT REMOVE IS DA PROBLEM
            rotateRightRemove(temp, G_Node, C_Node);
            /*
            • If b(g) was +1 then b(n) = 0, b(c) = -1, b(g) = 0
            • If b(g) was 0 then b(n) = 0, b(c) = 0, b(g) = 0
            • If b(g) was -1 then b(n) = +1, b(c) = 0, b(g) = 0






          • If b(g) was +1 then b(n) = 0, b(c) = -1, b(g) = 0
          • If b(g) was 0 then b(n) = 0, b(c) = 0, b(g) = 0
          • If b(g) was -1 then b(n) = +1, b(c) = 0, b(g) = 0
            */
          if(static_cast<AVLNode<Key, Value>*>(G_Node)->getBalance() == 1){
              static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
              static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(-1); //b(c) = -1
              static_cast<AVLNode<Key, Value>*>(G_Node)->setBalance(0); //b(g) = 0
          }else if(static_cast<AVLNode<Key, Value>*>(G_Node)->getBalance() == 0){
              static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
              static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(0); //b(c) = 0
              static_cast<AVLNode<Key, Value>*>(G_Node)->setBalance(0); //b(g) = 0
          }else if(static_cast<AVLNode<Key, Value>*>(G_Node)->getBalance() == -1){
              static_cast<AVLNode<Key, Value>*>(temp)->setBalance(1); //b(n) = 1
              static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(0); //b(c) = 0
              static_cast<AVLNode<Key, Value>*>(G_Node)->setBalance(0); //b(g) = 0
          }
        Remove_Fix(parent, next_diff);
    }
  }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() + diff == -1){ //If balance is negative one, that means your done
        //std::cout << "BALANCE IS NEGATIVE ONE. YOUR DONE: " << static_cast<int16_t>(static_cast<AVLNode<Key, Value>*>(temp)->getBalance()) << std::endl; 
        static_cast<AVLNode<Key, Value>*>(temp)->setBalance(-1); //b(n) = -1
        return;
  }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() + diff == 0){ //If balance is zero, that means you recurse
        //std::cout << "BALANCE IS ZERO. RECURSE" << std::endl;
        static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
        Remove_Fix(parent, next_diff);
  }
  
}else if(diff == 1){  //THIS IS REMOVE LEFT PART
      //std::cout << "REMOVE LAST PART" << std::endl;
     if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() + diff == 2){ //Zig zig or zig zag
        //std::cout << "ZIG ZIG or ZIG ZAG STUFF" << std::endl;
        Node<Key, Value>* C_Node = temp->getRight();
        Node<Key, Value>* G_Node;
        if(static_cast<AVLNode<Key, Value>*>(C_Node)->getBalance() == 1){ //If b(c) == 1
            G_Node = C_Node->getRight();
            //ROTATE LEFT since it is a slant right
            rotateLeftRemove(temp, C_Node, G_Node);
            static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
            static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(0); //b(c) = 0
            Remove_Fix(parent, next_diff);
        }
        else if(static_cast<AVLNode<Key, Value>*>(C_Node)->getBalance() == 0){
            G_Node = C_Node->getRight();
            rotateLeftRemove(temp, C_Node, G_Node);
            static_cast<AVLNode<Key, Value>*>(temp)->setBalance(1); //b(n) = 1
            static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(-1); //b(c) = -1
        }else if(static_cast<AVLNode<Key, Value>*>(C_Node)->getBalance() == -1 /*|| static_cast<AVLNode<Key, Value>*>(C_Node)->getBalance() == 0*/){
            
            G_Node = C_Node->getLeft();
            //ROTATE RIGHT AND THEN ROTATE LEFT since it is a right triangle
            rotateRightRemove(temp, C_Node, G_Node);
            rotateLeftRemove(temp, G_Node, C_Node);
/*
If b(g) was -1 then b(n) = 0, b(c) = 1, b(g) = 0
• If b(g) was 0 then b(n) = 0, b(c) = 0, b(g) = 0
• If b(g) was 1 then b(n) = -1, b(c) = 0, b(g) = 0
*/
            if(static_cast<AVLNode<Key, Value>*>(G_Node)->getBalance() == -1){
                static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
                static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(1); //b(c) = 1
                static_cast<AVLNode<Key, Value>*>(G_Node)->setBalance(0); //b(g) = 0
            }else if(static_cast<AVLNode<Key, Value>*>(G_Node)->getBalance() == 0){
                static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
                static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(0); //b(c) = 0
                static_cast<AVLNode<Key, Value>*>(G_Node)->setBalance(0); //b(g) = 0
            }else if(static_cast<AVLNode<Key, Value>*>(G_Node)->getBalance() == 1){
                static_cast<AVLNode<Key, Value>*>(temp)->setBalance(-1); //b(n) = -1
                static_cast<AVLNode<Key, Value>*>(C_Node)->setBalance(0); //b(c) = 0
                static_cast<AVLNode<Key, Value>*>(G_Node)->setBalance(0); //b(g) = 0
            }
            Remove_Fix(parent, next_diff);
        }
    }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() + diff == 1){ //If balance is one, that means your done
        static_cast<AVLNode<Key, Value>*>(temp)->setBalance(1);
        return;
    }else if(static_cast<AVLNode<Key, Value>*>(temp)->getBalance() + diff == 0){ //If balance is zero, that means you recurse
        static_cast<AVLNode<Key, Value>*>(temp)->setBalance(0); //b(n) = 0
        Remove_Fix(parent, next_diff);
    }
}


//Remove_Fix Left Maybe
/*
If n is null, return
• Compute next recursive call's arguments now before altering the tree
– Let p = parent(n) and if p is not NULL let ndiff (nextdiff) = -1 if n is a right child and +1 otherwise
• Assume diff = +1 and follow the remainder of this approach, mirroring if diff = -1
• Case 1: b(n) + diff == 2
– [Perform the check for the mirror case where b(n) + diff == -2, flipping left/right and -1/+1]
– Let c = right(n), the taller of the children
- Let g = right(c) for b(c) == 1 or b(c) == 0
– Case 1a: b(c) == 1 // zig-zig case
• rotateLeft(n), b(n) = b(c) = 0, removeFix(p, ndiff)
– Case 1b: b(c) == 0 // zig-zig case
• rotateRight(n), b(n) = 1, b(c) = -1 // Done!
– Case 1c: b(c) == -1 // zig-zag case
• Let g = left(c)
• rotateRight(c) then rotateLeft(n)
• If b(g) was -1 then b(n) = 0, b(c) = 1, b(g) = 0
• If b(g) was 0 then b(n) = 0, b(c) = 0, b(g) = 0
• If b(g) was 1 then b(n) = -1, b(c) = 0, b(g) = 0
• removeFix(p, ndiff);
• Case 2: b(n) + diff == +1: then b(n) = +1; // Done!
• Case 3: b(n) + diff == 0: then b(n) = 0, removeFix(p, ndiff)
Note:
p = parent of n
n = current node
c = taller child of n
g = grandchild of n
*/
}




template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
/*
Find node, n, to remove by walking the tree
• If n has 2 children, swap positions with in-order successor (or
predecessor) and perform the next step
– Recall if a node has 2 children we swap with its successor or predecessor who
can have at most 1 child and then remove that node
• Let p = parent(n)
• If p is not NULL,
– If n is a left child, let diff = +1
– If n is a left child to be removed, the right subtree now has greater height, so add diff = +1 to
balance of its parent
– if n is a right child, let diff = -1
– If n is a right child to be removed, the left subtree now has greater height, so add diff = -1 to
balance of its parent
– diff will be the amount added to updated the balance of p
• Delete n and update pointers
• “Patch tree” by calling removeFix(p, diff);
*/



//Need to find the remove value first in the AVL Tree
    Node<Key, Value>* temp = BinarySearchTree<Key, Value>::root_;
    while(temp != nullptr){
        if(key < temp->getKey()){
            temp = temp->getLeft();
        }else if(key > temp->getKey()){
            temp = temp->getRight();
        }else if(key == temp->getKey()){
            break;
        }
    }
    if(temp == nullptr){  //If we can't find the node, then we return nothing
      return;
    }

    Node<Key, Value>* parent; //Let parent be parent of n
    bool parent_setted = false; //Detect if parent pointer is set by the successor if condition
    bool left_child = false;  //Detect if left child got removed
    bool right_child = false; //Detect if right got removed
    bool successor_bool = false;  //Detect if we go through successor if condtions
    //Node<Key, Value>* succ;
    Node<Key, Value>* pred;
    Node<Key, Value>* left_child_Node;  //Will be used for the left child only if condition
    Node<Key, Value>* right_child_Node;  //Will be used for the right child only if condition
   
   
    //If there are two childs, then swap with predecessor and then remove
//--------------------------------->
    if(temp->getLeft() != nullptr && temp->getRight() != nullptr){
        pred = BinarySearchTree<Key, Value>::predecessor(temp);
        successor_bool = true;
        int pred_int = static_cast<int16_t>(static_cast<AVLNode<Key, Value>*>(pred)->getBalance());
        int temp_int = static_cast<int16_t>(static_cast<AVLNode<Key, Value>*>(temp)->getBalance());
        static_cast<AVLNode<Key, Value>*>(pred)->setBalance(temp_int);
        static_cast<AVLNode<Key, Value>*>(temp)->setBalance(pred_int);
        BinarySearchTree<Key, Value>::nodeSwap(temp, pred);

        //If there are no child for temp after swapping
        if(temp->getLeft() == nullptr && temp->getRight() == nullptr){
            Node<Key, Value>* parent_temp = temp->getParent();
            parent = temp->getParent();
            parent_setted = true;
        }else if(temp->getLeft() != nullptr && temp->getRight() == nullptr){  //If the temp node has one left child      
            Node<Key, Value>* parent_temp = temp->getParent();
            left_child_Node = temp->getLeft();
            parent = temp->getParent();
            parent_setted = true;
            if(parent_temp->getRight() == temp){
                parent_temp->setRight(left_child_Node);
            }else if(parent_temp->getLeft() == temp){
                parent_temp->setLeft(left_child_Node);
            }
            left_child_Node->setParent(parent_temp);
        }else if(temp->getLeft() == nullptr && temp->getRight() != nullptr){ //If the temp node has one right child
            Node<Key, Value>* parent_temp = temp->getParent();
            right_child_Node = temp->getRight();
            parent = temp->getParent();
            parent_setted = true;
            if(parent_temp->getRight() == temp){
                parent_temp->setRight(right_child_Node);
            }else if(parent_temp->getLeft() == temp){
                parent_temp->setLeft(right_child_Node);
            }
            right_child_Node->setParent(parent_temp);
        }

    }else if(temp->getLeft() != nullptr && temp->getRight() == nullptr){  //If there is one child that being the left child node
        parent = temp->getParent();
        if(BinarySearchTree<Key, Value>::root_ == temp){
            BinarySearchTree<Key, Value>::root_ = temp->getLeft();
            BinarySearchTree<Key, Value>::root_->setParent(nullptr);
        }else{
            left_child_Node = temp->getLeft();
            if(parent->getRight() == temp){
                parent->setRight(left_child_Node);
            }else if(parent->getLeft() == temp){
                parent->setLeft(left_child_Node);
            }
            left_child_Node->setParent(parent);
        }
        parent_setted = true;
    }else if(temp->getLeft() == nullptr && temp->getRight() == nullptr){  //If both of the childs are nullptr, then just remove the temp
        if(BinarySearchTree<Key, Value>::root_ == temp){
            BinarySearchTree<Key, Value>::root_ = nullptr;
        }
        Node<Key, Value>* temp_parent = temp->getParent();
        parent = temp_parent;
        parent_setted = true;
    }else if(temp->getLeft() == nullptr && temp->getRight() != nullptr){  //If there is no left child and the right child exists
        parent = temp->getParent();
        if(BinarySearchTree<Key, Value>::root_ == temp){
            BinarySearchTree<Key, Value>::root_ = temp->getRight();
            BinarySearchTree<Key, Value>::root_->setParent(nullptr);
        }else{
            right_child_Node = temp->getRight();
            if(temp == parent->getRight()){
                parent->setRight(right_child_Node);
                right_child_Node->setParent(parent);
            }else if(temp == parent->getLeft()){
                parent->setLeft(right_child_Node);
                right_child_Node->setParent(parent);
            }
        }
        parent_setted = true;
    }
    int diff = 0;
    //If parent is not nullptr
    if(parent != nullptr){
        if(temp == parent->getLeft()){  //If temp (the node that should be deleted) is on the left child of parent node, then increase diff +1
            diff += 1;
            parent->setLeft(nullptr);
        }else if(temp == parent->getRight()){ //If temp (the node that should be deleted) is on the right child of parent node, then increase diff -1
            diff -= 1;
            parent->setRight(nullptr);
        }else if(right_child_Node == parent->getRight() || left_child_Node == parent->getRight()){
            diff -= 1;
        }else if(left_child_Node == parent->getLeft() || right_child_Node == parent->getLeft()){ 
            diff += 1;
        }
        delete temp;
        Remove_Fix(parent, diff);
    }
}




template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}








#endif













