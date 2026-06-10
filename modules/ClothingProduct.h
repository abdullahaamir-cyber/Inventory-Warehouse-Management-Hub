#ifndef CLOTHING_PRODUCT_H
#define CLOTHING_PRODUCT_H

#include "Product.h"

// Subclass representing apparel products
class ClothingProduct : public Product {
private:
    std::string size;
    std::string material;
    std::string targetSeason; 

public:
    ClothingProduct(std::string id, std::string n, double price, int qty, std::string suppID, std::string sz, std::string mat, std::string season);
    virtual ~ClothingProduct() {}

    // Polymorphic implementations
    virtual void displayStatus() const override;
    virtual void checkExpiry() override; 
    virtual double calculateRisk() const override; 
    virtual void applyDiscount(double percentage) override; 
    virtual Product* clone() const override;

    // Apparel operations
    void fitGuide() const;

    // Getters
    std::string getSize() const { return size; }
    std::string getMaterial() const { return material; }
    std::string getTargetSeason() const { return targetSeason; }
};

#endif