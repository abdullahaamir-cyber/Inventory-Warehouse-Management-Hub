#include "ElectronicProduct.h"
#include "../core/ConsoleUI.h"
#include <iostream>
#include <cstring>

using namespace std;

// Constructor
ElectronicProduct::ElectronicProduct(string id, string n, double price, int qty, string suppID, int warranty, const char* brand, int volt) :
 Product(id, n, price, qty, suppID) {
     warrantyMonths = warranty;
     voltage = volt;
     
     // Deep copy the raw C string
     if (brand) {
         brandName = new char[strlen(brand) + 1];
         strcpy(brandName, brand);
     } else {
         brandName = new char[1];
         brandName[0] = '\0';
     }
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

     // Deep copy allocation
     brandName = new char[strlen(other.brandName) + 1];
     strcpy(brandName, other.brandName);
 }

 // Copy assignment operator
 ElectronicProduct& ElectronicProduct::operator=(const ElectronicProduct& other) {
    if (this == &other) return *this;

    Product::operator=(other);

    delete[] brandName;
    brandName = new char[strlen(other.brandName) + 1];
    strcpy(brandName, other.brandName);

    warrantyMonths = other.warrantyMonths;
    voltage = other.voltage;

    return *this;
}

// displayStatus 
void ElectronicProduct::displayStatus() const {
    ConsoleUI::printLabelValue("Product ID", productID);
    ConsoleUI::printLabelValue("Name", name);
    ConsoleUI::printLabelValue("Stock Quantity", to_string(quantity));
    ConsoleUI::printLabelValue("Base Price", "$" + ConsoleUI::formatDouble(basePrice));
    ConsoleUI::printLabelValue("Supplier ID", linkedSupplierID);
    ConsoleUI::printLabelValue("Brand", brandName);
    ConsoleUI::printLabelValue("Voltage", to_string(voltage) + "V");
    ConsoleUI::printLabelValue("Warranty Period", to_string(warrantyMonths) + " Months");
}

// checkExpiry
void ElectronicProduct::checkExpiry() {
    ConsoleUI::printInfo("Hardware Check: Electronic items do not expire.");
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
    ConsoleUI::printInfo("Testing circuits on " + string(brandName) + " - " + name + "... PASSED.");
}

Product* ElectronicProduct::clone() const {
    return new ElectronicProduct(*this); 
}