#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Vehicle {
protected:
    string registration;
    double dailyRate;
    bool rented;

public:
    Vehicle(string reg, double rate)
        : registration(reg), dailyRate(rate), rented(false) {}

    virtual double rentalCharge(int days, double usage) const = 0;

    virtual string type() const = 0;

    virtual void display() const {
        cout << type()
             << " | Registration: " << registration
             << " | Daily Rate: Rs. " << dailyRate
             << " | Status: " << (rented ? "Rented" : "Available")
             << '\n';
    }

    void rent() {
        if (!rented) {
            rented = true;
            cout << registration << " rented successfully.\n";
        } else {
            cout << registration << " is already rented.\n";
        }
    }

    void returnVehicle(int lateDays) {
        if (rented) {
            double lateFee = lateDays * dailyRate * 1.5;
            rented = false;

            cout << registration << " returned successfully.\n";
            cout << "Late Fee: Rs. " << lateFee << '\n';
        } else {
            cout << registration << " was not rented.\n";
        }
    }

    virtual ~Vehicle() = default;
};

class Bicycle : public Vehicle {
public:
    Bicycle(string reg, double rate)
        : Vehicle(reg, rate) {}

    string type() const override {
        return "Bicycle";
    }

    double rentalCharge(int days, double usage) const override {
        (void)usage;
        return dailyRate * days;
    }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelLevel;
    string serviceDueDate;

public:
    MotorVehicle(string reg, double rate,
                 double fuel, string date)
        : Vehicle(reg, rate),
          fuelLevel(fuel), serviceDueDate(date) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string reg, double rate,
               double fuel, string date)
        : MotorVehicle(reg, rate, fuel, date) {}

    string type() const override {
        return "TwoWheeler";
    }

    double rentalCharge(int days, double fuelUsed) const override {
        return dailyRate * days + fuelUsed * 100;
    }
};

class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(string reg, double rate, double fuel,
        string date, int seats)
        : MotorVehicle(reg, rate, fuel, date),
          seatingCapacity(seats) {}

    string type() const override {
        return "Car";
    }

    double rentalCharge(int days, double usage) const override {
        (void)usage;
        return dailyRate * days + seatingCapacity * 50 * days;
    }
};

class ElectricCar : public Car {
    double batteryCapacity;

public:
    ElectricCar(string reg, double rate, double battery,
                string date, int seats)
        : Car(reg, rate, 0, date, seats),
          batteryCapacity(battery) {}

    string type() const override {
        return "Electric Car";
    }

    double rentalCharge(int days, double energyUsed) const override {
        return dailyRate * days + energyUsed * 15;
    }
};

class ElectricBus : public MotorVehicle {
    double batteryCapacity;
    int seatingCapacity;

public:
    ElectricBus(string reg, double rate, double battery,
                string date, int seats)
        : MotorVehicle(reg, rate, 0, date),
          batteryCapacity(battery), seatingCapacity(seats) {}

    string type() const override {
        return "Electric Bus";
    }

    double rentalCharge(int days, double energyUsed) const override {
        return dailyRate * days + energyUsed * 12;
    }
};

int main() {
    cout << fixed << setprecision(2);

    Bicycle bicycle("BI-101", 200);
    TwoWheeler bike("TW-102", 500, 10, "20-12-2026");
    Car car("CA-103", 1500, 30, "25-12-2026", 5);
    ElectricCar ecar("EC-104", 2000, 60, "30-12-2026", 5);
    ElectricBus bus("EB-105", 3500, 150, "15-01-2027", 30);

    // Array of base-class pointers
    Vehicle* fleet[] = {
        &bicycle, &bike, &car, &ecar, &bus
    };

    int count = 5;

    cout << "VEHICLE RENTAL FLEET\n";
    cout << "--------------------\n";

    for (int i = 0; i < count; ++i) {
        fleet[i]->display();
    }

    cout << "\nRENTAL CHARGES\n";
    cout << "--------------\n";

    cout << "Bicycle: Rs. "
         << bicycle.rentalCharge(2, 0) << '\n';

    cout << "TwoWheeler: Rs. "
         << bike.rentalCharge(2, 3) << '\n';

    cout << "Car: Rs. "
         << car.rentalCharge(2, 0) << '\n';

    cout << "Electric Car: Rs. "
         << ecar.rentalCharge(2, 20) << '\n';

    cout << "Electric Bus: Rs. "
         << bus.rentalCharge(2, 50) << '\n';

    cout << "\nRENT AND RETURN DEMONSTRATION\n";
    bicycle.rent();
    bicycle.returnVehicle(2);

    cout << "\nUPDATED FLEET STATUS\n";
    for (int i = 0; i < count; ++i) {
        fleet[i]->display();
    }

    return 0;
}