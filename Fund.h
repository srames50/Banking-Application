#ifndef FUND_H
#define FUND_H

#include <string>
#include <vector>
using namespace std;

class Fund {

public:
    Fund();
    Fund(int balance, string type);

    int getBalance() const;
    string getType() const;
    
    void Deposit(int amount);
    bool Withdraw(int amount);

    void Record(string transaction);
    void PrintTransactions() const;

private:
    int balance_;
    string type_;
    vector<string> tHistory_;
};

#endif 
