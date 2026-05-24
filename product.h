#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    // The Attributes that should not be changed by subclasses (read-only)
    int productID;
    double price;
    int quantity;

protected:
    std::string productName; 

public:
    // Constructor
    Product();
    Product(int id, std::string name, double price, int qty);

    // Destructor 
    virtual ~Product();


    // Getters (subclasses can access these, but cannot modify them directly)
    int getProductID() const;
    double getPrice() const;
    int getQuantity() const;
    std::string getProductName() const;


    // Setters with validation
    void setPrice(double p);
    void setQuantity(int q);


    // Pure virtual functions (to be implemented by subclasses)
    virtual void displayStatus() const = 0;
    virtual double calculateRisk() const = 0;
    virtual void applyDiscount(double percent) = 0;


    // Utility function (price * quantity)
    double calculateValue() const; 

    // Operator overloading for output
    friend std::ostream& operator<<(std::ostream& os, const Product& p);
};

#endif