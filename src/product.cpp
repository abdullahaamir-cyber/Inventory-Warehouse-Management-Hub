#include "../include/product.h"
#include <iostream>

using namespace std;


int Product::nextID = 100;

//Constructors 
Product::Product() : productID(nextID++), price(0.0), quantity(0), productName("Unknown") {}

Product::Product(string name,double price,int qty) : productID(nextID++), productName(name), price(price), quantity(qty) {}

//Destructor
Product::~Product() {}

//Getters
int Product::getProductID() const {
    return productID;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

string Product::getProductName() const {
    return productName;
}

//Setters with Validation
void Product::setPrice(double p) {
      if(p < 0)
      throw invalid_argument("Price cannot be negative");
      price = p;
}

void Product::setQuantity(int q) {
     if(q < 0)
     throw invalid_argument("Quantity cannot be negative");
     quantity = q;
}

//Utility Function
double Product::calculateValue() const {
    return price * quantity;
}

//Operator overloading for output
ostream& operator <<(ostream& os, const Product& p) {
  p.displayStatus();
   return os;
}




