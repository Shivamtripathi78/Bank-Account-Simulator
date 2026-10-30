#include "BankManager.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <ctime>

using namespace std;

BankManager::BankManager() {
    loadAccounts();
}

int BankManager::findAccountIndex(int accountNumber) const {
    for (int i = 0; i < static_cast<int>(accounts.size()); i++) {
        if (accounts[i].getAccountNumber() == accountNumber) {
            return i;
        }
    }

    return -1;
}

void BankManager::loadAccounts() {
    ifstream file("accounts.txt");

    string line;

    while (getline(file, line)) {
        try {
            stringstream ss(line);

            string number, name, type, balance;

            getline(ss, number, '|');
            getline(ss, name, '|');
            getline(ss, type, '|');
            getline(ss, balance);

            int accountNumber = stoi(number);
            double amount = stod(balance);

            if (accountNumber > 0 && amount >= 0 &&
                findAccountIndex(accountNumber) == -1) {
                accounts.emplace_back(
                    accountNumber, name, type, amount
                );
            }
        }
        catch (...) {
            continue;
        }
    }

    file.close();
}

void BankManager::saveAccounts() const {
    ofstream file("accounts.txt");

    for (const BankAccount& account : accounts) {
        file << account.getAccountNumber() << "|"
             << account.getHolderName() << "|"
             << account.getAccountType() << "|"
             << fixed << setprecision(2)
             << account.getBalance() << "\n";
    }

    file.close();
}

void BankManager::recordTransaction(
    int accountNumber,
    const string& type,
    double amount,
    const string& details
) {
    ofstream file("transactions.txt", ios::app);

    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    if (!file || localTime == nullptr) {
        cout << "Warning: Could not save transaction history.\n";
        return;
    }

    file << put_time(localTime, "%Y-%m-%d %H:%M:%S")
         << "|" << accountNumber
         << "|" << type
         << "|" << fixed << setprecision(2) << amount
         << "|" << details << "\n";

    file.close();
}

void BankManager::createAccount() {
    int number;
    string name, type;
    double initialBalance;

    cout << "\nEnter Account Number: ";

    if (!(cin >> number) || number <= 0) {
        cout << "Invalid account number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (findAccountIndex(number) != -1) {
        cout << "Account number already exists!\n";
        return;
    }

    cout << "Enter Account Holder Name: ";
    getline(cin >> ws, name);

    cout << "Enter Account Type (Savings/Current): ";
    getline(cin, type);

    cout << "Enter Initial Deposit: ";

    if (!(cin >> initialBalance) || initialBalance < 0) {
        cout << "Invalid initial deposit.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    accounts.emplace_back(number, name, type, initialBalance);

    saveAccounts();

    if (initialBalance > 0) {
        recordTransaction(number, "Initial Deposit",
                          initialBalance, "Account created");
    }

    cout << "\nBank account created successfully!\n";
}

void BankManager::displayAccounts() const {
    if (accounts.empty()) {
        cout << "\nNo bank accounts available.\n";
        return;
    }

    cout << "\n"
         << left
         << setw(15) << "Account No."
         << setw(22) << "Holder Name"
         << setw(15) << "Account Type"
         << "Balance\n";

    cout << string(70, '-') << "\n";

    for (const BankAccount& account : accounts) {
        account.display();
    }
}

void BankManager::depositMoney() {
    int number;
    double amount;

    cout << "\nEnter Account Number: ";
    if (!(cin >> number)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccountIndex(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter Deposit Amount: ";

    if (!(cin >> amount) || amount <= 0) {
        cout << "Invalid deposit amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    accounts[index].deposit(amount);

    saveAccounts();
    recordTransaction(number, "Deposit", amount, "Cash deposit");

    cout << "\nDeposit successful!\n";
    cout << "Updated Balance: Rs. "
         << accounts[index].getBalance() << "\n";
}

void BankManager::withdrawMoney() {
    int number;
    double amount;

    cout << "\nEnter Account Number: ";

    if (!(cin >> number)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccountIndex(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter Withdrawal Amount: ";

    if (!(cin >> amount) || amount <= 0) {
        cout << "Invalid withdrawal amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (!accounts[index].withdraw(amount)) {
        cout << "Insufficient balance!\n";
        return;
    }

    saveAccounts();
    recordTransaction(number, "Withdrawal", amount, "Cash withdrawal");

    cout << "\nWithdrawal successful!\n";
    cout << "Remaining Balance: Rs. "
         << accounts[index].getBalance() << "\n";
}

void BankManager::checkBalance() const {
    int number;

    cout << "\nEnter Account Number: ";

    if (!(cin >> number)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccountIndex(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "\nAccount Holder: "
         << accounts[index].getHolderName();

    cout << "\nAccount Balance: Rs. "
         << fixed << setprecision(2)
         << accounts[index].getBalance() << "\n";
}

void BankManager::searchAccount() const {
    int number;

    cout << "\nEnter Account Number to Search: ";

    if (!(cin >> number)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccountIndex(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "\nAccount Found:\n";

    cout << left
         << setw(15) << "Account No."
         << setw(22) << "Holder Name"
         << setw(15) << "Account Type"
         << "Balance\n";

    accounts[index].display();
}

void BankManager::transferMoney() {
    int from, to;
    double amount;

    cout << "\nEnter Sender Account Number: ";

    if (!(cin >> from)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter Receiver Account Number: ";

    if (!(cin >> to)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (from == to) {
        cout << "Sender and receiver accounts must be different.\n";
        return;
    }

    int sender = findAccountIndex(from);
    int receiver = findAccountIndex(to);

    if (sender == -1 || receiver == -1) {
        cout << "One or both accounts were not found.\n";
        return;
    }

    cout << "Enter Transfer Amount: ";

    if (!(cin >> amount) || amount <= 0) {
        cout << "Invalid transfer amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (!accounts[sender].withdraw(amount)) {
        cout << "Insufficient balance!\n";
        return;
    }

    accounts[receiver].deposit(amount);

    saveAccounts();

    recordTransaction(from, "Transfer Out", amount,
                      "Transferred to " + to_string(to));

    recordTransaction(to, "Transfer In", amount,
                      "Received from " + to_string(from));

    cout << "\nTransfer completed successfully!\n";
}

void BankManager::showTransactionHistory() const {
    int number;

    cout << "\nEnter Account Number: ";

    if (!(cin >> number)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (findAccountIndex(number) == -1) {
        cout << "Account not found!\n";
        return;
    }

    ifstream file("transactions.txt");

    if (!file) {
        cout << "No transaction history available.\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\nTransaction History:\n";

    while (getline(file, line)) {
        stringstream ss(line);

        string date, account, type, amount, details;

        getline(ss, date, '|');
        getline(ss, account, '|');
        getline(ss, type, '|');
        getline(ss, amount, '|');
        getline(ss, details);

        try {
            if (stoi(account) == number) {
                cout << date << " | "
                     << type << " | Rs. "
                     << amount << " | "
                     << details << "\n";

                found = true;
            }
        }
        catch (...) {
            continue;
        }
    }

    if (!found) {
        cout << "No transactions found for this account.\n";
    }

    file.close();
}

void BankManager::deleteAccount() {
    int number;

    cout << "\nEnter Account Number to Delete: ";

    if (!(cin >> number)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findAccountIndex(number);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    if (accounts[index].getBalance() != 0) {
        cout << "Account cannot be deleted while balance is non-zero.\n";
        return;
    }

    accounts.erase(accounts.begin() + index);

    saveAccounts();

    cout << "\nAccount deleted successfully!\n";
}