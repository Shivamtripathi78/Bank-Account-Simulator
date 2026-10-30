# Bank Account Simulator

A console-based banking application developed using C++. It simulates basic banking operations, allowing users to create accounts, manage balances, transfer money, and track transaction history.

## Features

* Create and manage bank accounts.
* Deposit and withdraw money.
* Check account balances.
* Search accounts by account number.
* Transfer money between accounts.
* View transaction history.
* Delete accounts with zero balance.
* Store account data using file handling.

## Technologies Used

* **Language:** C++
* **Concepts:** OOP, Classes, Encapsulation, Vectors, File Handling, CRUD Operations.
* **Compiler:** GCC (G++)

## Project Structure

```text
Bank-Account-Simulator/
│
├── main.cpp
├── BankAccount.h
├── BankAccount.cpp
├── BankManager.h
├── BankManager.cpp
├── accounts.txt
├── transactions.txt
└── README.md
```

## How to Run

**1. Clone the repository**

```bash
git clone https://github.com/Shivamtripathi78/Bank-Account-Simulator.git
```

**2. Navigate to the project directory**

```bash
cd Bank-Account-Simulator
```

**3. Compile the project**

```bash
g++ -std=c++17 main.cpp BankAccount.cpp BankManager.cpp -o BankSimulator.exe
```

**4. Run the application**

```powershell
.\BankSimulator.exe
```

## Learning Outcomes

* Understanding OOP principles in C++.
* Implementing banking operations using classes and objects.
* Managing account records using vectors.
* Working with file handling for data persistence.
* Implementing transaction management and validation.

## Disclaimer

This project is developed for educational purposes and is not intended for real banking or financial transactions.

## Author

**Shivam Tripathi**

GitHub: [Shivamtripathi78](https://github.com/Shivamtripathi78)
