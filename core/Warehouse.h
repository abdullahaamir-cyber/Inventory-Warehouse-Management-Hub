#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "DynamicArray.h"
#include <string>
#include <iostream>
#include "Inventory.h"
#include "../modules/Product.h"

class Warehouse {
    friend class WarehouseManager; // Added to allow engine direct access to sections
public:
    static const int MAX_SECTIONS = 4;
    static const int SECTION_CAPACITY = 5;

private:
    std::string locationID;
    double totalSquareFootage; // Added to match rubric spec
    DynamicArray<Inventory> sections; // Aggregation of sections

public:
    Warehouse(std::string locID = "MAIN-FACILITY");
    
    // Setup
    void initializeSections();

    // Operations
    bool routeIncomingStock(Product* newProduct);
    double getGlobalValue() const;
    void findShortages() const;
    
    // Getters
    Inventory& getSection(int index);
    int getSectionCount() const;

    // Operator Overloading: Prints the whole warehouse map
    friend std::ostream& operator<<(std::ostream& os, const Warehouse& wh);
};

#endif