#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const    //const type & means that I can't change the inner contents of memory address
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:  //Inaccessible to the outer class
        //iterator& PreIncrementHelper(Node<Key, Value>* temp, Node<Key, Value>*& result);
        //iterator& PreIncrementHelper(Node<Key, Value>* temp);
        //void PreIncrementHelper(Node<Key, Value>* temp, bool& true_or_false);
        
        friend class BinarySearchTree<Key, Value>;  //Makes iterator accessible to the outer class
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    Node<Key, Value>* getLargestNode() const;
    virtual void insert_Helper(Node<Key, Value>*& root, Node<Key, Value>* prev, const std::pair<const Key, Value>& keyValuePair);
    virtual void remove_Helper(Node<Key, Value>* root, const Key& key);
    void clear_Helper(Node<Key, Value>* root);
    int isBalancedRow_Helper(Node<Key, Value>* root) const;
    bool isBalanced_Helper(Node<Key, Value>* root) const;
    void Destructor_Helper(Node<Key, Value>* root);
protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
   
    current_ = ptr;
    
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/

template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()  //Returns with current_ being a different pointed value from the beginning
{
    // TODO
    Node<Key, Value>* temp = current_;
    current_ = successor(current_);
    if(current_ == temp){
        current_ = nullptr;
    }
    
   
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
    
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    //Node<Key, Value>* temp = root_;
    //Node<Key, Value>* temp_two = temp;
    //NEED A HELPER DESTRUCTOR METHOD THAT DOES POST ORDER DELETE
  
    Destructor_Helper(root_);
    //delete root_;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::Destructor_Helper(Node<Key, Value>* root){
    if(root == nullptr){    //EOL or EOBS
        return;
    }else{
        //POST ORDER DELETE
        Destructor_Helper(root->getLeft());
        Destructor_Helper(root->getRight());
        delete root;    //Affects through everything
    }
}
/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const //iterator constructor that takes place in this method is Accessible because of friend inside protected of iterator class
{
    
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());  //iterator constructor that takes place in this method is Accessible because of friend inside protected of iterator class
    
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/

