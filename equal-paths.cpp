#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;

int equalPaths_NumberHelper(Node* root){  //Gets the number of rows till to the root
    if(root == nullptr){
        return 0;
    }else{
        int left_value = equalPaths_NumberHelper(root->left);
        int right_value = equalPaths_NumberHelper(root->right);

        if(left_value > right_value){
            return left_value + 1;
        }else if(right_value > left_value){
            return right_value + 1;
        }else if(left_value == right_value){
            return left_value + 1;
        }
    }
}
// You may add any prototypes of helper functions here
bool equalPaths_Helper(Node* root){
  
}

bool equalPaths(Node * root)
{
    // Add your code below
    //cout << "IT IS EQUAL PATHS YO" << endl;
    if(root == nullptr){
        return true;
    }
    if(root->left != nullptr && root->right == nullptr){
        int value = equalPaths_NumberHelper(root->left);
        if(value > 1){
          return false;
        }
        return true;
    }
    if(root->left == nullptr && root->right != nullptr){
        int value = equalPaths_NumberHelper(root->right);
        if(value > 1){
            return false;
        }
        return true;
    }
    //bool result_final = equalPaths_Helper(root);
    int left = equalPaths_NumberHelper(root->left);
    int right = equalPaths_NumberHelper(root->right);

    if(right == left){
        return true;
    }else{
        return false;
    }
    
}

