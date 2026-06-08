#ifndef FRAGILE_ELECTRONICS_H
#define FRAGILE_ELECTRONICS_H

#include "ElectronicProduct.h"

class FragileElectronics : public ElectronicProduct {
private:
    int fragilityRating; 
    std::string packagingType;

public:
    FragileElectronics(std::string id, std::string n, double price, int qty, std::string suppID, int warranty, const char* brand, int fragility, std::string packaging);
    virtual ~FragileElectronics() {}

    virtual void displayStatus() const override;
    virtual void checkExpiry() override;
    virtual double calculateRisk() const override; 
    virtual void applyDiscount(double percentage) override;
    double calculateShippingRisk() const; // Added to match rubric spec
    virtual Product* clone() const override;

    // Getters for serialisation
    int getFragilityRating() const { return fragilityRating; }
    std::string getPackagingType() const { return packagingType; }
};

#endif