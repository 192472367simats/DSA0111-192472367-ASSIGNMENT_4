#include <iostream>
using namespace std;

class CartValue {
    double amount;

public:
    explicit CartValue(double a) : amount(a) {}

    double total() const {
        return amount;
    }
};

int main() {
    CartValue c1(250), c2(780), c3(420);

    CartValue* carts[] = {&c1, &c2, &c3};

    int n = 3;
    int best = 0;

    for (int i = 1; i < n; ++i) {
        if (carts[i]->total() > carts[best]->total()) {
            best = i;
        }
    }

    cout << "Highest cart total: "
         << carts[best]->total() << '\n';

    return 0;
}