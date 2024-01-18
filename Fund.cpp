#include "Fund.h"
#include <iostream>
using namespace std;

Fund::Fund(){
    balance_ = 0;
    type_ = "";
}

Fund::Fund(int balance, string type){
    balance_ = balance;
    type_ = type;
}

int Fund::getBalance() const{
    return balance_;
}

string Fund::getType() const{
    return type_;
}

void Fund::Deposit(int amount){
    balance_ += amount;
}

bool Fund::Withdraw(int amount){
    if(balance_ >= amount){
        balance_ -= amount;
        return true;
    } else{
        return false;
    }
}

void Fund::Record(string transaction){
    tHistory_.push_back(transaction);
}

void Fund::PrintTransactions() const{
    for(int i = 0; i < tHistory_.size(); i++){
        cout << tHistory_[i] << endl;
    }
}