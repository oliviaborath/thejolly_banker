//
//  BSTree.h
//  Binary Search Tree of accounts.
//  TheJollyBanker
//

#ifndef BSTree_h
#define BSTree_h
#include "Account.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class BSTree {
friend ostream& operator<<(ostream &out, const BSTree& tree);
public:
 BSTree();
 ~BSTree();
 
bool Insert(Account* p_account);
void Flush();
bool Retrieve(int acct_ID, Account*& p_account) const;
void Display() const;
bool isEmpty() const;
int getCount() const;

private:
struct Node{
    Account* pAcct;
    Node* right;
    Node* left;
};
    Node* root_ = nullptr;
    bool RecursiveRetrieve(int acct_ID, Account*& p_account, Node* root) const;
    bool InsertRecursively(Account* p_account, Node* &root);
    void RecursiveDisplay(Node* root) const;
    void Flush(Node* root);
};



#endif /* BSTree_h */
