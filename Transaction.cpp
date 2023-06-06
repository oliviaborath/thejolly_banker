//
//  Transaction.cpp
//  Implementation of Transaction class.
//

#include <stdio.h>
#include <iostream>
#include "Transaction.h"
using namespace std;

Transaction::Transaction(){
    
}

Transaction::~Transaction(){
    
};

Transaction::Transaction(char type, string firstName, string lastName, int acctID, int fundID, int amount, bool s){
    type_ = type;
    acctID_ = acctID;
    first_ = firstName;
    last_ = lastName;
    fundID_ = fundID;
    amount_ = amount;
    success_ = s;
}

Transaction::Transaction(char type, string firstName, string lastName, int acctID, int fundID, int amount, string firstName2, string lastName2, int destinyID, int fundID2, bool s){
    type_ = type;
    acctID_ = acctID;
    first_ = firstName;
    last_ = lastName;
    fundID_ = fundID;
    amount_ = amount;
    destinyID_ = destinyID;
    first2_ = firstName2;
    last2_ = lastName2;
    fundID2_ = fundID2;
    success_ = s;
}

Transaction::Transaction(char type, string firstName, string lastName, int acctID, bool s){
    type_ = type;
    first_ = firstName;
    last_ = lastName;
    acctID_ = acctID;
    success_ = s;
}

Transaction::Transaction(char type, string firstName, string lastName, int acctID, int fundID, bool s){
    type_ = type;
    first_ = firstName;
    last_ = lastName;
    acctID_ = acctID;
    fundID_ = fundID;
    success_ = s;
}

Transaction::Transaction(char type, string firstName, string lastName, int acctID, int fundID, int acctID2, int fundID2, int amount, bool s){
    type_ = type;
    first_ = firstName;
    last_ = lastName;
    acctID_ = acctID;
    destinyID_ = acctID2;
    fundID_ = fundID;
    fundID2_ = fundID2;
    success_ = s;
}

bool Transaction::getStatus() const{
    return success_;
}

char Transaction::getType() const{
    return type_;
}

string Transaction::getFirstName() const{
    return first_;
}

string Transaction::getLastName() const{
    return last_;
}

string Transaction::getFirstName2() const{
    return first2_;
}

string Transaction::getLastName2() const{
    return last2_;
}

int Transaction::getID() const{
    return acctID_;
}

int Transaction::getDestinyID() const{
    return destinyID_;
}

int Transaction::getFundID() const{
    return fundID_;
}

int Transaction::getFundID2() const{
    return fundID2_;
}

int Transaction::getAmount() const{
    return amount_;
}

//Can output both failed and successful transactions.
ostream& operator<<(ostream &out, const Transaction& t){
    string funds[10] = {"Money Market", "Prime Money Market", "Long Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index"};
    string output[3] = {"Transaction unsuccessful.", "Transaction successful."};
    string s = "";
    switch(t.getType()){
        case 'D':
            if(t.getStatus()){
                out << "Deposited $" << t.getAmount() << " to " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << ". (Account #" << t.getID() << ")."<< endl;
                break;
            }
            else{
                out << "Failed to deposit $" << t.getAmount() << " to " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << ". (Account #" << t.getID() << ")."<< endl;
                break;
            }
            break;
        case 'W':
            if(t.getStatus()){
                out << "Withdrew $" << t.getAmount() << " from " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << ". (Account #" << t.getID() << ")."<< endl;
                break;
            }
            else{
                out << "Failed to withdraw $" << t.getAmount() << " from " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << ". (Account #" << t.getID() << ")."<< endl;
                break;
            }
        case 'T':
            if(t.getStatus()){
                out << "Transferred $" << t.getAmount() << " from " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << " (Account #" << t.getID() << ") to " << t.getFirstName2() << " " << t.getLastName2() << "'s " << funds[t.getFundID2()] << " (Account #" << t.getDestinyID() << ")." << endl;
                break;
            }
            else{
                out << "Failed to transfer $" << t.getAmount() << " from " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << " (Account #" << t.getID() << ") to " << t.getFirstName2() << " " << t.getLastName2() << "'s " << funds[t.getFundID2()] << " (Account #" << t.getDestinyID() << ")."<< endl;
                break;
            }
        case 'H':
            if(t.getStatus()){
                out << "Displayed all previous transactions for all of " << t.getFirstName() << " " << t.getLastName() << "'s funds. (Account #" << t.getID() << ")." << endl;
                break;
            }
            else{
                out << "Failed to display all previous transactions for all of " << t.getFirstName() << " " << t.getLastName() << "'s funds. (Account #" << t.getID() << ")." << endl;
                break;
            }
        case 'F':
            if(t.getStatus()){
                out << "Displayed all previous transactions for " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << ". (Account #" << t.getID() << ")." << endl;
                break;
            }
            else{
                out << "Failed to display all previous transactions for " << t.getFirstName() << " " << t.getLastName() << "'s " << funds[t.getFundID()] << ". (Account #" << t.getID() << ")." << endl;
                break;
            }
        case 'O':
            if(t.getStatus()){
                out << "Opened an account for client " << t.getFirstName() << " " << t.getLastName() << " (Account #" << t.getID() << ")." << endl;
            }
            else{
                out << "Failed to open an account for client " << t.getFirstName() << " " << t.getLastName() << " (Account #" << t.getID() << ")." << endl;
            }
            break;
        default:
            out << "Blank/Invalid Transaction." << endl;
    }
    return out;
}

