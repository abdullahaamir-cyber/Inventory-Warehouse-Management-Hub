#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
protected: 
    std::string productID;
    std::string name;
    double basePrice;
    int quantity;
    std::string linkedSupplierID;

public:
    Product(std::string id, std::string n, double price, int qty, std::string suppID);
    
    
    virtual ~Product() {}

    
    virtual void displayStatus() const = 0;
    virtual void checkExpiry() = 0;
    virtual double calculateRisk() const = 0;
    virtual void applyDiscount(double percentage) = 0;
    virtual Product* clone() const = 0; // Added for polymorphic deep copy

    // Operator Overloading
    Product& operator+(int incomingQuantity);
    bool operator==(const Product& other) const;

    // Getters / Utility
    std::string getID() const;
    std::string getName() const;
    int getQuantity() const;
    double calculateValue() const; // Value = price * quantity
    void reduceQuantity(int amount);
    std::string getSupplier() const;
    double getBasePrice() const; // To allow accessing base price in discount calculations
};

#endif