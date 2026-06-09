#ifndef ELECTRONIC_PRODUCT_H
#define ELECTRONIC_PRODUCT_H

#include "Product.h"

class ElectronicProduct : public Product {
protected:
    int warrantyMonths;
    char* brandName;
    int voltage; // Added to match rubric spec

public:
    ElectronicProduct(std::string id, std::string n, double price, int qty, std::string suppID, int warranty, const char* brand, int volt = 220);
    
    virtual ~ElectronicProduct();
    ElectronicProduct(const ElectronicProduct& other);
    ElectronicProduct& operator=(const ElectronicProduct& other);

    virtual void displayStatus() const override; 
    virtual void checkExpiry() override;
    virtual double calculateRisk() const override;
    virtual void applyDiscount(double percentage) override;
    virtual Product* clone() const override;
    void testHardware() const; // Added to match rubric spec
    
    // Getters for serialisation
    int getWarrantyMonths() const { return warrantyMonths; }
    const char* getBrandName() const { return brandName; }
    int getVoltage() const { return voltage; }
};

#endif