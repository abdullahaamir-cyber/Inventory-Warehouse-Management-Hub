#ifndef GROCERY_PRODUCT_H
#define GROCERY_PRODUCT_H

#include "Product.h"

class GroceryProduct : public Product {
protected:
    bool isRefrigerated;
    std::string foodCategory;
    int calories;      // Added to match rubric spec
    bool isHalal;       // Added to match rubric spec

public:
    GroceryProduct(std::string id, std::string n, double price, int qty, std::string suppID, bool refrigerated, std::string category, int cals = 150, bool halal = true);
    virtual ~GroceryProduct() {}
    
    virtual void displayStatus() const override;
    void checkSafety() const; // Added to match rubric spec

    // Getters for serialisation
    bool getIsRefrigerated() const { return isRefrigerated; }
    std::string getFoodCategory() const { return foodCategory; }
    int getCalories() const { return calories; }
    bool getIsHalal() const { return isHalal; }
};

#endif