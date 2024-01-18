#include "Bank.h"
#include "Account.h"
#include "BSTree.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

void Bank::ProcessTransactions(string fileName){
    queue<string> transactionQueue;
    string myText;
    ifstream MyReadFile(fileName);

    while (getline (MyReadFile, myText)){
        transactionQueue.push(myText);
    }
    string poppedTransaction;
    

    while (!transactionQueue.empty()) {
        poppedTransaction = transactionQueue.front();
        transactionQueue.pop();
        istringstream parseLine(poppedTransaction);
        char transactionType;
        parseLine >> transactionType;

        if (transactionType == 'O') {
            // open account in account.cpp first constructor
            int accountNumber;
            string firstName, lastName;
            parseLine >> accountNumber >> lastName >> firstName;
            Account* acct = new Account(accountNumber, firstName, lastName);
            // call insert on BSTree
            accounts_.Insert(acct);

        } else if (transactionType == 'D') {
            int accountNumber, fundNumber, amount;
            parseLine >> accountNumber >> fundNumber >> amount;
            if(amount < 0){
                cerr << "Cannot deposit negative amount of money" << endl;
                
            }
            else if(fundNumber > 8 || fundNumber < 0){
                cerr << "Invalid Fund Number" << endl;
                
            } else {
                Account* acct = accounts_.Find(accountNumber);
                if(acct != nullptr){
                    acct->Deposit(fundNumber, amount);
                }else{
                    cerr << "Account not found" << endl; 
                }
                
            }
            

        } else if (transactionType == 'W') {
            int accountNumber, fundNumber, amount;
            parseLine >> accountNumber >> fundNumber >> amount;
            if(amount < 0){
                cerr << "Cannot widthraw negative amount of money" << endl;
                
            }
            else if(fundNumber > 8 || fundNumber < 0){
                cerr << "Invalid Fund Number" << endl;
                
            } else{
                Account* acct = accounts_.Find(accountNumber);
                acct->Withdraw(fundNumber, amount);
            }

        } else if (transactionType == 'T') { // Transfer
            int accountNumber1, accountNumber2, fundNumber1, fundNumber2, amount;
            parseLine >> accountNumber1 >> fundNumber1 >> accountNumber2 >> fundNumber2 >> amount;
            if(amount < 0){
                cerr << "Cannot transfer negative amount of money" << endl;
                
            }
            else if(fundNumber1 > 8 || fundNumber1 < 0 || fundNumber2 > 8 || fundNumber2 < 0){
                cerr << "Invalid Fund Number" << endl;
                
            } else {
                Account* acct = accounts_.Find(accountNumber1);
                Account* toAccount = accounts_.Find(accountNumber2);
                if(acct != nullptr && toAccount != nullptr){
                    acct->Transfer(acct, toAccount, fundNumber1, fundNumber2, amount, poppedTransaction);
                }else{
                    cerr << "Account not found" << endl;  
                }
            }
            
        } else if (transactionType == 'H') {
            int accountNumber;
            parseLine >> accountNumber;
            Account* acct = accounts_.Find(accountNumber);
            if(acct == nullptr){
                cerr << "Account History not found " << endl;
            }else{
                acct->DisplayFullHistory();
            }

        } else if (transactionType == 'F') {
            int accountNumber, fundNumber;
            parseLine >> accountNumber >> fundNumber;
            if(fundNumber > 8 || fundNumber < 0){
                cerr << "Invalid Fund Number" << endl;
            }else{
                Account* acct = accounts_.Find(accountNumber);
                acct->OneFundHistory(fundNumber);
            }

        } else {
            cerr << "Invalid input" << endl;
            break;
        }
    }

    }

void Bank::PrintAccountInformation() const{
    cout << "Account Balances: " << endl;
    cout << " ";
    // inorder traversal:
    // call EndPrint for each account
    accounts_.Display();
}

