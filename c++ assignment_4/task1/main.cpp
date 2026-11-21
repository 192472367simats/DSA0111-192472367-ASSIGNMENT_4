#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Staff {
private:
    string name;
    int id;

public:
    Staff(const string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;

    string getName() const { return name; }
    int getId() const { return id; }

    virtual double pay() const = 0;
};

class Professor : public Staff {
private:
    double basic, research;
    static constexpr double DA_RATE = 0.42;

public:
    Professor(const string& n, int i, double b, double r)
        : Staff(n, i), basic(b), research(r) {}

    double pay() const override {
        return basic + basic * DA_RATE + research;
    }
};

class LabAssistant : public Staff {
private:
    double basic;
    static constexpr double DA_RATE = 0.42;

public:
    LabAssistant(const string& n, int i, double b)
        : Staff(n, i), basic(b) {}

    double pay() const override {
        return basic + basic * DA_RATE;
    }
};

class GuestFaculty : public Staff {
private:
    double hours, ratePerHour;

public:
    GuestFaculty(const string& n, int i, double h, double r)
        : Staff(n, i), hours(h), ratePerHour(r) {}

    double pay() const override {
        return hours * ratePerHour;
    }
};

int main() {
    vector<unique_ptr<Staff>> staff;

    staff.push_back(make_unique<Professor>("Anita", 101, 50000, 5000));
    staff.push_back(make_unique<LabAssistant>("Bala", 102, 30000));
    staff.push_back(make_unique<GuestFaculty>("Charan", 103, 40, 900));

    cout << fixed << setprecision(2);

    for (const auto& person : staff) {
        cout << person->getName() << " (" << person->getId()
             << ") : Rs. " << person->pay() << '\n';
    }

    return 0;
}