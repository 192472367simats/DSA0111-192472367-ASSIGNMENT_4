#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

constexpr double DA_RATE = 0.42;

class Staff {
protected:
    string name;
    int id;
public:
    Staff(string n, int i) : name(n), id(i) {}
    virtual double pay() const = 0;
    virtual void display() const {
        cout << name << " (ID: " << id << ") - Salary: Rs. "
             << pay() << '\n';
    }
    virtual ~Staff() = default;
};

class Professor : public Staff {
    double basic, research;
public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i), basic(b), research(r) {}

    double pay() const override {
        return basic + basic * DA_RATE + research;
    }
};

class LabAssistant : public Staff {
    double basic;
public:
    LabAssistant(string n, int i, double b)
        : Staff(n, i), basic(b) {}

    double pay() const override {
        return basic + basic * DA_RATE;
    }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(n, i), hours(h), rate(r) {}

    double pay() const override {
        return hours * rate;
    }
};

int main() {
    vector<unique_ptr<Staff>> employees;

    employees.push_back(make_unique<Professor>(
        "Arun", 101, 50000, 5000));

    employees.push_back(make_unique<LabAssistant>(
        "Priya", 102, 30000));

    employees.push_back(make_unique<GuestFaculty>(
        "Kumar", 103, 40, 800));

    cout << "COLLEGE PAYROLL DETAILS\n";
    cout << "-----------------------\n";

    for (const auto& employee : employees) {
        employee->display();
    }

    return 0;
}