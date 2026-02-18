#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

sqlite3 *db;
char *errMsg = 0;

// Create table
void createTable() {
    string sql =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "accountNumber INTEGER PRIMARY KEY,"
        "name TEXT,"
        "password TEXT,"
        "balance REAL);";

    sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}

// Check if account exists
bool accountExists(int accNo) {
    string sql = "SELECT * FROM accounts WHERE accountNumber = " + to_string(accNo) + ";";
    bool found = false;

    auto callback = [](void *data, int argc, char **argv, char **azColName) {
        bool *flag = (bool*)data;
        *flag = true;
        return 0;
    };

    sqlite3_exec(db, sql.c_str(), callback, &found, NULL);
    return found;
}

// Get balance
double getBalance(int accNo) {
    string sql = "SELECT balance FROM accounts WHERE accountNumber = " + to_string(accNo) + ";";
    double balance = 0;

    auto callback = [](void *data, int argc, char **argv, char **azColName) {
        double *bal = (double*)data;
        if (argv[0])
            *bal = stod(argv[0]);
        return 0;
    };

    sqlite3_exec(db, sql.c_str(), callback, &balance, NULL);
    return balance;
}

// Check password
bool checkPassword(int accNo, string password) {
    string sql = "SELECT password FROM accounts WHERE accountNumber = " + to_string(accNo) + ";";
    bool correct = false;

    auto callback = [](void *data, int argc, char **argv, char **azColName) {
        pair<string,bool>* info = (pair<string,bool>*)data;
        if (argv[0] && info->first == argv[0])
            info->second = true;
        return 0;
    };

    pair<string,bool> data = {password, false};
    sqlite3_exec(db, sql.c_str(), callback, &data, NULL);

    return data.second;
}

void createAccount() {
    int accNo;
    string name, password;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNo;

    if (accountExists(accNo)) {
        cout << "Account already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> name;

    cout << "Set Password: ";
    cin >> password;

    cout << "Enter Initial Balance: ";
    cin >> balance;

    string sql = "INSERT INTO accounts VALUES (" +
                 to_string(accNo) + ", '" +
                 name + "', '" +
                 password + "', " +
                 to_string(balance) + ");";

    if (sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg) != SQLITE_OK) {
        cout << "Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Account Created Successfully!\n";
    }
}

void deposit() {
    int accNo;
    string password;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Password: ";
    cin >> password;

    if (!checkPassword(accNo, password)) {
        cout << "Wrong Password!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    string sql = "UPDATE accounts SET balance = balance + " +
                 to_string(amount) +
                 " WHERE accountNumber = " +
                 to_string(accNo) + ";";

    sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    cout << "Deposit Successful!\n";
}

void withdraw() {
    int accNo;
    string password;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Password: ";
    cin >> password;

    if (!checkPassword(accNo, password)) {
        cout << "Wrong Password!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    double balance = getBalance(accNo);

    if (amount > balance) {
        cout << "Insufficient Balance!\n";
        return;
    }

    string sql = "UPDATE accounts SET balance = balance - " +
                 to_string(amount) +
                 " WHERE accountNumber = " +
                 to_string(accNo) + ";";

    sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    cout << "Withdrawal Successful!\n";
}

void checkBalance() {
    int accNo;
    string password;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Password: ";
    cin >> password;

    if (!checkPassword(accNo, password)) {
        cout << "Wrong Password!\n";
        return;
    }

    double balance = getBalance(accNo);
    cout << "Current Balance: " << balance << endl;
}

void deleteAccount() {
    int accNo;
    string password;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Password: ";
    cin >> password;

    if (!checkPassword(accNo, password)) {
        cout << "Wrong Password!\n";
        return;
    }

    string sql = "DELETE FROM accounts WHERE accountNumber = " +
                 to_string(accNo) + ";";

    sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    cout << "Account Deleted Successfully!\n";
}

int main() {

    if (sqlite3_open("bank.db", &db)) {
        cout << "Cannot open database!\n";
        return 1;
    }

    createTable();

    int choice;

    do {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Delete Account\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: deleteAccount(); break;
            case 6: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    sqlite3_close(db);
    return 0;
}
