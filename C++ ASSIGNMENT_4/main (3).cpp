#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
using namespace std;

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }

    virtual void display() const {
        cout << "General Account Interest Rate: "
             << rate() << "%\n";
    }

    virtual ~Account() {
        cout << "Account destructor\n";
    }
};

class SeniorAccount : public Account {
    double* history;

public:
    SeniorAccount() : history(new double[100]{}) {}

    double rate() const override {
        return 4.0;
    }

    void display() const override {
        cout << "Senior Account Interest Rate: "
             << rate() << "%\n";
    }

    ~SeniorAccount() override {
        delete[] history;
        cout << "SeniorAccount destructor\n";
    }
};

int main() {
    vector<unique_ptr<Account>> accounts;

    accounts.push_back(make_unique<Account>());
    accounts.push_back(make_unique<SeniorAccount>());

    cout << fixed << setprecision(1);
    cout << "BANK ACCOUNT DETAILS\n";
    cout << "--------------------\n";

    for (const auto& account : accounts) {
        account->display();
    }

    cout << "\nPOLYMORPHIC FUNCTION CALLS\n";

    SeniorAccount senior;
    Account* ptr = &senior;

    cout << "Non-virtual function result: "
         << ptr->rate() << "%\n";

    cout << "Virtual function result: "
         << ptr->rate() << "%\n";

    cout << "\nAccounts are automatically destroyed "
         << "using unique_ptr.\n";

    return 0;
}