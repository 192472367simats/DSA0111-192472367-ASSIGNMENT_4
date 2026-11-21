#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int id;
    string phone;

public:
    Person(const string& n, int i, const string& p)
        : name(n), id(i), phone(p) {
        cout << "Person ";
    }
};

class Student : public virtual Person {
protected:
    string programme;
    double cgpa;

public:
    Student(const string& n, int i, const string& p,
            const string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {
        cout << "Student ";
    }
};

class Staff : public virtual Person {
protected:
    string department;
    double salary;

public:
    Staff(const string& n, int i, const string& p,
          const string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {
        cout << "Staff ";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const string& n, int i, const string& p,
                      const string& prog, double c,
                      const string& dept, double s)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          Staff(n, i, p, dept, s) {
        cout << "TA ";
    }

    void display() const {
        cout << "\nName: " << name
             << "\nID: " << id
             << "\nPhone: " << phone
             << "\nProgramme: " << programme
             << "\nCGPA: " << cgpa
             << "\nDepartment: " << department
             << "\nSalary: " << salary << '\n';
    }
};

class ResearchScholar : public Student {
private:
    double fellowship;

public:
    ResearchScholar(const string& n, int i, const string& p,
                    const string& prog, double c, double f)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          fellowship(f) {}

    void display() const {
        cout << "\nResearch Scholar: " << name
             << "\nFellowship: " << fellowship << '\n';
    }
};

int main() {
    cout << "Construction order: ";

    TeachingAssistant ta(
        "Kavya", 101, "9876543210",
        "CSE", 8.5, "Computer Science", 30000
    );

    ta.display();

    ResearchScholar rs(
        "Arun", 102, "9876501234",
        "AI", 9.0, 15000
    );

    rs.display();

    return 0;
}