#include "Product.h"
#include <string>
using namespace std;

// Parameterized constructor
Product::Product(string id, string n, double price, int qty, string suppID) :
productID(id), name(n), basePrice(price), quantity(qty), linkedSupplierID(suppID) {}

// Operator Overloading 
Product& Product::operator+(int incomingQuantity) {
    quantity += incomingQuantity;
    return *this;
}

// Comparison Operator
bool Product::operator==(const Product& other) const {
    return productID == other.productID;
}

// Getters / Utility
string Product::getID() const {
    return productID;
}

string Product::getName() const {
    return name;
}

int Product::getQuantity() const {
    return quantity;
}

double Product::calculateValue() const {
    return basePrice * quantity;
}

void Product::reduceQuantity(int amount) {
    if(amount > quantity) 
     quantity = 0;
    else
     quantity -= amount;
}

string Product::getSupplier() const {
    return linkedSupplierID;
}

double Product::getBasePrice() const {
    return basePrice;
}