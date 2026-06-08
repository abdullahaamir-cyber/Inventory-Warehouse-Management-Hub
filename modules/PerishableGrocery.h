#ifndef PERISHABLE_GROCERY_H
#define PERISHABLE_GROCERY_H

#include "GroceryProduct.h"
#include "../core/Date.h"

class PerishableGrocery : public GroceryProduct {
private:
    Date expiryDate;
    double storageTempRequired;

public:
    PerishableGrocery(std::string id, std::string n, double price, int qty, std::string suppID, bool refrigerated, std::string category, Date expiry, double temp);
    virtual ~PerishableGrocery() {}

    virtual void displayStatus() const override;
    virtual void checkExpiry() override; 
    virtual double calculateRisk() const override; 
    virtual void applyDiscount(double percentage) override;
    virtual Product* clone() const override;

    // Getters for serialisation
    Date getExpiryDate() const { return expiryDate; }
    double getStorageTempRequired() const { return storageTempRequired; }
};

#endif