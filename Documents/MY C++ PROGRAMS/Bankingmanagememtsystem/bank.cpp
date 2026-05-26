#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class Account {
private:
    int accNo;
    int pin;
    string name;
    double balance;
    vector<string> transactionHistory;
public:
    // Create Account
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Set 4-Digit PIN: ";
        cin >> pin;
        cout << "Enter Initial Balance: ";
        cin >> balance;
        transactionHistory.push_back(
            "Account Created with Balance: " + to_string(balance)
        );
        cout << "Account Created Successfully!\n";
    }
    // PIN Verification
    bool verifyPin() {
        int enteredPin;
        cout << "Enter PIN: ";
        cin >> enteredPin;
        if(enteredPin == pin) {
            return true;
        }
        cout << "Incorrect PIN!\n";
        return false;
    }
    // Display Account
    void displayAccount() const {
        cout << "\n----- ACCOUNT DETAILS -----\n";
        cout << "Account Number : " << accNo << endl;
        cout << "Name           : " << name << endl;
        cout << "Balance        : " << balance << endl;
    }
    // Deposit Money
    void depositMoney() {
        if(!verifyPin()) {
            return;
        }
        double amount;
        cout << "Enter Amount to Deposit: ";
        cin >> amount;
        balance += amount;
        transactionHistory.push_back(
            "Deposited: " + to_string(amount)
        );
        cout << "Amount Deposited Successfully!\n";
    }
    // Withdraw Money
    void withdrawMoney() {
        if(!verifyPin()) {
            return;
        }
        double amount;
        cout << "Enter Amount to Withdraw: ";
        cin >> amount;
        if(amount > balance) {
            cout << "Insufficient Balance!\n";
            transactionHistory.push_back(
                "Failed Withdrawal Attempt: " + to_string(amount)
            );
        }
        else {
            balance -= amount;
            transactionHistory.push_back(
                "Withdrawn: " + to_string(amount)
            );
            cout << "Withdrawal Successful!\n";
        }
    }
    // Show Transaction History
    void showTransactionHistory() {
        if(!verifyPin()) {
            return;
        }
        cout << "\n----- TRANSACTION HISTORY -----\n";
        if(transactionHistory.empty()) {
            cout << "No Transactions Found!\n";
        }
        else {
            for(int i = 0; i < transactionHistory.size(); i++) {
                cout << i + 1 << ". "
                     << transactionHistory[i] << endl;
            }
        }
    }
    // Get Account Number
    int getAccountNumber() const {
        return accNo;
    }
    // Save Data to File
    void saveToFile(ofstream &out) {
        out << accNo << endl;
        out << name << endl;
        out << pin << endl;
        out << balance << endl;
        out << transactionHistory.size() << endl;
        for(int i = 0; i < transactionHistory.size(); i++) {
            out << transactionHistory[i] << endl;
        }
    }
    // Load Data from File
    void loadFromFile(ifstream &in) {
        in >> accNo;
        in.ignore();
        getline(in, name);
        in >> pin;
        in >> balance;
        int count;
        in >> count;
        in.ignore();
        transactionHistory.clear();
        for(int i = 0; i < count; i++) {
            string transaction;
            getline(in, transaction);
            transactionHistory.push_back(transaction);
        }
    }
};
// Save All Accounts
void saveAccounts(vector<Account> &accounts) {
    ofstream out("bank.txt");
    for(int i = 0; i < accounts.size(); i++) {
        accounts[i].saveToFile(out);
    }
    out.close();
}
// Load All Accounts
void loadAccounts(vector<Account> &accounts) {
    ifstream in("bank.txt");
    while(in >> ws && !in.eof()) {
        Account a;
        a.loadFromFile(in);
        accounts.push_back(a);
    }
    in.close();
}
int main() {
    vector<Account> accounts;
    loadAccounts(accounts);
    int choice;
    while(true) {
        cout << "\n========== BANKING MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Search Account\n";
        cout << "6. Delete Account\n";
        cout << "7. Transaction History\n";
        cout << "8. Exit\n";
        cout << "\nEnter Your Choice: ";
        cin >> choice;
        switch(choice) {
            // Create Account
            case 1: {
                Account a;
                a.createAccount();
                accounts.push_back(a);
                saveAccounts(accounts);
                break;
            }
            // Display All Accounts
            case 2: {
                if(accounts.empty()) {
                    cout << "\nNo Accounts Found!\n";
                }
                else {
                    for(int i = 0; i < accounts.size(); i++) {
                        accounts[i].displayAccount();
                    }
                }
                break;
            }
            // Deposit Money
            case 3: {
                int acc;
                cout << "\nEnter Account Number: ";
                cin >> acc;
                bool found = false;
                for(int i = 0; i < accounts.size(); i++) {
                    if(accounts[i].getAccountNumber() == acc) {
                        accounts[i].depositMoney();
                        saveAccounts(accounts);
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            // Withdraw Money
            case 4: {
                int acc;
                cout << "\nEnter Account Number: ";
                cin >> acc;
                bool found = false;
                for(int i = 0; i < accounts.size(); i++) {
                    if(accounts[i].getAccountNumber() == acc) {
                        accounts[i].withdrawMoney();
                        saveAccounts(accounts);
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            // Search Account
            case 5: {
                int acc;
                cout << "\nEnter Account Number: ";
                cin >> acc;
                bool found = false;
                for(int i = 0; i < accounts.size(); i++) {
                    if(accounts[i].getAccountNumber() == acc) {
                        accounts[i].displayAccount();
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            // Delete Account
            case 6: {
                int acc;
                cout << "\nEnter Account Number to Delete: ";
                cin >> acc;
                bool found = false;
                for(int i = 0; i < accounts.size(); i++) {
                    if(accounts[i].getAccountNumber() == acc) {
                        accounts.erase(accounts.begin() + i);
                        saveAccounts(accounts);
                        cout << "Account Deleted Successfully!\n";
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            // Transaction History
            case 7: {
                int acc;
                cout << "\nEnter Account Number: ";
                cin >> acc;
                bool found = false;
                for(int i = 0; i < accounts.size(); i++) {
                    if(accounts[i].getAccountNumber() == acc) {
                        accounts[i].showTransactionHistory();
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            // Exit
            case 8: {
                cout << "\nThank You for Using Banking System!\n";
                return 0;
            }
            default:
                cout << "\nInvalid Choice!\n";
        }
    }
    return 0;
}