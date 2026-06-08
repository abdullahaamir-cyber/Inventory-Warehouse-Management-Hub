#ifndef CLOTHING_PRODUCT_H
#define CLOTHING_PRODUCT_H

#include "Product.h"

class ClothingProduct : public Product {
private:
    std::string size;
    std::string material;
    std::string targetSeason; 

public:
    ClothingProduct(std::string id, std::string n, double price, int qty, std::string suppID, std::string sz, std::string mat, std::string season);
    virtual ~ClothingProduct() {}

    virtual void displayStatus() const override;
    virtual void checkExpiry() override; 
    virtual double calculateRisk() const override; 
    virtual void applyDiscount(double percentage) override; 
    void fitGuide() const; // Added to match rubric spec
    virtual Product* clone() const override;

    // Getters for serialisation
    std::string getSize() const { return size; }
    std::string getMaterial() const { return material; }
    std::string getTargetSeason() const { return targetSeason; }
};

#endif