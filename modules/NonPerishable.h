#ifndef NON_PERISHABLE_H
#define NON_PERISHABLE_H

#include "GroceryProduct.h"

class NonPerishable : public GroceryProduct {
private:
    int shelfLifeMonths;
    std::string preservativeLevel; // Added to match rubric spec

public:
    NonPerishable(std::string id, std::string n, double price, int qty, std::string suppID, bool refrigerated, std::string category, int shelfLife, std::string preservatives = "Normal");
    virtual ~NonPerishable() {}

    virtual void displayStatus() const override;
    virtual void checkExpiry() override; 
    virtual double calculateRisk() const override;
    virtual void applyDiscount(double percentage) override;
    std::string getStorageInstructions() const; // Added to match rubric spec
    virtual Product* clone() const override;

    // Getters for serialisation
    int getShelfLifeMonths() const { return shelfLifeMonths; }
    std::string getPreservativeLevel() const { return preservativeLevel; }
};

#endif