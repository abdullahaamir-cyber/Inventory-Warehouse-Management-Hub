#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include "../modules/Product.h"

class Inventory {
    friend class WarehouseManager; // Added to allow engine slot manipulation
private:
    std::string sectionType;
    int capacity;
    Product** slots; // Dynamic array of base pointers (Composition)

public:
    Inventory(std::string type, int maxCapacity = 5);
    
    
    ~Inventory(); 
    Inventory(const Inventory& other); 
    Inventory& operator=(const Inventory& other);

    // Operations
    bool addStockToSlot(Product* p);
    bool removeStockFromSlot(int index); // Handles the 'delete' keyword safely
    void sortByID(); // Added to match rubric spec
    
    // Operator Overloading: Shelf Access
    Product& operator[](int index) const;
    Product& operator[](int index);


    // Getters
    std::string getSectionType() const;
    int getCapacity() const;
};

#endif