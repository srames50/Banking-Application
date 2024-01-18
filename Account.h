#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Fund.h"
#include <string>
#include <vector>
using namespace std;

class Account {

public:
    Account(int id, const string& first, const string& last);

    int getAccountId() const;
    string getFullName() const;

    void Deposit(int fundId, int amount);
    bool Withdraw(int fundId, int amount);
    void Transfer(Account* fromAccount, Account* toAcct, int fromFund, int toFund, int amount, string poppedTransaction);
    void DisplayFullHistory() const;
    void DisplayHistory(int fundId) const;
    void EndPrint() const;
    void OneFundHistory(int fundId) const;

    bool operator==(const Account &a) const;
    bool operator<(const Account &a) const;
    bool operator>(const Account &a) const;
    

private:
    int acct_id_;
    string firstName_;
    string lastName_;
    Fund *funds[9];
    vector<string> pRecord_;
};

#endif 
