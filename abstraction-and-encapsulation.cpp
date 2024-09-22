#include <iostream>
using namespace std;

class Account {
protected:
    double balance;

public:
    Account(double initial_balance = 0) : balance(initial_balance) {}

    virtual void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount! Please enter a valid number." << endl;
        } else {
            balance += amount;
            cout << "Deposited: " << amount << ". New Balance: " << balance << endl;
        }
    }

    virtual void withdraw(double amount) = 0;  // Pure virtual function for withdrawal

    void checkBalance() const {
        cout << "Current Balance: " << balance << endl;
    }
};

class SavingsAccount : public Account {
private:
    const double MIN_BALANCE = 1000;

public:
    SavingsAccount(double initial_balance = 1000) : Account(initial_balance) {
        if (initial_balance < MIN_BALANCE) {
            balance = MIN_BALANCE;
        }
    }

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid amount! Please enter a valid number." << endl;
        } else if (balance - amount < MIN_BALANCE) {
            cout << "Withdrawal denied! Minimum balance of " << MIN_BALANCE << " required." << endl;
        } else {
            balance -= amount;
            cout << "Withdrew: " << amount << ". New Balance: " << balance << endl;
        }
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(double initial_balance = 0) : Account(initial_balance) {}

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid amount! Please enter a valid number." << endl;
        } else if (amount > balance) {
            cout << "Withdrawal denied! Insufficient balance." << endl;
        } else {
            balance -= amount;
            cout << "Withdrew: " << amount << ". New Balance: " << balance << endl;
        }
    }
};

void displayMainMenu() {
    cout << "\nMain Menu\n";
    cout << "1 - Savings Account\n";
    cout << "2 - Current Account\n";
    cout << "3 - Exit\n";
    cout << "Enter your Choice: ";
}

void displaySubMenu() {
    cout << "\nSub Menu\n";
    cout << "1 - Deposit\n";
    cout << "2 - Withdraw\n";
    cout << "3 - Check Balance\n";
    cout << "4 - Back to Main Menu\n";
    cout << "Enter your Choice: ";
}

int getValidInput() {
    int choice;
    cin >> choice;
    while (choice <= 0) {
        cout << "Invalid input! Please enter a valid number: ";
        cin >> choice;
    }
    return choice;
}

void handleAccountOperations(Account* account) {
    int subChoice;
    do {
        displaySubMenu();
        subChoice = getValidInput(); //Display Sub Menu for Savings and Current Account

        switch (subChoice) {
            case 1: {
                double depositAmount;
                cout << "Enter amount to deposit: ";
                cin >> depositAmount;
                account->deposit(depositAmount);
                break;
            }
            case 2: {
                double withdrawAmount;
                cout << "Enter amount to withdraw: ";
                cin >> withdrawAmount;
                account->withdraw(withdrawAmount);
                break;
            }
            case 3:
                account->checkBalance();
                break;
            case 4:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (subChoice != 4);
}

int main() { 
    SavingsAccount savings;
    CurrentAccount current;

    int choice;
    do {
        displayMainMenu();//Display Main Menu
        choice = getValidInput();

        switch (choice) {
            case 1:
                handleAccountOperations(&savings);
                break;
            case 2:
                handleAccountOperations(&current);
                break;
            case 3:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
