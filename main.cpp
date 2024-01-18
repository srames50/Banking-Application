#include "Bank.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char* argv[]){
    Bank JollyBanker;
    string filename = argv[1];
    JollyBanker.ProcessTransactions(filename);
    JollyBanker.PrintAccountInformation();
}