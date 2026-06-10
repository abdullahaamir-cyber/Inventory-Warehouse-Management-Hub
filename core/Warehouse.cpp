#include "Warehouse.h"
#include "ConsoleUI.h"
#include "../modules/ElectronicProduct.h"
#include "../modules/GroceryProduct.h"
#include "../modules/PerishableGrocery.h"
#include "../modules/NonPerishable.h"
#include "../modules/ClothingProduct.h"
#include <stdexcept>

using namespace std;

Warehouse::Warehouse(string locID) : locationID(locID), totalSquareFootage(10000.0) 
{
    initializeSections();
}

void Warehouse::initializeSections() 
{
    sections.clear();
    sections.push_back(Inventory("Electronics", SECTION_CAPACITY));
    sections.push_back(Inventory("Perishable", SECTION_CAPACITY));
    sections.push_back(Inventory("Non-Perishable", SECTION_CAPACITY));
    sections.push_back(Inventory("Clothing", SECTION_CAPACITY));
}

bool Warehouse::routeIncomingStock(Product* newProduct) 
{
    if (newProduct == nullptr) return false;

    string targetType = "";
    if (dynamic_cast<ElectronicProduct*>(newProduct) != nullptr) 
    {
        targetType = "Electronics";
    } 
    else if (dynamic_cast<PerishableGrocery*>(newProduct) != nullptr) 
    {
        targetType = "Perishable";
    } 
    else if (dynamic_cast<NonPerishable*>(newProduct) != nullptr) 
    {
        targetType = "Non-Perishable";
    } 
    else if (dynamic_cast<ClothingProduct*>(newProduct) != nullptr) 
    {
        targetType = "Clothing";
    }

    for (int i = 0; i < sections.size(); ++i) 
    {
        if (sections[i].getSectionType() == targetType) 
        {
            if (sections[i].addStockToSlot(newProduct)) 
            {
                return true;
            }
        }
    }
    return false;
}

double Warehouse::getGlobalValue() const 
{
    double total = 0.0;
    for (int i = 0; i < sections.size(); ++i) 
    {
        const Inventory& sec = sections[i];
        for (int slot = 0; slot < sec.getCapacity(); ++slot) 
        {
            Product* p = sec.getProduct(slot);
            if (p != nullptr) 
            {
                total += p->calculateValue();
            }
        }
    }
    return total;
}

void Warehouse::findShortages() const 
{
    ConsoleUI::printHeader("Low Stock Audit Alert");
    bool foundShortage = false;

    for (int i = 0; i < sections.size(); ++i) 
    {
        const Inventory& sec = sections[i];
        for (int slot = 0; slot < sec.getCapacity(); ++slot) 
        {
            Product* p = sec.getProduct(slot);
            if (p != nullptr && p->getQuantity() < 5) 
            {
                ConsoleUI::printError("Stock Critical: ID " + p->getID() + " (" + p->getName() 
                                     + ") has " + to_string(p->getQuantity()) + " units remaining.");
                foundShortage = true;
            }
        }
    }

    if (!foundShortage) 
    {
        ConsoleUI::printSuccess("All product inventories maintain safe stock levels (>= 5 units).");
    }
}

Inventory& Warehouse::getSection(int index) 
{
    if (index < 0 || index >= sections.size()) 
    {
        throw out_of_range("Section index out of bounds.");
    }
    return sections[index];
}

const Inventory& Warehouse::getSection(int index) const 
{
    if (index < 0 || index >= sections.size()) 
    {
        throw out_of_range("Section index out of bounds.");
    }
    return sections[index];
}

int Warehouse::getSectionCount() const 
{
    return sections.size();
}

std::ostream& operator<<(std::ostream& os, const Warehouse& wh) 
{
    os << "Warehouse: " << wh.locationID << " (" << wh.totalSquareFootage << " Sq. Ft.)\n";
    for (int i = 0; i < wh.sections.size(); ++i) 
    {
        const Inventory& sec = wh.sections[i];
        int occupied = 0;
        for (int slot = 0; slot < sec.getCapacity(); ++slot) 
        {
            if (sec.getProduct(slot) != nullptr) occupied++;
        }
        os << " - Sec " << i << " [" << sec.getSectionType() << "]: " 
           << occupied << "/" << sec.getCapacity() << " slots filled\n";
    }
    return os;
}
