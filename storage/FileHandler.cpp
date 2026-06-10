#include "FileHandler.h"
#include "../engine/WarehouseManager.h"
#include "../core/ConsoleUI.h"
#include "../modules/FragileElectronics.h"
#include "../modules/ElectronicProduct.h"
#include "../modules/PerishableGrocery.h"
#include "../modules/NonPerishable.h"
#include "../modules/ClothingProduct.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Static helper to split a line by commas
static DynamicArray<string> split(const string& s, char delimiter) 
{
    DynamicArray<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

void FileHandler::loadSuppliers(WarehouseManager& engine, const string& filename) 
{
    ifstream file(filename);
    if (!file) 
    {
        // If file doesn't exist, start with clean list silently
        return;
    }

    engine.systemSuppliers.clear();
    string line;
    while (getline(file, line)) 
    {
        if (line.empty()) continue;
        DynamicArray<string> tokens = split(line, ',');
        if (tokens.size() < 4) continue;

        string id = tokens[0];
        string name = tokens[1];
        double score = stod(tokens[2]);
        string terms = tokens[3];

        Supplier s(id, name, terms);
        s.performanceScore = score; // Accessible due to friendship
        engine.systemSuppliers.push_back(s);
    }
}

void FileHandler::saveSuppliers(const WarehouseManager& engine, const string& filename) 
{
    ofstream file(filename);
    if (!file) 
    {
        ConsoleUI::printError("Failed to write supplier backup: " + filename);
        return;
    }

    for (int i = 0; i < engine.systemSuppliers.size(); ++i) 
    {
        const Supplier& s = engine.systemSuppliers[i];
        file << s.getID() << ","
             << s.getName() << ","
             << s.getPerformanceScore() << ","
             << s.getContractTerms() << "\n";
    }
}

void FileHandler::loadProducts(WarehouseManager& engine, const string& filename) 
{
    ifstream file(filename);
    if (!file) 
    {
        // If file doesn't exist, start with empty layout
        return;
    }

    // Reset layout before loading
    engine.localWarehouse.initializeSections();

    string line;
    while (getline(file, line)) 
    {
        if (line.empty()) continue;
        DynamicArray<string> tokens = split(line, ',');
        if (tokens.size() < 6) continue;

        string type = tokens[0];
        string id = tokens[1];
        string name = tokens[2];
        double price = stod(tokens[3]);
        int qty = stoi(tokens[4]);
        string suppID = tokens[5];

        Product* prod = nullptr;

        if (type == "ELEC" && tokens.size() >= 9) 
        {
            int warranty = stoi(tokens[6]);
            string brand = tokens[7];
            int volt = stoi(tokens[8]);
            prod = new ElectronicProduct(id, name, price, qty, suppID, warranty, brand.c_str(), volt);
        } 
        else if (type == "FRAG" && tokens.size() >= 10) 
        {
            int warranty = stoi(tokens[6]);
            string brand = tokens[7];
            int fragility = stoi(tokens[8]);
            string packaging = tokens[9];
            prod = new FragileElectronics(id, name, price, qty, suppID, warranty, brand.c_str(), fragility, packaging);
        } 
        else if (type == "PERI" && tokens.size() >= 10) 
        {
            bool refrig = (stoi(tokens[6]) == 1);
            string cat = tokens[7];
            Date expiry = Date::parseString(tokens[8]);
            double temp = stod(tokens[9]);
            prod = new PerishableGrocery(id, name, price, qty, suppID, refrig, cat, expiry, temp);
        } 
        else if (type == "NPER" && tokens.size() >= 10) 
        {
            bool refrig = (stoi(tokens[6]) == 1);
            string cat = tokens[7];
            int shelfLife = stoi(tokens[8]);
            string preservatives = tokens[9];
            prod = new NonPerishable(id, name, price, qty, suppID, refrig, cat, shelfLife, preservatives);
        } 
        else if (type == "CLOT" && tokens.size() >= 9) 
        {
            string sizeStr = tokens[6];
            string materialStr = tokens[7];
            string seasonStr = tokens[8];
            prod = new ClothingProduct(id, name, price, qty, suppID, sizeStr, materialStr, seasonStr);
        }

        if (prod != nullptr) 
        {
            if (!engine.localWarehouse.routeIncomingStock(prod)) 
            {
                delete prod; // Memory safety
            }
        }
    }
}

void FileHandler::saveProducts(const WarehouseManager& engine, const string& filename) 
{
    ofstream file(filename);
    if (!file) 
    {
        ConsoleUI::printError("Failed to write products backup: " + filename);
        return;
    }

    for (int sec = 0; sec < engine.localWarehouse.getSectionCount(); ++sec) 
    {
        const Inventory& section = engine.localWarehouse.getSection(sec);
        for (int slot = 0; slot < section.getCapacity(); ++slot) 
        {
            Product* p = section.getProduct(slot);
            if (p == nullptr) continue;

            FragileElectronics* frag = dynamic_cast<FragileElectronics*>(p);
            ElectronicProduct* elec = dynamic_cast<ElectronicProduct*>(p);
            PerishableGrocery* perish = dynamic_cast<PerishableGrocery*>(p);
            NonPerishable* nonperish = dynamic_cast<NonPerishable*>(p);
            ClothingProduct* cloth = dynamic_cast<ClothingProduct*>(p);

            if (frag != nullptr) 
            {
                file << "FRAG," << p->getID() << "," << p->getName() << "," << p->getBasePrice() << ","
                     << p->getQuantity() << "," << p->getSupplier() << "," << elec->getWarrantyMonths() << ","
                     << elec->getBrandName() << "," << frag->getFragilityRating() << "," << frag->getPackagingType() << "\n";
            } 
            else if (elec != nullptr) 
            {
                file << "ELEC," << p->getID() << "," << p->getName() << "," << p->getBasePrice() << ","
                     << p->getQuantity() << "," << p->getSupplier() << "," << elec->getWarrantyMonths() << ","
                     << elec->getBrandName() << "," << elec->getVoltage() << "\n";
            } 
            else if (perish != nullptr) 
            {
                file << "PERI," << p->getID() << "," << p->getName() << "," << p->getBasePrice() << ","
                     << p->getQuantity() << "," << p->getSupplier() << "," << (perish->getIsRefrigerated() ? 1 : 0) << ","
                     << perish->getFoodCategory() << "," << perish->getExpiryDate().toString() << ","
                     << perish->getStorageTempRequired() << "\n";
            } 
            else if (nonperish != nullptr) 
            {
                file << "NPER," << p->getID() << "," << p->getName() << "," << p->getBasePrice() << ","
                     << p->getQuantity() << "," << p->getSupplier() << "," << (nonperish->getIsRefrigerated() ? 1 : 0) << ","
                     << nonperish->getFoodCategory() << "," << nonperish->getShelfLifeMonths() << ","
                     << nonperish->getPreservativeLevel() << "\n";
            } 
            else if (cloth != nullptr) 
            {
                file << "CLOT," << p->getID() << "," << p->getName() << "," << p->getBasePrice() << ","
                     << p->getQuantity() << "," << p->getSupplier() << "," << cloth->getSize() << ","
                     << cloth->getMaterial() << "," << cloth->getTargetSeason() << "\n";
            }
        }
    }
}
