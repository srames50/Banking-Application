#include "Account.h"
#include "Fund.h"
#include <string>
#include <iostream>
using namespace std;

Account::Account(int id, const string& first, const string& last){
    this->acct_id_ = id;
    this->firstName_ = first;
    this->lastName_ = last;
    
    funds[0] = new Fund(200, "  Money Market");
    funds[1] = new Fund(0, "  Prime Money Market");
    funds[2] = new Fund(0, "  Long-Term Bond");
    funds[3] = new Fund(0, "  Short-Term Bond");
    funds[4] = new Fund(0, "  500 Index Fund");
    funds[5] = new Fund(0, "  Capital Value Fund");
    funds[6] = new Fund(0, "  Growth Equity Fund");
    funds[7] = new Fund(0, "  Growth Index Fund");
    funds[8] = new Fund(0, "  International Fund");
    
}

int Account::getAccountId()const{
    return acct_id_;
}

string Account::getFullName() const{
    return lastName_ + " " + firstName_ + " ";
    
}

void Account::Deposit(int fundId, int amount){
    funds[fundId]->Deposit(amount);
    string s = ("   D " + to_string(acct_id_) + " " + to_string(fundId) + " " + to_string(amount));
    funds[fundId]->Record(s);
}

bool Account::Withdraw(int fundId, int amount){
    if(fundId > 8 || fundId < 0){
        cerr << "Fund ID can't be " << fundId << ".";
        return false;
    }
    if(amount <= funds[fundId]->getBalance()){
        string s = ("   W " + to_string(acct_id_) + " " + to_string(fundId) + " " + to_string(amount));
        funds[fundId]->Withdraw(amount);
        funds[fundId]->Record(s);
        return true;
    }
    // if withdraw can be covered by other allowed fund
    else if(fundId == 0 && (amount <= funds[0]->getBalance() + funds[1]->getBalance())){
        int fullFirstFund = funds[0]->getBalance();
        int amtNeeded = amount - fullFirstFund;
        string s1 = ("   W " + to_string(acct_id_) + " " + to_string(0) + " " + to_string(fullFirstFund));
        string s2 = ("   W " + to_string(acct_id_) + " " + to_string(1) + " " + to_string(amtNeeded));
        funds[0]->Withdraw(fullFirstFund);
        funds[0]->Record(s1);
        funds[1]->Withdraw(amtNeeded);
        funds[1]->Record(s2);
        return true;
    }
    else if(fundId == 1 && (amount <= funds[0]->getBalance() + funds[1]->getBalance())){
        int fullFirstFund = funds[1]->getBalance();
        int amtNeeded = amount - fullFirstFund;
        string s1 = ("   W " + to_string(acct_id_) + " " + to_string(1) + " " + to_string(fullFirstFund));
        string s2 = ("   W " + to_string(acct_id_) + " " + to_string(0) + " " + to_string(amtNeeded));
        funds[1]->Withdraw(fullFirstFund);
        funds[1]->Record(s1);
        funds[0]->Withdraw(amtNeeded);
        funds[0]->Record(s2);
        return true;
    }
    else if(fundId == 2 && (amount <= funds[2]->getBalance() + funds[3]->getBalance())){
        int fullFirstFund = funds[2]->getBalance();
        int amtNeeded = amount - fullFirstFund;
        string s1 = ("   W " + to_string(acct_id_) + " " + to_string(2) + " " + to_string(fullFirstFund));
        string s2 = ("   W " + to_string(acct_id_) + " " + to_string(3) + " " + to_string(amtNeeded));
        funds[2]->Withdraw(fullFirstFund);
        funds[2]->Record(s1);
        funds[3]->Withdraw(amtNeeded);
        funds[3]->Record(s2);
        return true;
    }
    else if(fundId == 3 && (amount <= funds[3]->getBalance() + funds[2]->getBalance())){
        int fullFirstFund = funds[3]->getBalance();
        int amtNeeded = amount - fullFirstFund;
        string s1 = ("   W " + to_string(acct_id_) + " " + to_string(3) + " " + to_string(fullFirstFund));
        string s2 = ("   W " + to_string(acct_id_) + " " + to_string(2) + " " + to_string(amtNeeded));
        funds[3]->Withdraw(fullFirstFund);
        funds[3]->Record(s1);
        funds[2]->Withdraw(amtNeeded);
        funds[2]->Record(s2);
        return true;
    }
    else{ // failed
        string s = ("   W " + to_string(acct_id_) + " " + to_string(fundId) + " " + to_string(amount) + " (Failed)");
        funds[fundId]->Record(s);
        return false;
    }
}


