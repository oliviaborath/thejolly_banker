//
//  Transaction.h
//  The Transaction class represents a requested transaction, it can be printed out.
//  TheJollyBanker

#ifndef Transaction_h
#define Transaction_h
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Transaction{
    friend ostream& operator<<(ostream &out, const Transaction& t);

public:
   Transaction();
    ~Transaction();
    Transaction(char type, string firstName, string lastName, int acctID, int fundID, int amount, bool s);
    Transaction(char type, string firstName, string lastName, int acctID, int fundID, int amount, string firstName2, string lastName2, int destinyID, int destinyFund, bool s);
    Transaction(char type, string firstName, string lastName, int acctID, bool s);
    Transaction(char type, string firstName, string lastName, int acctID, int fundID, bool s);
    Transaction(char type, string firstName, string lastName, int acctID, int fundID, int acctID2, int fundID2, int amount, bool s);

    char getType() const;
    string getFirstName() const;
    string getLastName() const;
    string getFirstName2() const;
    string getLastName2() const;
    bool getStatus() const;
    int getID() const;
    int getDestinyID() const;
    int getFundID() const;
    int getFundID2() const;
    int getAmount() const;
    
private:
    char type_;
    bool success_;
    string first_, last_, first2_, last2_;
    int acctID_, destinyID_, amount_, fundID_, fundID2_;
};

#endif /* Transaction_h */
