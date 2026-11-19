#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Cart {
    string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;

public:
    Cart& add(const string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double t = 0;

        for (int i = 0; i < n; ++i) {
            t += prices[i];
        }

        return t * (100 - discount) / 100;
    }

    void display() const {
        for (int i = 0; i < n; ++i) {
            cout << items[i] << " - Rs. "
                 << prices[i] << '\n';
        }
        cout << "Total: Rs. " << total() << '\n';
    }
};

int main() {
    cout << fixed << setprecision(2);

    // 1. Direct object access
    Cart cart1;
    cart1.add("Rice", 60).add("Dal", 120);
    cart1.setDiscount(10);

    cout << "1. DIRECT OBJECT ACCESS\n";
    cart1.display();

    // 2. Pointer access using ->
    Cart* ptr = &cart1;
    ptr->add("Oil", 180);

    cout << "\n2. POINTER ACCESS\n";
    cout << "Total: Rs. " << ptr->total() << '\n';

    // 3. Reference access
    Cart& ref = cart1;
    ref.add("Sugar", 50);

    cout << "\n3. REFERENCE ACCESS\n";
    cout << "Total: Rs. " << ref.total() << '\n';

    // 4. Dynamic object using new and delete
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Milk", 40).add("Bread", 35);

    cout << "\n4. DYNAMIC OBJECT ACCESS\n";
    cout << "Total: Rs. " << dynamicCart->total() << '\n';

    delete dynamicCart;

    // Array of pointers to Cart objects
    Cart cart2, cart3;

    cart2.add("Book", 200).add("Pen", 50);
    cart3.add("Bag", 700).add("Bottle", 150);

    Cart* carts[3] = {&cart1, &cart2, &cart3};

    int highestIndex = 0;

    for (int i = 1; i < 3; ++i) {
        if (carts[i]->total() > carts[highestIndex]->total()) {
            highestIndex = i;
        }
    }

    cout << "\nHIGHEST CART TOTAL\n";
    cout << "Cart number: " << highestIndex + 1 << '\n';
    cout << "Highest total: Rs. "
         << carts[highestIndex]->total() << '\n';

    return 0;
}