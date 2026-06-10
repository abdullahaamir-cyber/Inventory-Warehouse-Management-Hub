#include "ClothingProduct.h"
#include "../core/ConsoleUI.h"
#include <iostream>

using namespace std;

ClothingProduct::ClothingProduct(string id, string n, double price, int qty, string suppID, string sz, string mat, string season)
    : Product(id, n, price, qty, suppID), size(sz), material(mat), targetSeason(season) {}

void ClothingProduct::displayStatus() const 
{
    ConsoleUI::printLabelValue("Product ID", productID);
    ConsoleUI::printLabelValue("Name", name);
    ConsoleUI::printLabelValue("Stock Quantity", to_string(quantity));
    ConsoleUI::printLabelValue("Base Price", "$" + ConsoleUI::formatDouble(basePrice));
    ConsoleUI::printLabelValue("Supplier ID", linkedSupplierID);
    ConsoleUI::printLabelValue("Garment Size", size);
    ConsoleUI::printLabelValue("Fabric/Material", material);
    ConsoleUI::printLabelValue("Target Season", targetSeason);
}

void ClothingProduct::checkExpiry() 
{
    ConsoleUI::printInfo("Seasonal Check: " + name + " is designated for " + targetSeason + " (no chemical expiration).");
}

double ClothingProduct::calculateRisk() const 
{
    if (targetSeason == "Winter" || targetSeason == "winter") return 0.3;
    if (targetSeason == "Summer" || targetSeason == "summer") return 0.2;
    return 0.15;
}

void ClothingProduct::applyDiscount(double percentage) 
{
    if (percentage < 0 || percentage > 100) 
    {
        ConsoleUI::printError("Invalid discount percentage.");
        return;
    }
    basePrice -= basePrice * (percentage / 100.0);
    ConsoleUI::printSuccess("Discount applied to " + name + ". New price: $" + ConsoleUI::formatDouble(basePrice));
}

void ClothingProduct::fitGuide() const 
{
    ConsoleUI::printHeader("Garment Fit & Fabric Guide");
    ConsoleUI::printLabelValue("Product Name", name);
    ConsoleUI::printLabelValue("Garment Size", size);
    ConsoleUI::printLabelValue("Fabric Composition", material);
    ConsoleUI::printLabelValue("Recommended Season", targetSeason);

    if (material == "Cotton" || material == "cotton") 
    {
        ConsoleUI::printInfo("Care Instructions: Machine wash cold, tumble dry low.");
    } 
    else if (material == "Wool" || material == "wool") 
    {
        ConsoleUI::printInfo("Care Instructions: Dry clean only to avoid shrinkage.");
    } 
    else if (material == "Polyester" || material == "polyester") 
    {
        ConsoleUI::printInfo("Care Instructions: Machine wash warm, iron low.");
    } 
    else 
    {
        ConsoleUI::printInfo("Care Instructions: Standard wash. Follow inner tag instructions.");
    }
    ConsoleUI::printDivider();
}

Product* ClothingProduct::clone() const 
{
    return new ClothingProduct(*this);
}