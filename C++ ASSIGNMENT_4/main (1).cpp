#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int id;
    string phone;

public:
    Person(string n, int i, string p)
        : name(n), id(i), phone(p) {
        cout << "Person created\n";
    }

    virtual ~Person() = default;
};

class Student : virtual public Person {
protected:
    string programme;
    double cgpa;

public:
    Student(string n, int i, string p, string prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {
        cout << "Student created\n";
    }
};

class Staff : virtual public Person {
protected:
    string department;
    double salary;

public:
    Staff(string n, int i, string p, string dept, double s)
        : Person(n, i, p), department(dept), salary(s) {
        cout << "Staff created\n";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int i, string p,
                      string prog, double c,
                      string dept, double s)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          Staff(n, i, p, dept, s) {
        cout << "Teaching Assistant created\n";
    }

    void display() const {
        cout << "\nTEACHING ASSISTANT DETAILS\n";
        cout << "Name: " << name << '\n';
        cout << "ID: " << id << '\n';
        cout << "Phone: " << phone << '\n';
        cout << "Programme: " << programme << '\n';
        cout << "CGPA: " << cgpa << '\n';
        cout << "Department: " << department << '\n';
        cout << "Salary: Rs. " << salary << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship;

public:
    ResearchScholar(string n, int i, string p,
                    string prog, double c, double f)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          fellowship(f) {
        cout << "Research Scholar created\n";
    }

    void display() const {
        cout << "\nRESEARCH SCHOLAR DETAILS\n";
        cout << "Name: " << name << '\n';
        cout << "ID: " << id << '\n';
        cout << "Programme: " << programme << '\n';
        cout << "CGPA: " << cgpa << '\n';
        cout << "Fellowship: Rs. " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant ta(
        "Kavya", 101, "9876543210",
        "CSE-AI", 8.7, "Computer Science", 25000
    );

    ta.display();

    ResearchScholar scholar(
        "Rahul", 102, "9876501234",
        "M.Tech", 9.1, 15000
    );

    scholar.display();

    return 0;
}