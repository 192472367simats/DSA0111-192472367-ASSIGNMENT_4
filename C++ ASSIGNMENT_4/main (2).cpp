#include <iostream>
#include <string>
using namespace std;

class Address {
    string city;
    int pin;

public:
    Address(string c, int p) : city(c), pin(p) {
        cout << "Address constructor\n";
    }

    ~Address() {
        cout << "Address destructor\n";
    }

    string getAddress() const {
        return city + "-" + to_string(pin);
    }
};

class Course {
    string courseName;

public:
    Course(string c) : courseName(c) {
        cout << "Course constructor\n";
    }

    ~Course() {
        cout << "Course destructor\n";
    }

    string getCourse() const {
        return courseName;
    }
};

class Person {
protected:
    string name;
    int age;
    Address address;

public:
    Person(string n, int a, string city, int pin)
        : name(n), age(a), address(city, pin) {
        cout << "Person constructor\n";
    }

    virtual ~Person() {
        cout << "Person destructor\n";
    }
};

class Student : virtual public Person {
protected:
    long long regNo;
    Course course;

public:
    Student(string n, int a, long long r,
            string city, int pin, string c)
        : Person(n, a, city, pin),
          regNo(r), course(c) {
        cout << "Student constructor\n";
    }

    ~Student() override {
        cout << "Student destructor\n";
    }

    void display() const {
        cout << "\nSTUDENT DETAILS\n";
        cout << "Name: " << name << '\n';
        cout << "Age: " << age << '\n';
        cout << "Register Number: " << regNo << '\n';
        cout << "Address: " << address.getAddress() << '\n';
        cout << "Course: " << course.getCourse() << '\n';
    }
};

class Staff : virtual public Person {
protected:
    string department;

public:
    Staff(string n, int a, string city, int pin, string d)
        : Person(n, a, city, pin), department(d) {
        cout << "Staff constructor\n";
    }

    ~Staff() override {
        cout << "Staff destructor\n";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int a, long long r,
                      string city, int pin, string c, string d)
        : Person(n, a, city, pin),
          Student(n, a, r, city, pin, c),
          Staff(n, a, city, pin, d) {
        cout << "TeachingAssistant constructor\n";
    }

    ~TeachingAssistant() override {
        cout << "TeachingAssistant destructor\n";
    }
};

int main() {
    cout << "CREATING STUDENT\n";
    {
        Student s("Kavya", 19, 192311001,
                  "Salem", 636001, "C++ Programming");
        s.display();
    }

    cout << "\nCREATING STAFF\n";
    {
        Staff st("Arun", 35, "Chennai", 600001,
                 "Computer Science");
    }

    cout << "\nCREATING TEACHING ASSISTANT\n";
    {
        TeachingAssistant ta(
            "Priya", 22, 192311002,
            "Chennai", 600002, "Artificial Intelligence",
            "Computer Science"
        );
    }

    return 0;
}