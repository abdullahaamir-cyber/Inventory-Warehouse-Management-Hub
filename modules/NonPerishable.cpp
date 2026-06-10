#include "NonPerishable.h"
#include <iostream>

using namespace std;

NonPerishable::NonPerishable(string id, string n, double price, int qty,
    string suppID, bool refrigerated, string category,
    int shelfLife, string preservatives)
    : GroceryProduct(id, n, price, qty, suppID, refrigerated, category),
      shelfLifeMonths(shelfLife),
      preservativeLevel(preservatives)
{}

void NonPerishable::displayStatus() const {
    GroceryProduct::displayStatus();
    cout << "  Type       : Non-Perishable\n";
    cout << "  Shelf Life : " << shelfLifeMonths << " months\n";
    cout << "  Preservatives: " << preservativeLevel << "\n";
    cout << "----------------------------------------\n";
}

void NonPerishable::checkExpiry() {
    if (shelfLifeMonths >= 12)
        cout << "[OK] " << name << " has a long shelf life of "
             << shelfLifeMonths << " months. No expiry concern.\n";
    else if (shelfLifeMonths >= 3)
        cout << "[NOTE] " << name << " has " << shelfLifeMonths
             << " months shelf life. Monitor stock rotation.\n";
    else
        cout << "[ATTENTION] " << name << " has only " << shelfLifeMonths
             << " months shelf life. Prioritize selling.\n";
}

string NonPerishable::getStorageInstructions() const {
    string instructions = "";
    instructions += "Category     : " + foodCategory + "\n";
    instructions += "Shelf Life   : " + to_string(shelfLifeMonths) + " months\n";
    instructions += "Preservatives: " + preservativeLevel + "\n";
    instructions += "Refrigeration: ";
    instructions += (isRefrigerated ? "Required" : "Not Required");
    return instructions;
}

double NonPerishable::calculateRisk() const {
    // longer shelf life = lower risk
    if (shelfLifeMonths >= 12) return 0.1;
    if (shelfLifeMonths >= 6)  return 0.2;
    return 0.35;
}

void NonPerishable::applyDiscount(double percentage) {
    if (percentage < 0 || percentage > 100) {
        cout << "[ERROR] Invalid discount percentage.\n";
        return;
    }
    basePrice -= basePrice * (percentage / 100.0);
    cout << "[DISCOUNT] " << name << " new price: Rs." << basePrice << "\n";
}

Product* NonPerishable::clone() const {
    return new NonPerishable(*this);
}