//
//  Fund.cpp
//  Implementation of the Fund class.
//  TheJollyBanker
//


#include <stdio.h>
#include "Fund.h"

Fund::Fund(string name){
    name_ = name;
}

Fund::~Fund(){
    
}

bool Fund::Deposit(int amount){
    if(amount >= 0){
    balance_ += amount;
    return true;
    }
    return false;
}

bool Fund::Withdraw(int amount){
    if(amount >= 0 && amount <= balance_){
        balance_ -= amount;
        return true;
    }
        return false;
}

bool Fund::Log(Transaction t){
    pTransactions.push_back(t);
    return true;
}

vector<Transaction> Fund::getFundTransactions(){
    return pTransactions;
}

string Fund::getName() const{
    return name_;
}

int Fund::getBalance() const{
    return balance_;
}