void Account::Transfer(Account* fromAccount, Account* toAccount, int fromFund, int toFund, int amount, string poppedTransaction){
    if(toAccount->acct_id_ != fromAccount->acct_id_){
        if(fromAccount->funds[fromFund]->getBalance() >= amount){// if we have enough to direct make transfer
            funds[fromFund]->Record("  " + poppedTransaction);
            toAccount->funds[toFund]->Record("  " + poppedTransaction);
            toAccount->funds[toFund]->Deposit(amount);
            fromAccount->funds[fromFund]->Withdraw(amount);
        } else if(fromFund == 0 && (amount <= fromAccount->funds[0]->getBalance() + fromAccount->funds[1]->getBalance())){
            int fullFirstFund = fromAccount->funds[0]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(0) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(1) + " " + to_string(amtNeeded));
            funds[0]->Withdraw(fullFirstFund);
            funds[0]->Record(s1);
            funds[1]->Withdraw(amtNeeded);
            funds[1]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        } else if(fromFund == 1 && (amount <= fromAccount->funds[0]->getBalance() + fromAccount->funds[1]->getBalance())){
            int fullFirstFund = funds[1]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(1) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(0) + " " + to_string(amtNeeded));
            funds[1]->Withdraw(fullFirstFund);
            funds[1]->Record(s1);
            funds[0]->Withdraw(amtNeeded);
            funds[0]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        } else if(fromFund == 2 && (amount <= fromAccount->funds[2]->getBalance() + fromAccount->funds[3]->getBalance())){
            int fullFirstFund = funds[2]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(2) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(3) + " " + to_string(amtNeeded));
            funds[2]->Withdraw(fullFirstFund);
            funds[2]->Record(s1);
            funds[3]->Withdraw(amtNeeded);
            funds[3]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        } else if(fromFund == 3 && (amount <= fromAccount->funds[3]->getBalance() + fromAccount->funds[2]->getBalance())){
            int fullFirstFund = funds[3]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(3) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(2) + " " + to_string(amtNeeded));
            funds[3]->Withdraw(fullFirstFund);
            funds[3]->Record(s1);
            funds[2]->Withdraw(amtNeeded);
            funds[2]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        }
        else{ // dont have enough for transfer
            funds[fromFund]->Record("  " + poppedTransaction + " Failed");
            toAccount->funds[toFund]->Record("  " + poppedTransaction + " Failed");
            cerr << "Error: Insufficient funds for transfer." << endl; 
        }
    }
    // transfer within account
    if(toAccount->acct_id_ == fromAccount->acct_id_){
        if(fromAccount->funds[fromFund]->Withdraw(amount)){
            funds[toFund]->Deposit(amount);
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(fromFund) + " " + to_string(acct_id_) + " " + to_string(toFund) + " " + to_string(amount));
            funds[fromFund]->Record(s1);
            funds[toFund]->Record(s1);
        } else if(fromFund == 0 && (amount <= fromAccount->funds[0]->getBalance() + fromAccount->funds[1]->getBalance())){
            int fullFirstFund = fromAccount->funds[0]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(0) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(1) + " " + to_string(amtNeeded));
            funds[0]->Withdraw(fullFirstFund);
            funds[0]->Record(s1);
            funds[1]->Withdraw(amtNeeded);
            funds[1]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        } else if(fromFund == 1 && (amount <= fromAccount->funds[0]->getBalance() + fromAccount->funds[1]->getBalance())){
            int fullFirstFund = funds[1]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(1) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(0) + " " + to_string(amtNeeded));
            funds[1]->Withdraw(fullFirstFund);
            funds[1]->Record(s1);
            funds[0]->Withdraw(amtNeeded);
            funds[0]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        } else if(fromFund == 2 && (amount <= fromAccount->funds[2]->getBalance() + fromAccount->funds[3]->getBalance())){
            int fullFirstFund = funds[2]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(2) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(3) + " " + to_string(amtNeeded));
            funds[2]->Withdraw(fullFirstFund);
            funds[2]->Record(s1);
            funds[3]->Withdraw(amtNeeded);
            funds[3]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        } else if(fromFund == 3 && (amount <= fromAccount->funds[3]->getBalance() + fromAccount->funds[2]->getBalance())){
            int fullFirstFund = funds[3]->getBalance();
            int amtNeeded = amount - fullFirstFund;
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(3) + " " + to_string(fullFirstFund));
            string s2 = ("   T " + to_string(acct_id_) + " " + to_string(2) + " " + to_string(amtNeeded));
            funds[3]->Withdraw(fullFirstFund);
            funds[3]->Record(s1);
            funds[2]->Withdraw(amtNeeded);
            funds[2]->Record(s2);
            toAccount->funds[toFund]->Deposit(amount);
            return;
        } else{
            string s1 = ("   T " + to_string(acct_id_) + " " + to_string(fromFund) + " " + to_string(acct_id_) + " " + to_string(toFund) + " " + to_string(amount) + " Failed");
            funds[fromFund]->Record(s1);
            funds[toFund]->Record(s1);
            cerr << "Error: Insufficient funds for transfer." << endl;
            
            //record failed transfer?
        }
    }
    
}

void Account::DisplayFullHistory() const{
    cout << "Transaction History for " + getFullName() + "by fund." << endl;
    for(int i = 0; i < 9; i++){
        DisplayHistory(i);
    }
}

void Account::EndPrint() const{
    cout << getFullName() + "Account ID: " + to_string(getAccountId()) << endl;
    for(int i = 0; i < 9; i++){
        cout << funds[i]->getType() + ": $" + to_string(funds[i]->getBalance()) << endl;
    }
}

void Account::DisplayHistory(int fundId) const{
    cout << funds[fundId]->getType() + ": $" + to_string(funds[fundId]->getBalance()) << endl;
    funds[fundId]->PrintTransactions();
}

void Account::OneFundHistory(int fundId) const{
    cout << "Transaction History for " + getFullName() << endl;
    cout << funds[fundId]->getType() + ": $" + to_string(funds[fundId]->getBalance()) << endl;
    funds[fundId]->PrintTransactions();
}

bool Account::operator==(const Account &a) const{
    return acct_id_ == a.getAccountId();
}

bool Account::operator<(const Account &a) const{
    return acct_id_ < a.getAccountId();
}

bool Account::operator>(const Account &a) const{
    return acct_id_ > a.getAccountId();
}