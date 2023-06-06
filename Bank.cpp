//
//  Bank.cpp
//  Bank class implementation.
//  TheJollyBanker
//

#include "Bank.h"

Bank::Bank(){
    
}

Bank::~Bank(){
    
}

bool Bank::ReadFile(const string &fileName){
    string line;
    ifstream inFile;
    inFile.open(fileName);
    if(!inFile.is_open()){
        cerr << "file not found" << endl;
        return false;
    }
    while(getline(inFile, line)){
        vector<string> v = tokenize(line);
        AddToQueue(v);
    }
    inFile.close();
    return true;
}

//Tokenize the line of string.
vector<string> Bank::tokenize(string line){
    string buf; //Buffer string.
    stringstream ss(line);
    vector<string> toReturn;
    while(ss >> buf)
        toReturn.push_back(buf);
    return toReturn;
}

bool Bank::AddToQueue(vector<string> commands){
    int acctID, fundID, acctIDEnd, fundIDEnd, amount;
    char type = commands[0].at(0);
    if(type == 'W'){
            acctID = stoi(commands[1].substr(0, 4));
            fundID = stoi(commands[1].substr(4, commands[1].size()));
            amount = stoi(commands[2]);
            Transaction w(type, "", "", acctID, fundID, amount, true);
            pCommands.push(w);
        return true;
    }
    else if(type == 'D'){
            acctID = stoi(commands[1].substr(0, 4));
            fundID = stoi(commands[1].substr(4, commands[1].size()));
            amount = stoi(commands[2]);
            Transaction t(type, "", "", acctID, fundID, amount, true);
            pCommands.push(t);
            return true;
    }
    else if(type == 'T'){
            acctID = stoi(commands[1].substr(0, 4));
            fundID = stoi(commands[1].substr(4, commands[1].size()));
            acctIDEnd = stoi(commands[3].substr(0, 4));
            fundIDEnd = stoi(commands[3].substr(4,commands[3].size()));
            int amount = stoi(commands[2]);
            Transaction t(type, "", "", acctID, fundID, amount, "", "", acctIDEnd, fundIDEnd, true);
            pCommands.push(t);
            return true;
    }
    else if(type == 'H'){
            int IDandFund = stoi(commands[1]);
            Transaction t(type, "", "", IDandFund, true);
            pCommands.push(t);
            return true;
    }
    else if(type == 'O'){
            string firstName = commands[1];
            string lastName = commands[2];
            acctID = stoi(commands[3].substr(0, 4));
            Transaction t(type, firstName, lastName, acctID, true);
            pCommands.push(t);
            return true;
    }
        string str = "";
        for(string s: commands)
            str+= s + " ";
        cerr << "Invalid transaction: " << str;
        return false;
}

bool Bank::ProcessQueue(){
    while(!pCommands.empty()){
        Transaction toProcess = pCommands.front();
        pCommands.pop();
        if(toProcess.getType() == 'W'){
            int acctID = toProcess.getID();
            int fundID = toProcess.getFundID();
            int amount = toProcess.getAmount();
            Account *acc;
            if(pAccounts.Retrieve(acctID, acc))
                acc->RemoveFunds(fundID, amount);
            else
                cerr << "Account " << acctID << " doesn't exist." << endl;
        }
        else if(toProcess.getType() == 'D'){
            int acctID = toProcess.getID();
            int fundID = toProcess.getFundID();
            int amount = toProcess.getAmount();
            Account *acc;
            if(pAccounts.Retrieve(acctID, acc))
                acc->AddToFund(fundID, amount);
            else
                cerr << "Account " << acctID << " doesn't exist." << endl;
        }
        else if(toProcess.getType() == 'T'){
            if(toProcess.getStatus()){
                int acctID = toProcess.getID();
                int fundID = toProcess.getFundID();
                int amount = toProcess.getAmount();
                int destinyID = toProcess.getDestinyID();
                int destinyFundID = toProcess.getFundID2();
                Account *acc;
                Account *destination;
                if(pAccounts.Retrieve(acctID, acc) && pAccounts.Retrieve(destinyID, destination)){
                    acc->RemoveFunds(fundID, amount);
                    destination->AddToFund(destinyFundID, amount);
                }
                else{
                    cerr << "Invalid Transfer: T " << acctID << fundID << " " << amount << " " << destinyID << destinyFundID << endl;
                }
                }
        }
        else if(toProcess.getType() == 'H'){
            if(toProcess.getID() >= 10000 && toProcess.getID() <= 99999){
                Account *acc;
                int fundID = toProcess.getID() % 10;
                int acctID = toProcess.getID() / 10;
                if(pAccounts.Retrieve(acctID, acc)){
                    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
                    acc->printFundTransactions(fundID);
                    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
                }
                else
                    cerr << "Account " << acctID << " doesn't exist." << endl;
            }
        else if(toProcess.getID() >= 1000 && toProcess.getID() <= 9999){
                Account *acc;
                int acctID = toProcess.getID();
                if(pAccounts.Retrieve(acctID, acc)){
                    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
                    acc->printTransactions();
                    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
                }
                else{
                        cerr << "Account " << acctID << " doesn't exist." << endl;
                }
        }
        }
        else if(toProcess.getType() == 'O'){
            Account *dummy;
            if(pAccounts.Retrieve(toProcess.getID(), dummy)){
                cerr << "Account #" << toProcess.getID() << " already exists." << endl;
            }
            else{
                Account *ins_acc = new Account(toProcess.getID(), toProcess.getFirstName(), toProcess.getLastName());
                pAccounts.Insert(ins_acc);
            }
        }
    }
    return true;
}

void Bank::Display(){
    pAccounts.Display();
}
