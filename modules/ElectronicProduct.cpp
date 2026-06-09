#include "ElectronicProduct.h"
#include <iostream>
using namespace std;

// Constructor
ElectronicProduct::ElectronicProduct(string id, string n, double price, int qty, string suppID, int warranty, const char* brand, int volt) :
 Product(id, n, price, qty, suppID) {

     warrantyMonths = warranty;
     voltage = volt;
     
     //Deep copy the raw C string
     brandName = new char[strlen(brand) + 1];
     strcpy(brandName , brand);
 }

 // Destructor
 ElectronicProduct::~ElectronicProduct() {
    delete[] brandName;
    brandName = nullptr;
 }

 // Copy Constructor
 ElectronicProduct::ElectronicProduct(const ElectronicProduct& other) : Product(other) {

    warrantyMonths = other.warrantyMonths;
    voltage = other.voltage;

    // Deep copy allocate fresh memory don't just copy the pointer
    brandName = new char[strlen(other.brandName) + 1];
    strcpy(brandName , other.brandName);
 }

 // Copy assignment operator
ElectronicProduct& ElectronicProduct::operator=(const ElectronicProduct& other) {

        if(this == &other) return *this;

        Product::operator=(other);

        delete[] brandName;
        brandName = new char[strlen(other.brandName + 1)];
        strcpy(brandName , other.brandName);

        warrantyMonths = other.warrantyMonths;
        voltage = other.voltage;

        return *this;
}

// displayStatus 
void ElectronicProduct::displayStatus() const {
        cout << "  Product ID   : " << productID  << "\n"
         << "  Name         : " << name << "\n"
         << "  Quantity     : " << quantity << "\n"
         << "  Base Price   : " << basePrice << "\n"
         << "  Supplier     : " << linkedSupplierID << "\n"
         << "  Brand        : " << brandName << "\n"
         << "  Voltage      : " << voltage << "V"  << "\n"
         << "  Warranty     : " << warrantyMonths << " months" << "\n";
}

// checkExpiry
void ElectronicProduct::checkExpiry() {
    cout<<"Electronics do not have an expiration limit.\n";
}

// calculateRisk
double ElectronicProduct::calculateRisk() const {
     return 0.03;
}

// applyDiscount
void ElectronicProduct::applyDiscount(double percentage) {
    basePrice -= basePrice * (percentage / 100.0);
}

// testHardware
void ElectronicProduct::testHardware() const {
    cout<<"Testing circuits on " << brandName << " - " << name << "\n";
}

Product* ElectronicProduct::clone() const {
    return new ElectronicProduct(*this); 
}