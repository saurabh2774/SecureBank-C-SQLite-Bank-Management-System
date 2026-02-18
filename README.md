# SecureBank-C-SQLite-Bank-Management-System
Developed a console based banking system in C++ integrated with SQLite for persistent storage. Implemented account authentication, deposit/withdrawal operations with overdraft protection, balance inquiry, and account deletion using SQL based data management.
🏦 SecureBank – C++ SQLite Bank Management System
📌 Project Overview

SecureBank is a console-based Bank Management System developed using C++ and SQLite.
The application allows users to create bank accounts, perform deposits and withdrawals, check balances, and securely delete accounts.

The system integrates SQLite as an embedded database to provide persistent storage and real-time SQL-based data handling.

🚀 Features

Create new bank accounts

Password-protected authentication

Deposit money

Withdraw money with overdraft protection

Check account balance

Delete account

Persistent database storage using SQLite

🛠 Technologies Used

C++

SQLite (Embedded Database)

SQL Queries

File Compilation using GCC & G++

Menu-driven Console Application

🧠 Concepts Demonstrated

Object-Oriented Programming Concepts

Database Integration in C++

SQL CRUD Operations

Data Validation

Authentication Logic

Callback Functions in SQLite

Modular Function Design

📂 Project Structure
SecureBank/
│
├── main.cpp
├── sqlite3.c
├── sqlite3.h
├── sqlite3.o
└── bank.db (auto-generated)

▶ How to Run
Step 1 – Compile SQLite
gcc -c sqlite3.c

Step 2 – Compile Program
g++ main.cpp sqlite3.o -o bank

Step 3 – Run
bank

🔒 Security Features

Password authentication before transactions

Overdraft prevention

Duplicate account prevention

Structured SQL operations

🎯 Future Improvements

Password hashing

Prepared statements (SQL injection prevention)

Transaction logging system

GUI version

Migration to MySQL backend

👨‍💻 Author

Developed as a database-integrated C++ mini-project demonstrating backend logic and SQL integration.
