#include <iostream>
#include <string>
using namespace std;

class Cart {
    string customer;
    double amount;

public:
    Cart(const string& customer, double amount)
        : customer(customer), amount(amount) {}

    Cart& setAmount(double amount) {
        this->amount = amount;
        return *this;
    }

    double total() const {
        return amount;
    }
};

int main() {
    // 1. Direct object
    Cart direct("Asha", 250);
    cout << direct.total() << '\n';

    // 2. Pointer to existing object
    Cart* ptr = &direct;
    cout << ptr->total() << '\n';

    // 3. Reference
    Cart& ref = direct;
    cout << ref.total() << '\n';

    // 4. Dynamic object
    Cart* dynamicCart = new Cart("Ravi", 500);
    cout << dynamicCart->total() << '\n';

    delete dynamicCart;

    return 0;
}