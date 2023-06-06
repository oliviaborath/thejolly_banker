//
//  Fund.h
//  Represents the funds, there are ten funds, with two joint funds. 
//  TheJollyBanker
//

#ifndef Fund_h
#define Fund_h
#include <stdio.h>
#include "Transaction.h"

class Fund {
public:
    Fund(string name);
    ~Fund();
    bool Deposit(int amount);
    bool Withdraw(int amount);
    bool Log(Transaction t);
    vector<Transaction> getFundTransactions();
    string getName() const;
    int getBalance() const;
    
private:
    string name_;
    int balance_ = 0;
    vector<Transaction> pTransactions;
};

#endif /* Fund_h */
