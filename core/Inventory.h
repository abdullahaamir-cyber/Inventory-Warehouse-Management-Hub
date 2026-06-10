#ifndef INVENTORY_H
#define INVENTORY_H

#include "../modules/Product.h"
#include <string>

// Category-specific shelf containing product slots
class Inventory {
    friend class WarehouseManager;
    friend class Warehouse;
private:
    std::string sectionType;
    int capacity;
    Product** slots; // Array of polymorphic Product pointers

public:
    Inventory(std::string type = "General", int maxCapacity = 5);
    ~Inventory(); 

    // Deep copy support
    Inventory(const Inventory& other); 
    Inventory& operator=(const Inventory& other);

    // Operations
    bool addStockToSlot(Product* p);
    bool removeStockFromSlot(int index); // Cleans up dynamic memory
    void sortByID();
    
    // Slot index accessors
    Product& operator[](int index) const;
    Product& operator[](int index);

    // Getters
    std::string getSectionType() const;
    int getCapacity() const;
    Product* getProduct(int index) const { return (index >= 0 && index < capacity) ? slots[index] : nullptr; }
};

#endif