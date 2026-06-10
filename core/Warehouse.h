#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "DynamicArray.h"
#include <string>
#include <iostream>
#include "Inventory.h"
#include "../modules/Product.h"

// Facility containing multiple inventory sections
class Warehouse {
    friend class WarehouseManager;
    friend class FileHandler;
public:
    static const int MAX_SECTIONS = 4;
    static const int SECTION_CAPACITY = 5;

private:
    std::string locationID;
    double totalSquareFootage;
    DynamicArray<Inventory> sections;

public:
    Warehouse(std::string locID = "MAIN-FACILITY");
    
    // Allocates category sections (Electronics, Perishable, etc.)
    void initializeSections();

    // Core warehouse operations
    bool routeIncomingStock(Product* newProduct);
    double getGlobalValue() const;
    void findShortages() const;
    
    // Getters
    Inventory& getSection(int index);
    const Inventory& getSection(int index) const;
    int getSectionCount() const;

    // prints the layout map to stream
    friend std::ostream& operator<<(std::ostream& os, const Warehouse& wh);
};

#endif