#include "PerishableGrocery.h"
#include <iostream>

using namespace std;

// This will come from Member 6's engine
// Ask Member 6 to declare this in their file
extern Date currentSystemDate;

PerishableGrocery::PerishableGrocery(string id, string n, double price,
    int qty, string suppID, bool refrigerated,
    string category, Date expiry, double temp)
    : GroceryProduct(id, n, price, qty, suppID, refrigerated, category),
      expiryDate(expiry),
      storageTempRequired(temp)
{}

void PerishableGrocery::displayStatus() const {
    GroceryProduct::displayStatus();
    cout << "  Type       : Perishable\n";
    cout << "  Expiry Date: " << expiryDate << "\n";
    cout << "  Storage Temp: " << storageTempRequired << " degrees C\n";
    cout << "----------------------------------------\n";
}

void PerishableGrocery::checkExpiry() {
    // compare expiryDate with today using Date operators
    if (expiryDate < currentSystemDate) {
        cout << "[EXPIRED]  " << name << " expired on "
             << expiryDate << ". Remove from shelf immediately.\n";
    }
    else if (expiryDate == currentSystemDate) {
        cout << "[CRITICAL] " << name << " expires TODAY ("
             << expiryDate << "). Apply discount now.\n";
    }
    else {
        // check if expiry is within same month - close to expiring
        bool sameMonth = (expiryDate.getMonth() == currentSystemDate.getMonth()
                       && expiryDate.getYear() == currentSystemDate.getYear());

        if (sameMonth) {
            cout << "[WARNING]  " << name << " is expiring this month on "
                 << expiryDate << ". Consider discounting.\n";
        } else {
            cout << "[FRESH]    " << name << " is good until "
                 << expiryDate << ".\n";
        }
    }
}

double PerishableGrocery::calculateRisk() const {
    // refrigerated perishables are highest risk
    // non refrigerated perishables are still high risk
    if (isRefrigerated)
        return 0.85;
    return 0.65;
}

void PerishableGrocery::applyDiscount(double percentage) {
    if (percentage < 0 || percentage > 100) {
        cout << "[ERROR] Invalid discount percentage for " << name << ".\n";
        return;
    }
    basePrice -= basePrice * (percentage / 100.0);
    cout << "[DISCOUNT] " << name << " discounted. New price: Rs."
         << basePrice << "\n";
}

Product* PerishableGrocery::clone() const {
    return new PerishableGrocery(*this);
}
