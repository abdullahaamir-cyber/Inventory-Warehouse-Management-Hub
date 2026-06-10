#include "FragileElectronics.h"
#include "../core/ConsoleUI.h"
#include <iostream>

using namespace std;

// Constructor
FragileElectronics::FragileElectronics(string id, string n, double price, int qty, string suppID, int warranty, const char* brand, int fragility, string packaging)
    : ElectronicProduct(id, n, price, qty, suppID, warranty, brand), fragilityRating(fragility), packagingType(packaging) {}

// displayStatus
void FragileElectronics::displayStatus() const 
{
    ElectronicProduct::displayStatus();
    ConsoleUI::printLabelValue("Fragility Rating", to_string(fragilityRating) + "/10");
    ConsoleUI::printLabelValue("Packaging Cushion", packagingType);
}

// checkExpiry
void FragileElectronics::checkExpiry() 
{
    ConsoleUI::printInfo("Hardware Check: Fragile electronics do not expire.");
}

// calculateRisk
double FragileElectronics::calculateRisk() const 
{
    return 0.05 + (fragilityRating * 0.07);
}

// calculateShippingRisk
double FragileElectronics::calculateShippingRisk() const 
{
    double risk = fragilityRating * 0.08;
    if (packagingType == "BubbleWrap" || packagingType == "Foam") 
    {
        risk *= 0.5; // Cushioned packaging reduces risk
    }
    return risk;
}

// applyDiscount
void FragileElectronics::applyDiscount(double percentage) 
{
    ElectronicProduct::applyDiscount(percentage);
}

// clone
Product* FragileElectronics::clone() const 
{
    return new FragileElectronics(*this);
}