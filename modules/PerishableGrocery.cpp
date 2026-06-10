#include "PerishableGrocery.h"
#include "../core/ConsoleUI.h"
#include <iostream>

using namespace std;

extern Date currentSystemDate;

PerishableGrocery::PerishableGrocery(string id, string n, double price, int qty, string suppID, bool refrigerated, string category, Date expiry, double temp)
    : GroceryProduct(id, n, price, qty, suppID, refrigerated, category), expiryDate(expiry), storageTempRequired(temp) {}

void PerishableGrocery::displayStatus() const 
{
    GroceryProduct::displayStatus();
    ConsoleUI::printLabelValue("Storage Category", "Perishable Fresh Goods");
    ConsoleUI::printLabelValue("Cargo Expiry Date", expiryDate.toString());
    ConsoleUI::printLabelValue("Required Storage Temp", ConsoleUI::formatDouble(storageTempRequired) + " °C");
}

void PerishableGrocery::checkExpiry() 
{
    if (expiryDate < currentSystemDate) 
    {
        ConsoleUI::printError("[EXPIRED] " + name + " expired on " + expiryDate.toString() + ". Remove from shelf immediately.");
    }
    else if (expiryDate == currentSystemDate) 
    {
        ConsoleUI::printError("[CRITICAL] " + name + " expires TODAY (" + expiryDate.toString() + "). Apply discount now.");
    }
    else 
    {
        bool sameMonth = (expiryDate.getMonth() == currentSystemDate.getMonth() && expiryDate.getYear() == currentSystemDate.getYear());
        if (sameMonth) 
        {
            ConsoleUI::printError("[WARNING] " + name + " is expiring this month on " + expiryDate.toString() + ". Consider discounting.");
        } 
        else 
        {
            ConsoleUI::printSuccess("[FRESH] " + name + " is good until " + expiryDate.toString() + ".");
        }
    }
}

double PerishableGrocery::calculateRisk() const 
{
    if (isRefrigerated) return 0.85;
    return 0.65;
}

void PerishableGrocery::applyDiscount(double percentage) 
{
    if (percentage < 0 || percentage > 100) 
    {
        ConsoleUI::printError("Invalid discount percentage for " + name);
        return;
    }
    basePrice -= basePrice * (percentage / 100.0);
    ConsoleUI::printSuccess("Discount applied to " + name + ". New price: $" + ConsoleUI::formatDouble(basePrice));
}

Product* PerishableGrocery::clone() const 
{
    return new PerishableGrocery(*this);
}
