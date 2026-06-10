#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

// Abstract base class representing a warehouse product
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

    // Polymorphic operations
    virtual void displayStatus() const = 0;
    virtual void checkExpiry() = 0;
    virtual double calculateRisk() const = 0;
    virtual void applyDiscount(double percentage) = 0;
    virtual Product* clone() const = 0;

    // Operator Overloading
    Product& operator+(int incomingQuantity);
    bool operator==(const Product& other) const;

    // Getters and helper methods
    std::string getID() const;
    std::string getName() const;
    int getQuantity() const;
    double calculateValue() const; // price * quantity
    void reduceQuantity(int amount);
    std::string getSupplier() const;
    double getBasePrice() const;
};

#endif