#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string holderName;
    string accountType;
    double balance;

public:
    BankAccount();
    BankAccount(int number, string name, string type, double initialBalance);

    int getAccountNumber() const;
    string getHolderName() const;
    string getAccountType() const;
    double getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount);

    void setHolderName(string name);
    void setAccountType(string type);

    void display() const;
};

#endif