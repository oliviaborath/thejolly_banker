//
//  Account.h
//  TheJollyBanker
//

#ifndef Account_h
#define Account_h
#include "Fund.h"
#include "Transaction.h"
#include <iostream>
#include <vector>
#include <string>
const int NUM_OF_FUNDS = 10;
const int MONEY_MARKET = 0;
const int PRIME_MONEY_MARKET = 1;
const int LONG_TERM_BOND = 2;
const int SHORT_TERM_BOND = 3;

class Account{
friend ostream& operator<<(ostream &out, const Account& pAcct);
public:
    Account();
    Account(unsigned int accID, string firstName, string lastName);
    ~Account();
    bool AddToFund(int fundID, int amount);
    bool RemoveFunds(int fundID, int amount);
   bool RemoveFromJointFunds(int fundID1, int fundID2, int amount);
    void printTransactions();
    void printFundTransactions(int fundID);
    string getFirstName() const;
    string getLastName() const;
    int getID() const;
    
    bool operator==(const Account &a) const;
    bool operator<(const Account &a) const;
    bool operator>(const Account &a) const;
    
     
private:
    string first_, last_;
    int acctID_;
    Fund *funds[NUM_OF_FUNDS];
    vector<Transaction>pTransactions;
};

#endif /* Account_h */
