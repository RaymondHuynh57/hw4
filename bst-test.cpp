#include <iostream>
#include <map>
#include <string>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<int, int> bt;
    bt.insert(std::make_pair(15, 15));
	  bt.insert(std::make_pair(-41, -41));
	  bt.insert(std::make_pair(-32, -32));
    bt.insert(std::make_pair(-39, -39));
    bt.insert(std::make_pair(73, 73));
    
    bt.insert(std::make_pair(138, 138));
	  bt.insert(std::make_pair(-117, -117));
	  bt.insert(std::make_pair(147, 147));
    bt.insert(std::make_pair(-1, -1));
    bt.insert(std::make_pair(65, 65));

    bt.insert(std::make_pair(5, 5));
	  bt.insert(std::make_pair(31, 31));
	  bt.insert(std::make_pair(-72, -72));
    bt.insert(std::make_pair(-50, -50));
    bt.insert(std::make_pair(49, 49));

    bt.insert(std::make_pair(35, 35));
	  bt.insert(std::make_pair(79, 79));
	  bt.insert(std::make_pair(-60, -60));
    bt.insert(std::make_pair(105, 105));
    bt.insert(std::make_pair(-149, -149));

    bt.insert(std::make_pair(-67, -67));
	  bt.insert(std::make_pair(-68, -68));
	  bt.insert(std::make_pair(134, 134));
    bt.insert(std::make_pair(119, 119));
    bt.insert(std::make_pair(58, 58));

    bt.insert(std::make_pair(121, 121));
	  bt.insert(std::make_pair(-22, -22));
	  bt.insert(std::make_pair(46, 46));
    bt.insert(std::make_pair(36, 36));
    bt.insert(std::make_pair(-123, -123));
    bt.insert(std::make_pair(-50, -50));
    bt.remove(-50);
    bt.clear();
    //bt.print();
	  //bt.remove(2);
	  //bt.remove(1);

    //bt.print();

    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int, int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
        cout << "SOMETHING" << endl;
    }
    
    /*
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');
    */


    // AVL Tree Tests
  /*
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
  */
    return 0;
}
