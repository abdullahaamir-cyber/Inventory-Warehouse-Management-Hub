#include "ClothingProduct.h"
#include <iostream>

using namespace std;

ClothingProduct::ClothingProduct(string id, string n, double price, int qty,
    string suppID, string sz, string mat, string season)
    : Product(id, n, price, qty, suppID),
      size(sz),
      material(mat),
      targetSeason(season)
{}

void ClothingProduct::displayStatus() const {
    cout << "----------------------------------------\n";
    cout << "  [CLOTHING] " << name << " (ID: " << productID << ")\n";
    cout << "  Size       : " << size << "\n";
    cout << "  Material   : " << material << "\n";
    cout << "  Season     : " << targetSeason << "\n";
    cout << "  Price      : Rs." << basePrice << "\n";
    cout << "  Quantity   : " << quantity << "\n";
    cout << "  Supplier   : " << linkedSupplierID << "\n";
    cout << "----------------------------------------\n";
}

void ClothingProduct::checkExpiry() {
    // clothing does not expire but seasonal relevance matters
    cout << "[INFO] " << name << " is a " << targetSeason
         << " season item. No expiry date applicable.\n";
}

double ClothingProduct::calculateRisk() const {
    // risk based on season relevance,winter items riskier in summer stock
    if (targetSeason == "Winter" || targetSeason == "winter")
        return 0.3;
    if (targetSeason == "Summer" || targetSeason == "summer")
        return 0.2;
    return 0.15;
}

void ClothingProduct::applyDiscount(double percentage) {
    if (percentage < 0 || percentage > 100) {
        cout << "[ERROR] Invalid discount percentage.\n";
        return;
    }
    basePrice -= basePrice * (percentage / 100.0);
    cout << "[DISCOUNT] " << name << " new price: Rs." << basePrice << "\n";
}

void ClothingProduct::fitGuide() const {
    cout << "----------------------------------------\n";
    cout << "  Fit Guide for: " << name << "\n";
    cout << "  Size         : " << size << "\n";
    cout << "  Material     : " << material << "\n";
    cout << "  Best Season  : " << targetSeason << "\n";

    if (material == "Cotton" || material == "cotton")
        cout << "  Care         : Machine wash cold, tumble dry low.\n";
    else if (material == "Wool" || material == "wool")
        cout << "  Care         : Dry clean only.\n";
    else if (material == "Polyester" || material == "polyester")
        cout << "  Care         : Machine wash warm.\n";
    else
        cout << "  Care         : Follow label instructions.\n";

    cout << "----------------------------------------\n";
}

Product* ClothingProduct::clone() const {
    return new ClothingProduct(*this);
}