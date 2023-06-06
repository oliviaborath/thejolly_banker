//
//  Bank.h
//  Represents Bank class which reads the txt file and adds the 
//  TheJollyBanker
//

#ifndef Bank_h
#define Bank_h
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include "BSTree.h"
#include "Account.h"
#include "Transaction.h"
using namespace std;

class Bank{
public:
    Bank();
    ~Bank();
    bool ReadFile(const string &fileName);
    bool AddToQueue(vector<string> commands);
    bool ProcessQueue();
    void Display();
private:
    BSTree pAccounts;
    vector<string> tokenize(string line);
    queue<Transaction> pCommands;
};

#endif /* Bank_h */
