#ifndef BANKMANAGER_H
#define BANKMANAGER_H

#include "BankAccount.h"
#include <vector>
#include <string>

class BankManager {
private:
    vector<BankAccount> accounts;

    void loadAccounts();
    void saveAccounts() const;
    void recordTransaction(int accountNumber,
                           const string& type,
                           double amount,
                           const string& details);

    int findAccountIndex(int accountNumber) const;

public:
    BankManager();

    void createAccount();
    void displayAccounts() const;
    void depositMoney();
    void withdrawMoney();
    void checkBalance() const;
    void searchAccount() const;
    void transferMoney();
    void showTransactionHistory() const;
    void deleteAccount();
};

#endif