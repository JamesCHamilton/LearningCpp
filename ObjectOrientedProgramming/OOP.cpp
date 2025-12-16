#include <iostream>
#include <string>
using namespace std;//don't actually use this in real code

// Base class (Parent)
class Vehicle {
protected:
    string brand;
    int year;
public:
    Vehicle(string b, int y) : brand(b), year(y) {}

    virtual void displayInfo() { // virtual = allows polymorphism
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
};

// Derived class (Child) - Inheritance
class Car : public Vehicle {
private:
    int doors;
public:
    Car(string b, int y, int d) : Vehicle(b, y), doors(d) {}

    // Override (Polymorphism)
    void displayInfo() override {
        cout << "Car -> Brand: " << brand << ", Year: " << year 
             << ", Doors: " << doors << endl;
    }
};

// Another derived class
class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
public:
    Motorcycle(string b, int y, bool sidecar) : Vehicle(b, y), hasSidecar(sidecar) {}

    void displayInfo() override {
        cout << "Motorcycle -> Brand: " << brand << ", Year: " << year
             << ", Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }
};

// Main function
int main() {
    Vehicle* v1 = new Car("Toyota", 2022, 4);
    Vehicle* v2 = new Motorcycle("Harley-Davidson", 2021, false);

    v1->displayInfo();  // Calls Car’s displayInfo()
    v2->displayInfo();  // Calls Motorcycle’s displayInfo()

    delete v1;
    delete v2;

    return 0;
}
