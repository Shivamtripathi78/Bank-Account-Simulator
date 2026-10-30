#include <iostream>
#include <limits>
#include "BankManager.h"

using namespace std;

int main() {
    BankManager bank;
    int choice;

    do {
        cout << "\n=====================================\n";
        cout << "       BANK ACCOUNT SIMULATOR\n";
        cout << "=====================================\n";

        cout << "1. Create Bank Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Account Balance\n";
        cout << "6. Search Account\n";
        cout << "7. Transfer Money\n";
        cout << "8. Transaction History\n";
        cout << "9. Delete Account\n";
        cout << "0. Exit\n";

        cout << "=====================================\n";
        cout << "Enter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                bank.createAccount();
                break;

            case 2:
                bank.displayAccounts();
                break;

            case 3:
                bank.depositMoney();
                break;

            case 4:
                bank.withdrawMoney();
                break;

            case 5:
                bank.checkBalance();
                break;

            case 6:
                bank.searchAccount();
                break;

            case 7:
                bank.transferMoney();
                break;

            case 8:
                bank.showTransactionHistory();
                break;

            case 9:
                bank.deleteAccount();
                break;

            case 0:
                cout << "\nThank you for using Bank Account Simulator!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}