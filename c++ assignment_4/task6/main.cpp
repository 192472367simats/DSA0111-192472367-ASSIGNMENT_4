#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Vehicle {
protected:
    string registrationNo;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(const string& reg, double rate)
        : registrationNo(reg), dailyRate(rate) {}

    virtual ~Vehicle() = default;

    virtual double charge(int days) const = 0;

    bool rent() {
        if (rented)
            return false;

        rented = true;
        return true;
    }

    double returnVehicle(int lateDays) {
        if (!rented)
            return 0.0;

        rented = false;
        const double lateFeePerDay = 200.0;

        return max(0, lateDays) * lateFeePerDay;
    }

    virtual void display() const {
        cout << registrationNo << " | Rs." << dailyRate
             << " per day | "
             << (rented ? "Rented" : "Available");
    }

    string regNo() const {
        return registrationNo;
    }
};

class Bicycle : public Vehicle {
public:
    using Vehicle::Vehicle;

    double charge(int days) const override {
        return dailyRate * days;
    }

    void display() const override {
        cout << "Bicycle | ";
        Vehicle::display();
        cout << '\n';
    }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    string serviceDueDate;

public:
    MotorVehicle(const string& reg, double rate,
                 double level, const string& due)
        : Vehicle(reg, rate),
          fuelOrChargeLevel(level),
          serviceDueDate(due) {}
};

class TwoWheeler : public MotorVehicle {
public:
    using MotorVehicle::MotorVehicle;

    double charge(int days) const override {
        return dailyRate * days;
    }

    void display() const override {
        cout << "TwoWheeler | ";
        Vehicle::display();

        cout << " | Level: " << fuelOrChargeLevel
             << " | Service: " << serviceDueDate << '\n';
    }
};

class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(const string& reg, double rate, double level,
        const string& due, int seats)
        : MotorVehicle(reg, rate, level, due),
          seatingCapacity(seats) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    void display() const override {
        cout << "Car | ";
        Vehicle::display();

        cout << " | Seats: " << seatingCapacity
             << " | Level: " << fuelOrChargeLevel << '\n';
    }
};

class ElectricCar : public Car {
protected:
    double batteryCapacityKWh;
    double energyRatePerKWh;

public:
    ElectricCar(const string& reg, double rate,
                double level, const string& due,
                int seats, double battery,
                double energyRate)
        : Car(reg, rate, level, due, seats),
          batteryCapacityKWh(battery),
          energyRatePerKWh(energyRate) {}

    double charge(int days) const override {
        return dailyRate * days
             + batteryCapacityKWh * energyRatePerKWh * 0.05;
    }

    void display() const override {
        cout << "ElectricCar | ";
        Vehicle::display();

        cout << " | Battery: " << batteryCapacityKWh
             << " kWh | Seats: " << seatingCapacity << '\n';
    }
};

// New vehicle type
class ElectricBus : public Vehicle {
    double batteryCapacityKWh;
    double energyRatePerKWh;

public:
    ElectricBus(const string& reg, double rate,
                double battery, double energyRate)
        : Vehicle(reg, rate),
          batteryCapacityKWh(battery),
          energyRatePerKWh(energyRate) {}

    double charge(int days) const override {
        return dailyRate * days
             + batteryCapacityKWh * energyRatePerKWh * 0.10;
    }

    void display() const override {
        cout << "ElectricBus | ";
        Vehicle::display();

        cout << " | Battery: " << batteryCapacityKWh
             << " kWh\n";
    }
};

int main() {
    vector<unique_ptr<Vehicle>> fleet;

    fleet.push_back(make_unique<Bicycle>("BI-101", 100));

    fleet.push_back(make_unique<TwoWheeler>(
        "TW-202", 500, 70, "2026-12-15"
    ));

    fleet.push_back(make_unique<Car>(
        "CA-303", 1500, 60, "2026-12-20", 5
    ));

    fleet.push_back(make_unique<ElectricCar>(
        "EV-404", 2200, 90, "2026-12-25", 5, 60, 8
    ));

    fleet.push_back(make_unique<ElectricBus>(
        "EB-505", 5000, 180, 8
    ));

    cout << fixed << setprecision(2);

    for (const auto& v : fleet) {
        v->display();

        cout << "Two-day charge: Rs. "
             << v->charge(2) << '\n';
    }

    cout << "\nRenting " << fleet[0]->regNo() << ": "
         << (fleet[0]->rent()
             ? "successful" : "already rented") << '\n';

    double lateFee = fleet[0]->returnVehicle(2);

    cout << "Returned; late fee: Rs. "
         << lateFee << '\n';

    return 0;
}