/*
This function will insert a new node into the tree with the specified key
and value. There is no guarantee the tree is balanced before or after the insertion. If key is already in the tree, you should overwrite the current value with the updated value. Runtime is O(h).
*/
template <class Key, class Value>
void BinarySearchTree<Key,Value>::insert_Helper(Node<Key, Value>*& root, Node<Key, Value>* prev, const std::pair<const Key, Value>& keyValuePair){


}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //std::cout << "BST INSERT" << std::endl;
    if(root_ == nullptr){
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        root_->setLeft(nullptr);
        root_->setRight(nullptr);
    }else{
        Node<Key, Value>* temp = root_;
        Node<Key, Value>* temp_two = temp;
        bool left = false;  //If it is true, that means you set the parent Node to contain the new node to the left
        bool right = false; //If it is true, that means you set the parent Node to contain the new node to the right
        bool middle = false;
        while(root_ != nullptr){
            left = false;
            right = false;
            temp_two = root_;
            if(keyValuePair.first < root_->getKey()){
                left = true;
                root_ = root_->getLeft();
            }else if(keyValuePair.first > root_->getKey()){
                right = true;
                root_ = root_->getRight();  //THIS IS THE PROBLEM
            }else if(keyValuePair.first == root_->getKey()){
                middle = true;
                root_->setValue(keyValuePair.second);
                break;
            }
        }
        if(middle){

        }else{
            root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp_two);
        }

        if(left == true){
            root_->getParent()->setLeft(root_);
        }else if(right == true){
            root_->getParent()->setRight(root_);
        }
        root_ = temp;
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove_Helper(Node<Key, Value>* root, const Key& key){
   
}
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* temp = root_; //Temp pointers can modify the public memory addresses
    int counter = 0;
    while(temp != nullptr){
        if(key == temp->getKey()){
            if(temp->getLeft() != nullptr && temp->getRight() == nullptr){ //If the left is nullptr
                ++counter;
                if(root_ == temp){  //If root is equal to temp
                    root_ = temp->getLeft();  //<-------- DIS IS A PROBLEM DUDE
                }
                bool right = false;
                bool left = false;


                if(temp->getParent() != nullptr){
                    if(temp == temp->getParent()->getLeft()){
                        left = true;
                    }else if(temp == temp->getParent()->getRight()){
                        right = true;
                    }
                }

                temp->getLeft()->setParent(temp->getParent());
                if(temp->getParent() != nullptr){ //REMOVE IS DA PROBLEM
                    if(right){
                       temp->getParent()->setRight(temp->getLeft());
                    }else if(left){
                        temp->getParent()->setLeft(temp->getLeft());
                    }
                }
                
            }else if(temp->getLeft() == nullptr && temp->getRight() != nullptr){  //If the right is nullptr
                ++counter;
                if(root_ == temp){
                    root_ = temp->getRight();
                }
                bool right = false;
                bool left = false;
                if(temp->getParent() != nullptr){ //Prevent seg fault errors
                    if(temp->getParent()->getLeft() == temp){
                        temp->getParent()->setLeft(temp->getRight());
                    }else if(temp->getParent()->getRight() == temp){
                        temp->getParent()->setRight(temp->getRight());
                    }
                }
                temp->getRight()->setParent(temp->getParent());
            }else if(temp->getLeft() != nullptr && temp->getRight() != nullptr){  //If the both childs exist when removing, switch with predecessor and then remove it
                ++counter;
                //std::cout << "PREDECESSOR INSERT" << std::endl;
                Node<Key, Value>* pred = predecessor(temp);
                nodeSwap(temp, pred);
                if(temp->getLeft() != nullptr && temp->getRight() == nullptr){ //If the left is nullptr
                    ++counter;
                    temp->getLeft()->setParent(temp->getParent());
                    if(temp->getParent() != nullptr){
                        if(temp->getParent()->getLeft() == temp){
                            temp->getParent()->setLeft(temp->getLeft());
                        }else if(temp->getParent()->getRight() == temp){
                            temp->getParent()->setRight(temp->getLeft());
                        }
                    }
                
                }else if(temp->getLeft() == nullptr && temp->getRight() != nullptr){  //If the right is nullptr
                    ++counter;
                    temp->getRight()->setParent(temp->getParent());
                    if(temp->getParent() != nullptr){
                        if(temp->getParent()->getLeft() == temp){
                            temp->getParent()->setLeft(temp->getRight());
                        }else if(temp->getParent()->getRight() == temp){
                            temp->getParent()->setRight(temp->getRight());
                        }
                    }
               
                }else if(temp->getLeft() == nullptr && temp->getRight() == nullptr){
                    Node<Key, Value>* temp_no_child = temp->getParent();
                    if(temp_no_child->getLeft() == temp){
                        temp_no_child->setLeft(nullptr);
                    }else if(temp_no_child->getRight() == temp){
                        temp_no_child->setRight(nullptr);
                    }

                }
            }
            Node<Key, Value>* end_result = temp->getParent();
            if(end_result != nullptr){  //Make sure end_result being nullptr leads to seg faults
                 if(end_result->getLeft() == temp){
                      end_result->setLeft(nullptr);
                 }else if(end_result->getRight() == temp){
                      end_result->setRight(nullptr);
                 }
            }
           
            delete temp;
            temp = nullptr;
            if(counter == 0){
                root_ = nullptr;
            }

        }else if(key < temp->getKey()){
            temp = temp->getLeft();
        }else if(key > temp->getKey()){
            temp = temp->getRight();
        }
        ++counter;
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    //Left subtree and the very right for two child existing
    //Predecessor is the problem
    Node<Key, Value>* temp = current;
    Node<Key, Value>* temp_temp = temp;
    //std::cout << "PREDECESSOR" << std::endl;
    //if(current != nullptr){
        //std::cout << "CURRENT IS NOT NULLPTR" << std::endl;
    //}
    if((current->getLeft() != nullptr && current->getRight() != nullptr) || (current->getLeft() != nullptr && current->getRight() == nullptr)){  //If both childs exist, then that menas it will go left subtree and then right most Node
        //std::cout << "FIRST PRED IF CONDITION" << std::endl;
        temp = temp->getLeft();
        while(temp->getRight() != nullptr){
            temp = temp->getRight();
        }
    }else if((current->getLeft() == nullptr && current->getRight() != nullptr) || (current->getLeft() == nullptr && current->getRight() == nullptr)){  //No left for predecessor or no left or right for predecessor means it goes up and choose the parent node of the right node
        Node<Key, Value>* temp_two = temp;
        //std::cout << "SECOND PRED IF CONDITION" << std::endl;
        while(temp->getParent() != nullptr){
            temp_two = temp;
            //std::cout << "TEMP IN WHILE LOOP: " << temp->getKey() << " " << temp->getValue() << std::endl;
            temp = temp->getParent();

            if(temp_two == temp->getRight()){
                break;
            }
        }
        //std::cout << "SECOND PRED IF CONDITION RESULT: " << temp->getKey() << " " << temp->getValue() << std::endl;
    }

    if(temp_temp->getKey() < temp->getKey()){
        return temp_temp;
    }
    return temp;
}
//iterators can't access the methods of the Binary Search Tree. The inner class can't access methods from the outer class
template <typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current){
    //Two children Node existing. Right subtree and then go to the leftmost
    //If the right child existed, then go to the right and then leftmost
    //If no right subtree, then go to the Node that is a left child of parent node and then point to parent node
        Node<Key, Value>* temp = current;
        Node<Key, Value>* temp_temp = temp;
        if((current->getLeft() != nullptr && current->getRight() != nullptr) || (current->getLeft() == nullptr && current->getRight() != nullptr)){  //Two child Nodes existed or if right child existed
            temp = temp->getRight();
            while(temp->getLeft() != nullptr){
                temp = temp->getLeft();
            }
        }

        else if(current->getLeft() != nullptr && current->getRight() == nullptr){  //If Right Child does not exist, then go up instead. Parent Node of Left Node
            Node<Key, Value>* temp_two = temp;
            while(temp->getParent() != nullptr){
                temp_two = temp;
                temp = temp->getParent();
                if(temp->getLeft() == temp_two){
                    break;
                }
            }
        }else if(current->getLeft() == nullptr && current->getRight() == nullptr){
            Node<Key, Value>* temp_two = current;
            while(temp->getParent() != nullptr){
                temp_two = temp;
                temp = temp->getParent();
                if(temp->getLeft() == temp_two){
                    break;
                }
            }
        }
       
        if(temp_temp->getKey() > temp->getKey()){
            return temp_temp;
        }
        return temp;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_Helper(Node<Key, Value>* root){
    if(root == nullptr){
        return;
    }else{
        clear_Helper(root->getLeft());
        clear_Helper(root->getRight());
        delete root;
        return;
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    //POST-order
    clear_Helper(root_);
    root_ = nullptr;
}

template <typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getLargestNode() const{
    Node<Key, Value>* temp = root_;

    while(temp->getRight() != nullptr){
        temp = temp->getRight();
    }
    return temp;
}
/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* temp = root_;
    if(root_ == nullptr){
        return root_;
    }
    while(temp->getLeft() != nullptr){
        temp = temp->getLeft();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* temp = root_;
    while(temp != nullptr){
        if(key == temp->getKey()){
            break;
        }else if(key > temp->getKey()){
            temp = temp->getRight();
        }else if(key < temp->getKey()){
            temp = temp->getLeft();
        }
    }
    return temp;
}

/**
 * Return true iff the BST is balanced.
 */

template <typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedRow_Helper(Node<Key, Value>* root) const{ //Method can access data variables in the same class level.
    if(root == nullptr){
        return 0;
    }else{
        //Post-order
        int left_value = isBalancedRow_Helper(root->getLeft());
        int right_value = isBalancedRow_Helper(root->getRight());
        if(left_value > right_value){
            return left_value + 1;
        }else if(right_value > left_value){
            return right_value + 1;
        }else{
            return left_value + 1;
        }
    }
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced_Helper(Node<Key, Value>* root) const{
   if(root == nullptr){
        return true;
   }else{
        //Pre-Order From the root
        int left_row_value = isBalancedRow_Helper(root->getLeft()); //Branches off to a different recursion
        int right_row_value = isBalancedRow_Helper(root->getRight()); //Branches off to a different recursion

        int difference = right_row_value - left_row_value;
        if(difference > 1 || difference < -1){
            return false; //Doesn't allow the BST to recurse down further and go up the BST instead earlier
        }

        bool left_bool = isBalanced_Helper(root->getLeft());
        bool right_bool = isBalanced_Helper(root->getRight());

        if(left_bool && right_bool){
            return true;
        }else{
            return false;
        }

   }
}
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    bool result_final = isBalanced_Helper(root_);
    return result_final;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
