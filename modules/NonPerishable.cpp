#include "NonPerishable.h"
#include "../core/ConsoleUI.h"
#include <iostream>

using namespace std;

NonPerishable::NonPerishable(string id, string n, double price, int qty, string suppID, bool refrigerated, string category, int shelfLife, string preservatives)
    : GroceryProduct(id, n, price, qty, suppID, refrigerated, category), shelfLifeMonths(shelfLife), preservativeLevel(preservatives) {}

void NonPerishable::displayStatus() const 
{
    GroceryProduct::displayStatus();
    ConsoleUI::printLabelValue("Storage Category", "Non-Perishable Goods");
    ConsoleUI::printLabelValue("Expected Shelf Life", to_string(shelfLifeMonths) + " Months");
    ConsoleUI::printLabelValue("Preservative Grade", preservativeLevel);
}

void NonPerishable::checkExpiry() 
{
    if (shelfLifeMonths >= 12) 
    {
        ConsoleUI::printSuccess("[OK] " + name + " has a long shelf life of " + to_string(shelfLifeMonths) + " months. No expiry concern.");
    } 
    else if (shelfLifeMonths >= 3) 
    {
        ConsoleUI::printInfo("[NOTE] " + name + " has " + to_string(shelfLifeMonths) + " months shelf life. Monitor stock rotation.");
    } 
    else 
    {
        ConsoleUI::printError("[ATTENTION] " + name + " has only " + to_string(shelfLifeMonths) + " months shelf life. Prioritize selling.");
    }
}

string NonPerishable::getStorageInstructions() const 
{
    string instructions = "";
    instructions += "Category     : " + foodCategory + "\n";
    instructions += "Shelf Life   : " + to_string(shelfLifeMonths) + " months\n";
    instructions += "Preservatives: " + preservativeLevel + "\n";
    instructions += "Refrigeration: ";
    instructions += (isRefrigerated ? "Required" : "Not Required");
    return instructions;
}

double NonPerishable::calculateRisk() const 
{
    if (shelfLifeMonths >= 12) return 0.1;
    if (shelfLifeMonths >= 6)  return 0.2;
    return 0.35;
}

void NonPerishable::applyDiscount(double percentage) 
{
    if (percentage < 0 || percentage > 100) 
    {
        ConsoleUI::printError("Invalid discount percentage.");
        return;
    }
    basePrice -= basePrice * (percentage / 100.0);
    ConsoleUI::printSuccess("Discount applied to " + name + ". New price: $" + ConsoleUI::formatDouble(basePrice));
}

Product* NonPerishable::clone() const 
{
    return new NonPerishable(*this);
}