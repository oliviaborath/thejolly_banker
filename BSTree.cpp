//
//  BSTree.cpp
//  Binary Search Tree class implementation.
//  TheJollyBanker
//


#include "BSTree.h"


BSTree::BSTree(){
}

BSTree::~BSTree(){
    Flush();
}
    
bool BSTree::Insert(Account* p_account){
    if (p_account->getID() < 1000 || p_account->getID() > 9999)
        {
            cerr << "Invalid account number: " << p_account->getID() << endl;
            return false;
        }
    else{
        return InsertRecursively(p_account, root_);
    }
    return false;
}

bool BSTree::InsertRecursively(Account* p_account, Node*& root){
    if(root == nullptr){
        root = new Node;
        root->pAcct = p_account;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    int racctID = root->pAcct->getID();
    if(p_account->getID() > racctID){
        InsertRecursively(p_account, root->right);
    }
    else if(p_account->getID() < racctID){
        InsertRecursively(p_account, root->left);
    }
    return false;
}

bool BSTree::Retrieve(int acct_num, Account*& p_account) const{
    return RecursiveRetrieve(acct_num, p_account, root_);
}

bool BSTree::RecursiveRetrieve(int acct_num, Account*& p_account, Node* root) const{
    if(root != nullptr){
        if(acct_num == root->pAcct->getID()){
            p_account = root->pAcct;
            return true;
        }
        if(acct_num < root->pAcct->getID()){
            return RecursiveRetrieve(acct_num, p_account, root->left);
        }
        else{
            return RecursiveRetrieve(acct_num, p_account, root->right);
        }
    }
    else{
        return false;
    }
}

void BSTree::Display() const{
    if(isEmpty())
        cerr << "Error, account list is empty, looks like your file didn't read in properly. Please try again.";
    RecursiveDisplay(root_);
}

void BSTree::RecursiveDisplay(Node* root) const{
    if(root == nullptr)
        return;
    RecursiveDisplay(root->left);
    cout << *root->pAcct;
    RecursiveDisplay(root->right);
}

void BSTree::Flush(){
    delete root_;
    root_ = nullptr;
    return;
}

bool BSTree::isEmpty() const{
    return root_ == nullptr;
}

ostream& operator<<(ostream &out, const BSTree& tree){
    tree.Display();
    return out;
}



