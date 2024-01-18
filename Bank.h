#ifndef BANK_H
#define BANK_H

#include "BSTree.h"

class Bank {

public:
    void ProcessTransactions(string fileName);
    void PrintAccountInformation() const;

private:
    BinarySearchTree accounts_;
};

#endif
