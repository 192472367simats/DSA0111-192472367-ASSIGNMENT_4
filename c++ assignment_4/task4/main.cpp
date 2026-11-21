#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }

    virtual ~Account() = default;
};

class SeniorAccount : public Account {
    vector<double> history = vector<double>(100);

public:
    double rate() const override {
        return 4.0;
    }

    ~SeniorAccount() override = default;
};

int main() {
    vector<unique_ptr<Account>> accounts;

    accounts.push_back(make_unique<Account>());
    accounts.push_back(make_unique<SeniorAccount>());

    for (const auto& a : accounts) {
        cout << a->rate() << '\n';
    }

    return 0;
}