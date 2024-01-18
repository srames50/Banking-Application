#include "BSTree.h"
#include <iostream>
using namespace std;


BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& bst) {

}

BinarySearchTree::~BinarySearchTree() {

}




bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
}


bool BinarySearchTree::Retrieve(const int& acct_number, Account*& account) const {
    return RetrieveHelper(acct_number, account, root_);
}

bool BinarySearchTree::RetrieveHelper(int acct_num, Account*& p_account, Node* root) const{
    if(root != nullptr){
        if(acct_num == root->p_account->getAccountId()){
            p_account = root->p_account;
            return true;
        }
        if(acct_num < root->p_account->getAccountId()){
            return RetrieveHelper(acct_num, p_account, root->left);
        }
        else{
            return RetrieveHelper(acct_num, p_account, root->right);
        }
    }else{
        return false; 
    }
}


bool BinarySearchTree::Insert(Account* account) {
    return InsertHelper(account, root_);
}

bool BinarySearchTree::InsertHelper(Account* p_account, Node*& root){
    if(root == nullptr){
        root = new Node;
        root->p_account = p_account;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    
    int rootAcctID = root->p_account->getAccountId();
    if(p_account->getAccountId() > rootAcctID){
        InsertHelper(p_account, root->right);
    }
    else if(p_account->getAccountId() < rootAcctID){
        InsertHelper(p_account, root->left);
    }else{
        cerr << "Invalid Account ID, Account ID already in use" << endl;
        return false;
    }
    return false;
}

void BinarySearchTree::Display() const {
   DisplayHelper(root_);
}

void BinarySearchTree::DisplayHelper(Node* root) const{
    if(root == nullptr){
        cout << "root is nullptr" << endl;
    }
    if(root->left != nullptr){
        DisplayHelper(root->left);
    } 
    root->p_account->EndPrint();
    if(root->right != nullptr){
        DisplayHelper(root->right);
    }
}

Account* BinarySearchTree::Find(int acct_num){
    return FindHelper(acct_num, root_);
}

Account* BinarySearchTree::FindHelper(int acct_num, Node*& root){
    if(root == nullptr){
        return nullptr;
    }
    if(root->p_account->getAccountId() == acct_num){
            return root->p_account;
    }else if(root->p_account->getAccountId() < acct_num){
        return FindHelper(acct_num, root->right);
    }else{
        return FindHelper(acct_num, root->left);
    }
    
}


