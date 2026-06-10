#include "GroceryProduct.h"
#include "../core/ConsoleUI.h"
#include <iostream>

using namespace std;

GroceryProduct::GroceryProduct(string id, string n, double price, int qty, string suppID, bool refrigerated, string category, int cals, bool halal)
    : Product(id, n, price, qty, suppID), isRefrigerated(refrigerated), foodCategory(category), calories(cals), isHalal(halal) {}

void GroceryProduct::displayStatus() const 
{
    ConsoleUI::printLabelValue("Product ID", productID);
    ConsoleUI::printLabelValue("Name", name);
    ConsoleUI::printLabelValue("Stock Quantity", to_string(quantity));
    ConsoleUI::printLabelValue("Base Price", "$" + ConsoleUI::formatDouble(basePrice));
    ConsoleUI::printLabelValue("Supplier ID", linkedSupplierID);
    ConsoleUI::printLabelValue("Food Category", foodCategory);
    ConsoleUI::printLabelValue("Calories Count", to_string(calories) + " kcal");
    ConsoleUI::printLabelValue("Refrigeration Needed", isRefrigerated ? "YES" : "NO");
    ConsoleUI::printLabelValue("Halal Certified", isHalal ? "YES" : "NO");
}

void GroceryProduct::checkSafety() const 
{
    if (isHalal) 
    {
        ConsoleUI::printSuccess("Safety Check: " + name + " is verified [Halal Certified].");
    } 
    else 
    {
        ConsoleUI::printInfo("Safety Check: " + name + " conforms to standard health regulations.");
    }
}
