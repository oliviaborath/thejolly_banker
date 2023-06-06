//
//  Account.cpp
//  Implementation of Account class.
//  TheJollyBanker
//

#include "Account.h"
#include "Fund.h"
#include <vector>

Account::Account(unsigned int acctID, string firstName, string lastName){
    acctID_ = acctID;
    first_ = firstName;
    last_ = lastName;
    Transaction t('O', first_, last_, acctID, true);
    pTransactions.push_back(t);
    funds[0] = new Fund("Money Market");
    funds[1] = new Fund("Prime Money Market");
    funds[2] = new Fund("Long-Term Bond");
    funds[3] = new Fund("Short-Term Bond");
    funds[4] = new Fund("500 Index Fund");
    funds[5] = new Fund("Capital Value Fund");
    funds[6] = new Fund("Growth Equity Fund");
    funds[7] = new Fund("Growth Index Fund");
    funds[8] = new Fund("Value Fund");
    funds[9] = new Fund("Value Stock Index");
}

Account::~Account(){
}

bool Account::AddToFund(int fundID, int amount){
    if(fundID > 9 || fundID < 0){
        cerr << "Fund ID can't be " << fundID << "." << endl;
        return false;
    }
    if(amount >= 0){
        funds[fundID]->Deposit(amount);
        Transaction t('D', first_, last_, acctID_, fundID, amount, true);
        funds[fundID]->Log(t);
        pTransactions.push_back(t);
        return true;
    }
    else{
        Transaction t('D', first_, last_, acctID_, fundID, amount, false);
        funds[fundID]->Log(t);
        pTransactions.push_back(t);
        cerr << t;
        return false;
    }
}

bool Account::RemoveFunds(int fundID, int amount){
    if(fundID > 9 || fundID < 0){
        cerr << "Fund ID can't be " << fundID << ".";
        return false;
    }
    if(amount <= funds[fundID]->getBalance()){ //Successful withdrawal.
        Transaction t('W', first_, last_, acctID_, fundID, amount, true);
        funds[fundID]->Withdraw(amount);
        funds[fundID]->Log(t);
        pTransactions.push_back(t);
        return true;
    }
    //These will execute in the scenario where joint funds cover enough for a withdrawal.
    else if(fundID == 0 && (amount <= funds[MONEY_MARKET]->getBalance() + funds[PRIME_MONEY_MARKET]->getBalance())){
        return RemoveFromJointFunds(MONEY_MARKET, PRIME_MONEY_MARKET, amount);
    }
    else if(fundID == 1 && (amount <= funds[MONEY_MARKET]->getBalance() + funds[PRIME_MONEY_MARKET]->getBalance())){
        return RemoveFromJointFunds(PRIME_MONEY_MARKET, MONEY_MARKET, amount);
    }
    else if(fundID == 2 && (amount <= funds[LONG_TERM_BOND]->getBalance() + funds[SHORT_TERM_BOND]->getBalance())){
        return RemoveFromJointFunds(LONG_TERM_BOND, SHORT_TERM_BOND, amount);
    }
    else if(fundID == 3 && (amount <= funds[SHORT_TERM_BOND]->getBalance() + funds[LONG_TERM_BOND]->getBalance())){
        return RemoveFromJointFunds(SHORT_TERM_BOND, LONG_TERM_BOND, amount);
    }
    else{
        Transaction t('W', first_, last_, acctID_, fundID, amount, false);
        funds[fundID]->Log(t);
        pTransactions.push_back(t);
        cerr << t;
        return false;
    }
}

bool Account::RemoveFromJointFunds(int fundID1, int fundID2, int amount){
        int toRemove = amount;
        int num = funds[fundID1]->getBalance();
        toRemove -= num;
        funds[fundID1]->Withdraw(num);
        Transaction t('W', first_, last_, acctID_, fundID1, num, true);
        pTransactions.push_back(t);
        funds[fundID1]->Log(t);
        funds[fundID2]->Withdraw(toRemove);
        Transaction t2('W', first_, last_, acctID_, fundID2, toRemove, true);
        pTransactions.push_back(t2);
        funds[fundID2]->Log(t2);
        return true;
    }

void Account::printTransactions(){
    cout << "Displaying All Transactions of " << first_ << " " << last_ << "'s account (Account #" << acctID_ << "):" << endl;
    for(Transaction t: pTransactions)
        cout << t;
}
              
void Account::printFundTransactions(int fundID){
    cout << "Displaying All Transactions for " << first_ << " " << last_ << "'s " << funds[fundID]->getName() << " (Account #" << acctID_ << "):" << endl;
    for(Transaction t: funds[fundID]->getFundTransactions())
        cout << t;
}

string Account::getFirstName() const{
            return first_;
}

string Account::getLastName() const{
            return last_;
}

int Account::getID() const{
            return acctID_;
}


ostream& operator<<(ostream &out, const Account& pAcct){
    out << pAcct.getFirstName() << " " << pAcct.getLastName() << "'s Account (#" << pAcct.getID() << ")" << endl;
    for(int i = 0; i < NUM_OF_FUNDS; i++)
    out << pAcct.funds[i]->getName() << ": " << "$" << pAcct.funds[i]->getBalance() << endl;
    return out;
}

bool Account::operator==(const Account &a) const{
    return acctID_ == a.getID();
}

bool Account::operator<(const Account &a) const{
    return acctID_ < a.getID();
}

bool Account::operator>(const Account &a) const{
    return acctID_ > a.getID();
}
