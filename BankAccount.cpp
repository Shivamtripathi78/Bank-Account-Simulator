#include "BankAccount.h"
#include <iostream>
#include <iomanip>

BankAccount::BankAccount() {
    accountNumber = 0;
    holderName = "";
    accountType = "";
    balance = 0;
}

BankAccount::BankAccount(int number, string name, string type,
                         double initialBalance) {
    accountNumber = number;
    holderName = name;
    accountType = type;
    balance = initialBalance;
}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

string BankAccount::getHolderName() const {
    return holderName;
}

string BankAccount::getAccountType() const {
    return accountType;
}

double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::deposit(double amount) {
    balance += amount;
}

bool BankAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    balance -= amount;
    return true;
}

void BankAccount::setHolderName(string name) {
    holderName = name;
}

void BankAccount::setAccountType(string type) {
    accountType = type;
}

void BankAccount::display() const {
    cout << left
         << setw(15) << accountNumber
         << setw(22) << holderName
         << setw(15) << accountType
         << "Rs. " << fixed << setprecision(2)
         << balance << endl;
}