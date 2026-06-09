#include "FragileElectronics.h"
#include <iostream>
using namespace std;


// Constructor
FragileElectronics::FragileElectronics(string id, string n, double price,int qty, string suppID, int warranty, const char* brand, int fragility, string packaging)
    : ElectronicProduct(id, n, price, qty, suppID, warranty, brand)
{
    fragilityRating = fragility;
    packagingType   = packaging;
}

// displayStatus
void FragileElectronics::displayStatus() const {
    
    ElectronicProduct::displayStatus();

    cout << "  Fragility    : " << fragilityRating << "\n"
         << "  Packaging    : " << packagingType   << "\n";
}

// checkExpiry
void FragileElectronics::checkExpiry() {
    cout << "Fragile electronics do not have an expiration limit.\n";
}

// calculateRisk
double FragileElectronics::calculateRisk() const {
    return fragilityRating * 0.07;
}

//calculateShippingrisk
double FragileElectronics::calculateShippingRisk() const {
    double risk = calculateRisk();

    if (packagingType == "BubbleWrap" || packagingType == "Foam") {
        risk *= 0.5;
    }

    return risk;
}

// applyDiscount
void FragileElectronics::applyDiscount(double percentage) {
    ElectronicProduct::applyDiscount(percentage);
}

// clone
Product* FragileElectronics::clone() const {
    return new FragileElectronics(*this);
}