#include "WarehouseManager.h"
#include "../core/ConsoleUI.h"
#include "../storage/FileHandler.h"
#include "../modules/ElectronicProduct.h"
#include "../modules/FragileElectronics.h"
#include "../modules/GroceryProduct.h"
#include "../modules/PerishableGrocery.h"
#include "../modules/NonPerishable.h"
#include "../modules/ClothingProduct.h"
#include <iostream>
#include <iomanip>

using namespace std;

extern Date currentSystemDate;

WarehouseManager::WarehouseManager() 
{
    // Initialize system to default simulated date: 2026-06-09
    currentSystemDate = Date(9, 6, 2026);
    ::currentSystemDate = currentSystemDate;
    
    // Set pending order dispatch to inactive
    pendingDispatch.isActive = false;
    pendingDispatch.productRef = nullptr;
    pendingDispatch.quantityRequested = 0;
    pendingDispatch.deliveryAddress = "";
}

WarehouseManager::~WarehouseManager() 
{
    // Destructor of warehouse sections will cascade and clean up all slot product pointers
}

void WarehouseManager::loadSystemData() 
{
    FileHandler::loadSuppliers(*this, "data_files/suppliers.txt");
    FileHandler::loadProducts(*this, "data_files/products.txt");
}

void WarehouseManager::saveSystemData() 
{
    FileHandler::saveSuppliers(*this, "data_files/suppliers.txt");
    FileHandler::saveProducts(*this, "data_files/products.txt");
}

void WarehouseManager::runMainMenu() 
{
    bool running = true;
    while (running) 
    {
        DynamicArray<string> mainOptions;
        mainOptions.push_back("Supplier Management Menu");
        mainOptions.push_back("Warehouse Grid Layout & Shelf Management");
        mainOptions.push_back("Inventory Operations & Expiry Auditing");
        mainOptions.push_back("Order Dispatching & Cargo Manifests");
        mainOptions.push_back("System History & Transaction Audit Logs");
        mainOptions.push_back("Save & Shutdown Application");

        int choice = ConsoleUI::showMenu("Main Dashboard Control", mainOptions);
        switch (choice) 
        {
            case 1: 
            {
                bool sub = true;
                while (sub) 
                {
                    DynamicArray<string> opts;
                    opts.push_back("View Registered Suppliers");
                    opts.push_back("Register New Supplier Company");
                    opts.push_back("Remove/Deregister Supplier");
                    opts.push_back("Process Supplier Restock Intake");
                    opts.push_back("Back to Main Dashboard");

                    int subChoice = ConsoleUI::showMenu("Supplier Operations Menu", opts);
                    
                    if (subChoice == 1) viewRegisteredSuppliers();
                    else if (subChoice == 2) registerNewSupplier();
                    else if (subChoice == 3) removeSupplier();
                    else if (subChoice == 4) processIncomingShipment();
                    else sub = false;
                }
                break;
            }
            case 2: 
            {
                bool sub = true;
                while (sub) 
                {
                    DynamicArray<string> opts;
                    opts.push_back("Show Warehouse Map Visualizer");
                    opts.push_back("Inspect Shelf Slot & Product Details");
                    opts.push_back("Transfer Stock Between Grid Locations");
                    opts.push_back("Back to Main Dashboard");
                    int subChoice = ConsoleUI::showMenu("Warehouse Layout & Shelf Management", opts);
                    
                    if (subChoice == 1) viewWarehouseLayout();
                    else if (subChoice == 2) inspectSpecificSlot();
                    else if (subChoice == 3) transferStock();
                    else sub = false;
                }
                break;
            }
            case 3: 
            {
                bool sub = true;
                while (sub) 
                {
                    DynamicArray<string> opts;
                    opts.push_back("Display Global Financial Stats");
                    opts.push_back("Run Grocery Expiry Date Audit");
                    opts.push_back("Run Electronics Fragility Risk Assessment");
                    opts.push_back("Apply Clearance Sale Batch Discounts");
                    opts.push_back("Change Simulated System Date");
                    opts.push_back("Back to Main Dashboard");
                    
                    int subChoice = ConsoleUI::showMenu("Inventory Operations Menu", opts);
                    
                    if (subChoice == 1) viewGlobalInventoryStats();
                    else if (subChoice == 2) runGlobalExpiryAudit();
                    else if (subChoice == 3) runRiskAssessment();
                    else if (subChoice == 4) executeSeasonalClearance();
                    else if (subChoice == 5) changeSystemDate();
                    else sub = false;
                }
                break;
            }
            case 4: 
            {
                bool sub = true;
                while (sub) 
                {
                    DynamicArray<string> opts;
                    opts.push_back("Create Staged Dispatch Order");
                    opts.push_back("View Pending Shipment Manifest & Confirm");
                    opts.push_back("Back to Main Dashboard");
                    int subChoice = ConsoleUI::showMenu("Order Dispatch & Manifest Management", opts);
                    
                    if (subChoice == 1) createDispatchOrder();
                    else if (subChoice == 2) viewPendingManifests();
                    else sub = false;
                }
                break;
            }
            case 5: 
            {
                bool sub = true;
                while (sub) 
                {
                    DynamicArray<string> opts;
                    opts.push_back("Print Supplier Historical Audit Logs");
                    opts.push_back("Print Product Movement Audit Logs");
                    opts.push_back("Wipe System Transaction History logs");
                    opts.push_back("Back to Main Dashboard");
                    int subChoice = ConsoleUI::showMenu("System History & Logs audit", opts);
                    
                    if (subChoice == 1) printSupplierHistory();
                    else if (subChoice == 2) printProductHistory();
                    else if (subChoice == 3) clearHistoricalLogs();
                    else sub = false;
                }
                break;
            }
            case 6:
                running = false;
                break;
            default:
                break;
        }
    }
}

void WarehouseManager::viewRegisteredSuppliers() const 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Registered Suppliers list");
    
    if (systemSuppliers.empty()) 
    {
        ConsoleUI::printInfo("No suppliers registered in system database.");
        ConsoleUI::pause();
        return;
    }

    DynamicArray<string> headers;
    headers.push_back("Supplier ID");
    headers.push_back("Company Name");
    headers.push_back("Performance Score");
    headers.push_back("Contract Terms");

    DynamicArray<int> widths;
    widths.push_back(15);
    widths.push_back(30);
    widths.push_back(20);
    widths.push_back(20);

    DynamicArray<DynamicArray<string>> rows;
    for (int i = 0; i < systemSuppliers.size(); ++i) 
    {
        DynamicArray<string> row;
        row.push_back(systemSuppliers[i].getID());
        row.push_back(systemSuppliers[i].getName());
        row.push_back(ConsoleUI::formatDouble(systemSuppliers[i].getPerformanceScore()));
        row.push_back(systemSuppliers[i].getContractTerms());
        rows.push_back(row);
    }

    ConsoleUI::printTable(headers, widths, rows);
    ConsoleUI::pause();
}

void WarehouseManager::registerNewSupplier() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Register Supplier Company");

    string id = ConsoleUI::promptString("Enter Supplier ID (unique string tag)", true);
    
    // Check uniqueness
    for (int i = 0; i < systemSuppliers.size(); ++i) 
    {
        if (systemSuppliers[i].getID() == id) 
        {
            ConsoleUI::printError("Deregistration Failed: A supplier with this ID is already registered.");
            ConsoleUI::pause();
            return;
        }
    }

    string name = ConsoleUI::promptString("Enter Supplier Company Name", true);
    string terms = ConsoleUI::promptString("Enter Payment Terms (e.g. Net 30, COD)", true);

    Supplier newSupplier(id, name, terms);
    systemSuppliers.push_back(newSupplier);

    // Record action in audit log
    string timestamp = currentSystemDate.toString();
    supplierLog.recordAction(timestamp, "REGISTERED SUPPLIER: " + name + " [" + id + "]", newSupplier);

    ConsoleUI::printSuccess("Supplier '" + name + "' registered successfully.");
    ConsoleUI::pause();
}

void WarehouseManager::removeSupplier() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Deregister Supplier");

    if (systemSuppliers.empty()) 
    {
        ConsoleUI::printInfo("No suppliers registered to remove.");
        ConsoleUI::pause();
        return;
    }

    string id = ConsoleUI::promptString("Enter ID of Supplier to remove", true);
    int targetIdx = -1;
    for (int i = 0; i < systemSuppliers.size(); ++i) 
    {
        if (systemSuppliers[i].getID() == id) 
        {
            targetIdx = i;
            break;
        }
    }

    if (targetIdx == -1) 
    {
        ConsoleUI::printError("Supplier not found in database registry.");
        ConsoleUI::pause();
        return;
    }

    string sName = systemSuppliers[targetIdx].getName();
    Supplier removedSupplier = systemSuppliers[targetIdx];
    systemSuppliers.erase(targetIdx);

    string timestamp = currentSystemDate.toString();
    supplierLog.recordAction(timestamp, "REMOVED SUPPLIER: " + sName + " [" + id + "]", removedSupplier);

    ConsoleUI::printSuccess("Supplier '" + sName + "' removed from registry.");
    ConsoleUI::pause();
}

void WarehouseManager::processIncomingShipment() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Process Purchase Intake");

    if (systemSuppliers.empty()) 
    {
        ConsoleUI::printError("Process Failed: You must register at least one Supplier first.");
        ConsoleUI::pause();
        return;
    }

    // Select Supplier
    DynamicArray<string> suppOpts;
    for (int i = 0; i < systemSuppliers.size(); ++i) 
    {
        suppOpts.push_back(systemSuppliers[i].getName() + " [" + systemSuppliers[i].getID() + "]");
    }
    suppOpts.push_back("Cancel Intake Process");

    int suppIdx = ConsoleUI::showMenu("Select Supplier for Shipment Intake", suppOpts) - 1;
    if (suppIdx < 0 || suppIdx >= (int)systemSuppliers.size()) return;

    Supplier& supplierRef = systemSuppliers[suppIdx];

    // Select Product Category Branch
    DynamicArray<string> catOpts;
    catOpts.push_back("Electronic Hardware");
    catOpts.push_back("Fragile Electronics Cargo");
    catOpts.push_back("Perishable Grocery Product");
    catOpts.push_back("Non-Perishable Grocery Product");
    catOpts.push_back("Clothing / Apparel Merchandise");
    catOpts.push_back("Cancel Intake");

    int catIdx = ConsoleUI::showMenu("Select Product Classification", catOpts);
    if (catIdx == 6) return;

    // Prompt for standard parameters
    string pID = ConsoleUI::promptString("Enter Product ID Tag (must be unique)", true);
    
    // Check if Product ID already exists anywhere in local warehouse
    for (int sec = 0; sec < localWarehouse.sections.size(); ++sec) 
    {
        for (int slot = 0; slot < localWarehouse.sections[sec].getCapacity(); ++slot) 
        {
            Product* existing = localWarehouse.sections[sec].slots[slot];
            if (existing != nullptr && existing->getID() == pID) 
            {
                ConsoleUI::printError("Intake Failed: Product ID tag '" + pID + "' is already in use on shelf grid.");
                ConsoleUI::pause();
                return;
            }
        }
    }

    string pName = ConsoleUI::promptString("Enter Product Title Name", true);
    double pPrice = ConsoleUI::promptDouble("Enter Wholesale Base Price", 0.01);
    int pQty = ConsoleUI::promptInt("Enter Intake Carton Quantity", 1, 10000);

    Product* newProduct = nullptr;

    if (catIdx == 1) 
    {
        // Electronic Hardware
        int warranty = ConsoleUI::promptInt("Enter Warranty Period (Months)", 1, 120);
        string brand = ConsoleUI::promptString("Enter Brand Name", true);
        int voltage = ConsoleUI::promptInt("Enter Rated Operating Voltage (Volts)", 5, 480);
        newProduct = new ElectronicProduct(pID, pName, pPrice, pQty, supplierRef.getID(), warranty, brand.c_str(), voltage);
    } 
    else if (catIdx == 2) 
    {
        // Fragile Electronics Cargo
        int warranty = ConsoleUI::promptInt("Enter Warranty Period (Months)", 1, 120);
        string brand = ConsoleUI::promptString("Enter Brand Name", true);
        int fragility = ConsoleUI::promptInt("Enter Fragility Level Scale (1-10)", 1, 10);
        string packaging = ConsoleUI::promptString("Enter Packaging Cushion Material (e.g. Foam, Bubble)", true);
        newProduct = new FragileElectronics(pID, pName, pPrice, pQty, supplierRef.getID(), warranty, brand.c_str(), fragility, packaging);
    } 
    else if (catIdx == 3) 
    {
        // Perishable Grocery Product
        bool isRefrig = ConsoleUI::promptConfirm("Is this product refrigerated");
        string foodCat = ConsoleUI::promptString("Enter Food Category (e.g. Dairy, Meat, Produce)", true);
        string dateStr = ConsoleUI::promptString("Enter Expiration Date (YYYY-MM-DD)", true);
        double reqTemp = ConsoleUI::promptDouble("Enter Storage Temp (°C)", -50.0);
        
        Date expiry = Date::parseString(dateStr);
        newProduct = new PerishableGrocery(pID, pName, pPrice, pQty, supplierRef.getID(), isRefrig, foodCat, expiry, reqTemp);
    } 
    else if (catIdx == 4) 
    {
        // Non-Perishable Grocery Product
        bool isRefrig = ConsoleUI::promptConfirm("Is this product refrigerated");
        string foodCat = ConsoleUI::promptString("Enter Food Category (e.g. Canned, Dry, Spices)", true);
        int shelfLife = ConsoleUI::promptInt("Enter Shelf Life expectation (Months)", 1, 240);
        string preservatives = ConsoleUI::promptString("Enter Preservative Category (e.g. Organic, Sodium)", true);
        newProduct = new NonPerishable(pID, pName, pPrice, pQty, supplierRef.getID(), isRefrig, foodCat, shelfLife, preservatives);
    } 
    else if (catIdx == 5) 
    {
        // Clothing / Apparel Merchandise
        string sizeStr = ConsoleUI::promptString("Enter Clothing Size Label (e.g. S, M, L, XL)", true);
        string materialStr = ConsoleUI::promptString("Enter Fabric Material Composition", true);
        string seasonStr = ConsoleUI::promptString("Enter Selling Season (e.g. Winter, Summer)", true);
        newProduct = new ClothingProduct(pID, pName, pPrice, pQty, supplierRef.getID(), sizeStr, materialStr, seasonStr);
    }

    if (newProduct == nullptr) return;

    // Try routing item to warehouse grid section dynamically
    if (localWarehouse.routeIncomingStock(newProduct)) 
    {
        double totalCost = pPrice * pQty;
        supplierRef.orderRestock(pName, pQty, totalCost);
        supplierRef.generateInvoice(totalCost);

        // Record logs
        productLog.recordAction(currentSystemDate.toString(), "INTAKE: Routed ID " + pID + " (" + pName + ") Qty: " + to_string(pQty) + " to Section", newProduct);
        ConsoleUI::printSuccess("Stock routed to shelf section and logged successfully.");
    } 
    else 
    {
        ConsoleUI::printError("Routing Failed: No eligible section with empty slots found.");
        delete newProduct; // Prevent memory leak since routing was unsuccessful
    }
    
    ConsoleUI::pause();
}

void WarehouseManager::viewWarehouseLayout() const 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Warehouse 2D Top-View Grid Map");

    cout << "\nFacility ID: " << localWarehouse.locationID << " | Storage Space: " << localWarehouse.totalSquareFootage << " sq. ft.\n";
    ConsoleUI::printDivider();

    for (int sec = 0; sec < localWarehouse.sections.size(); ++sec) 
    {
        const Inventory& section = localWarehouse.sections[sec];
        string type = section.getSectionType();
        
        // Convert category type to uppercase for styling
        for (auto &c : type) c = toupper(c);

        cout << "  [AISLE " << sec << ": " << type << "]\n";
        
        // Render Top of the Storage Shelf Boxes
        cout << "    RACK: ";
        for (int slot = 0; slot < section.getCapacity(); ++slot) 
        {
            cout << "┌───────┐ ";
        }
        cout << "\n          ";

        // Render Shelf Box Content containing Product SKU ID or empty space
        for (int slot = 0; slot < section.getCapacity(); ++slot) 
        {
            Product* p = section.slots[slot];
            if (p == nullptr) 
            {
                cout << "│  ---  │ ";
            } 
            else 
            {
                string itemID = p->getID();
                if (itemID.length() > 5) {
                    itemID = itemID.substr(0, 5);
                } else if (itemID.length() < 5) {
                    itemID.append(5 - itemID.length(), ' ');
                }
                cout << "│ " << itemID << " │ ";
            }
        }
        cout << "\n          ";

        // Render Bottom of the Storage Shelf Boxes
        for (int slot = 0; slot < section.getCapacity(); ++slot) 
        {
            cout << "└───────┘ ";
        }
        cout << "\n\n";
    }

    ConsoleUI::printDivider();
    cout << "LEGEND: [  ---  ] = Empty Shelf Space | [IDTag] = Occupied Shelf Slot with Product SKU\n";
    ConsoleUI::printDivider();
    ConsoleUI::pause();
}

void WarehouseManager::inspectSpecificSlot() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Inspect Shelf slot");

    int maxSecs = localWarehouse.sections.size();
    if (maxSecs == 0) 
    {
        ConsoleUI::printInfo("No warehouse sections initialized.");
        ConsoleUI::pause();
        return;
    }

    int secIdx = ConsoleUI::promptInt("Enter Section Index", 0, maxSecs - 1);
    Inventory& sec = localWarehouse.sections[secIdx];

    int maxSlots = sec.getCapacity();
    int slotIdx = ConsoleUI::promptInt("Enter Shelf Slot Index", 0, maxSlots - 1);

    Product* prod = sec.slots[slotIdx];
    if (prod == nullptr) 
    {
        ConsoleUI::printInfo("Slot is currently [ EMPTY ]");
        ConsoleUI::pause();
        return;
    }

    // Header card
    ConsoleUI::printLabelValue("Product Type", sec.getSectionType());
    prod->displayStatus();

    // Run dynamic casts to perform polymorphic actions specific to categories
    ElectronicProduct* elec = dynamic_cast<ElectronicProduct*>(prod);
    if (elec != nullptr) 
    {
        elec->testHardware();
        FragileElectronics* frag = dynamic_cast<FragileElectronics*>(prod);
        if (frag != nullptr) 
        {
            double r = frag->calculateShippingRisk();
            ConsoleUI::printLabelValue("Fragility Index Value", to_string(frag->getFragilityRating()) + "/10");
            ConsoleUI::printLabelValue("Calculated Shipping Risk factor", ConsoleUI::formatDouble(r * 100) + "%");
        }
    }

    GroceryProduct* groc = dynamic_cast<GroceryProduct*>(prod);
    if (groc != nullptr) 
    {
        groc->checkSafety();
        PerishableGrocery* perish = dynamic_cast<PerishableGrocery*>(prod);
        if (perish != nullptr) 
        {
            perish->checkExpiry();
            // Compare dates
            if (perish->getExpiryDate() < currentSystemDate) 
            {
                ConsoleUI::printError("EXPIRED CARGO ALERT: Dispose of expired grocery stock immediately!");
            }
        }
        NonPerishable* nonPerish = dynamic_cast<NonPerishable*>(prod);
        if (nonPerish != nullptr) 
        {
            cout << "Storage Instructions: " << nonPerish->getStorageInstructions() << endl;
        }
    }

    ClothingProduct* cloth = dynamic_cast<ClothingProduct*>(prod);
    if (cloth != nullptr) 
    {
        cloth->fitGuide();
    }

    ConsoleUI::pause();
}

void WarehouseManager::transferStock() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Transfer Stock Pointer");

    int maxSecs = localWarehouse.sections.size();
    if (maxSecs == 0) return;

    ConsoleUI::printInfo("Source shelf location:");
    int srcSec = ConsoleUI::promptInt("Enter Source Section Index", 0, maxSecs - 1);
    int srcSlot = ConsoleUI::promptInt("Enter Source Slot", 0, localWarehouse.sections[srcSec].getCapacity() - 1);

    Product* pSrc = localWarehouse.sections[srcSec].slots[srcSlot];
    if (pSrc == nullptr) 
    {
        ConsoleUI::printError("Transfer aborted: Source slot is empty.");
        ConsoleUI::pause();
        return;
    }

    ConsoleUI::printInfo("Destination shelf location:");
    int destSec = ConsoleUI::promptInt("Enter Destination Section Index", 0, maxSecs - 1);
    int destSlot = ConsoleUI::promptInt("Enter Destination Slot", 0, localWarehouse.sections[destSec].getCapacity() - 1);

    // Swap pointers
    Product* pTemp = localWarehouse.sections[destSec].slots[destSlot];
    localWarehouse.sections[destSec].slots[destSlot] = pSrc;
    localWarehouse.sections[srcSec].slots[srcSlot] = pTemp;

    // Log movement in transaction trail
    string action = "MOVED: " + pSrc->getName() + " [" + pSrc->getID() + "] from Sec " + to_string(srcSec) + "[" + to_string(srcSlot) + "] to Sec " + to_string(destSec) + "[" + to_string(destSlot) + "]";
    productLog.recordAction(currentSystemDate.toString(), action, pSrc);

    ConsoleUI::printSuccess("Stock pointer relocated successfully.");
    ConsoleUI::pause();
}

void WarehouseManager::viewGlobalInventoryStats() const 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Global Inventory Statistics");

    int totalOccupied = 0;
    int totalCapacity = 0;
    double cumulativeVal = 0.0;
    int elecCount = 0;
    int grocCount = 0;
    int clothCount = 0;

    for (int sec = 0; sec < localWarehouse.sections.size(); ++sec) 
    {
        const Inventory& currentSec = localWarehouse.sections[sec];
        totalCapacity += currentSec.getCapacity();
        for (int slot = 0; slot < currentSec.getCapacity(); ++slot) 
        {
            Product* p = currentSec.slots[slot];
            if (p != nullptr) 
            {
                totalOccupied++;
                cumulativeVal += p->calculateValue();

                if (dynamic_cast<ElectronicProduct*>(p) != nullptr) elecCount++;
                else if (dynamic_cast<GroceryProduct*>(p) != nullptr) grocCount++;
                else if (dynamic_cast<ClothingProduct*>(p) != nullptr) clothCount++;
            }
        }
    }

    double fillPercentage = 0.0;
    if (totalCapacity > 0) 
    {
        fillPercentage = ((double)totalOccupied / totalCapacity) * 100.0;
    }

    ConsoleUI::printLabelValue("Current System Simulated Date", currentSystemDate.toString());
    ConsoleUI::printDivider();
    ConsoleUI::printLabelValue("Total Capacity Slots in Warehouse", to_string(totalCapacity));
    ConsoleUI::printLabelValue("Total Shelves Occupied Slots", to_string(totalOccupied) + " (" + ConsoleUI::formatDouble(fillPercentage) + "% Filled)");
    ConsoleUI::printLabelValue("Total Combined Asset Financial Worth", "$" + ConsoleUI::formatDouble(cumulativeVal));
    ConsoleUI::printDivider();
    ConsoleUI::printLabelValue("Electronic Hardware Products on Shelves", to_string(elecCount));
    ConsoleUI::printLabelValue("Grocery Food Stock items on Shelves", to_string(grocCount));
    ConsoleUI::printLabelValue("Apparel / Garments items on Shelves", to_string(clothCount));
    ConsoleUI::pause();
}

void WarehouseManager::runGlobalExpiryAudit() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Grocery Expiry Date Audit Trail");

    DynamicArray<string> headers;
    headers.push_back("Product ID");
    headers.push_back("Food Name");
    headers.push_back("Refrigerated");
    headers.push_back("Expiry Date");
    headers.push_back("Expiry Status");

    DynamicArray<int> widths;
    widths.push_back(12);
    widths.push_back(25);
    widths.push_back(15);
    widths.push_back(15);
    widths.push_back(20);

    DynamicArray<DynamicArray<string>> rows;

    for (int sec = 0; sec < localWarehouse.sections.size(); ++sec) 
    {
        Inventory& currentSec = localWarehouse.sections[sec];
        for (int slot = 0; slot < currentSec.getCapacity(); ++slot) 
        {
            Product* p = currentSec.slots[slot];
            if (p != nullptr) 
            {
                PerishableGrocery* perish = dynamic_cast<PerishableGrocery*>(p);
                if (perish != nullptr) 
                {
                    DynamicArray<string> row;
                    row.push_back(perish->getID());
                    row.push_back(perish->getName());
                    row.push_back(perish->getIsRefrigerated() ? "YES" : "NO");
                    
                    Date exp = perish->getExpiryDate();
                    row.push_back(exp.toString());

                    // Calculate date difference
                    if (exp < currentSystemDate) 
                    {
                        row.push_back("[EXPIRED]");
                    } 
                    else if (exp == currentSystemDate) 
                    {
                        row.push_back("[EXPIRES TODAY]");
                    } 
                    else 
                    {
                        row.push_back("[FRESH / SAFE]");
                    }
                    rows.push_back(row);
                }
            }
        }
    }

    if (rows.empty()) 
    {
        ConsoleUI::printInfo("No perishable grocery items found in warehouse stock.");
    } 
    else 
    {
        ConsoleUI::printTable(headers, widths, rows);
    }
    
    ConsoleUI::pause();
}

void WarehouseManager::runRiskAssessment() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Electronics Fragility Risk Audit");

    DynamicArray<string> headers;
    headers.push_back("Product ID");
    headers.push_back("Hardware Name");
    headers.push_back("Voltage");
    headers.push_back("Fragility Rating");
    headers.push_back("Shipping Risk");

    DynamicArray<int> widths;
    widths.push_back(12);
    widths.push_back(25);
    widths.push_back(10);
    widths.push_back(20);
    widths.push_back(20);

    DynamicArray<DynamicArray<string>> rows;

    for (int sec = 0; sec < localWarehouse.sections.size(); ++sec) 
    {
        Inventory& currentSec = localWarehouse.sections[sec];
        for (int slot = 0; slot < currentSec.getCapacity(); ++slot) 
        {
            Product* p = currentSec.slots[slot];
            if (p != nullptr) 
            {
                FragileElectronics* frag = dynamic_cast<FragileElectronics*>(p);
                if (frag != nullptr) 
                {
                    DynamicArray<string> row;
                    row.push_back(frag->getID());
                    row.push_back(frag->getName());
                    row.push_back(to_string(frag->getVoltage()) + "V");
                    row.push_back(to_string(frag->getFragilityRating()) + "/10");
                    
                    double risk = frag->calculateShippingRisk();
                    row.push_back(ConsoleUI::formatDouble(risk * 100) + "%");
                    
                    rows.push_back(row);
                }
            }
        }
    }

    if (rows.empty()) 
    {
        ConsoleUI::printInfo("No fragile electronic products found in warehouse stock.");
    } 
    else 
    {
        ConsoleUI::printTable(headers, widths, rows);
    }
    
    ConsoleUI::pause();
}

void WarehouseManager::executeSeasonalClearance() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Seasonal Clearance Discount Menu");

    int maxSecs = localWarehouse.sections.size();
    if (maxSecs == 0) return;

    int secIdx = ConsoleUI::promptInt("Enter Target Section Index to apply Clearance sale", 0, maxSecs - 1);
    double discount = ConsoleUI::promptDouble("Enter Discount Percentage to apply (e.g. 15.0)", 0.0);

    if (discount <= 0.0 || discount > 100.0) 
    {
        ConsoleUI::printError("Clearance Discount cancelled: invalid percentage rate.");
        ConsoleUI::pause();
        return;
    }

    Inventory& sec = localWarehouse.sections[secIdx];
    int appliedCount = 0;

    for (int slot = 0; slot < sec.getCapacity(); ++slot) 
    {
        Product* p = sec.slots[slot];
        if (p != nullptr) 
        {
            p->applyDiscount(discount);
            appliedCount++;
        }
    }

    string logMsg = "CLEARANCE DISCOUNT: Applied " + ConsoleUI::formatDouble(discount) + "% discount to Section " + to_string(secIdx);
    productLog.recordAction(currentSystemDate.toString(), logMsg, nullptr);

    ConsoleUI::printSuccess("Applied clearance markdown price changes to " + to_string(appliedCount) + " products.");
    ConsoleUI::pause();
}

void WarehouseManager::changeSystemDate() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Change Simulated System Date");
    
    ConsoleUI::printLabelValue("Current System simulated date is", currentSystemDate.toString());

    int day = ConsoleUI::promptInt("Enter Simulated Calendar Day", 1, 31);
    int month = ConsoleUI::promptInt("Enter Simulated Calendar Month", 1, 12);
    int year = ConsoleUI::promptInt("Enter Simulated Calendar Year", 2026, 2035);

    currentSystemDate = Date(day, month, year);
    ::currentSystemDate = currentSystemDate;

    ConsoleUI::printSuccess("System simulated date successfully set to: " + currentSystemDate.toString());
    ConsoleUI::pause();
}

void WarehouseManager::createDispatchOrder() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Stage Order Dispatch Shipment");

    if (pendingDispatch.isActive) 
    {
        ConsoleUI::printInfo("A shipment order is already staged. View/Confirm pending manifests before creating a new one.");
        ConsoleUI::pause();
        return;
    }

    string targetID = ConsoleUI::promptString("Enter Product ID to dispatch", true);
    
    // Search for product and verify stock availability
    Product* targetProduct = nullptr;

    for (int sec = 0; sec < localWarehouse.sections.size(); ++sec) 
    {
        for (int slot = 0; slot < localWarehouse.sections[sec].getCapacity(); ++slot) 
        {
            Product* p = localWarehouse.sections[sec].slots[slot];
            if (p != nullptr && p->getID() == targetID) 
            {
                targetProduct = p;
                break;
            }
        }
        if (targetProduct != nullptr) break;
    }

    if (targetProduct == nullptr) 
    {
        ConsoleUI::printError("Dispatch Failed: Product tag ID not found on any warehouse shelf.");
        ConsoleUI::pause();
        return;
    }

    ConsoleUI::printInfo("Item Located: " + targetProduct->getName() + " (In Stock Qty: " + to_string(targetProduct->getQuantity()) + ")");
    int qty = ConsoleUI::promptInt("Enter requested dispatch quantity", 1, targetProduct->getQuantity());
    string address = ConsoleUI::promptString("Enter delivery destination shipping address", true);

    // Stage order details
    pendingDispatch.isActive = true;
    pendingDispatch.productRef = targetProduct;
    pendingDispatch.quantityRequested = qty;
    pendingDispatch.deliveryAddress = address;

    ConsoleUI::printSuccess("Dispatch order staged successfully! View manifest to finalize ship confirmation.");
    ConsoleUI::pause();
}

void WarehouseManager::viewPendingManifests() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Staged Cargo Shipment Manifest");

    if (!pendingDispatch.isActive || pendingDispatch.productRef == nullptr) 
    {
        ConsoleUI::printInfo("No shipment order is currently staged for dispatch.");
        ConsoleUI::pause();
        return;
    }

    Product* p = pendingDispatch.productRef;
    int qty = pendingDispatch.quantityRequested;
    double baseVal = p->getBasePrice();
    double totalVal = baseVal * qty;

    ConsoleUI::printLabelValue("Carrier Delivery Address", pendingDispatch.deliveryAddress);
    ConsoleUI::printLabelValue("Item ID / Name", p->getID() + " - " + p->getName());
    ConsoleUI::printLabelValue("Dispatched Unit Count", to_string(qty));
    ConsoleUI::printLabelValue("Aggregated Cargo Value", "$" + ConsoleUI::formatDouble(totalVal));

    // Dynamic warning casts
    FragileElectronics* fragile = dynamic_cast<FragileElectronics*>(p);
    if (fragile != nullptr) 
    {
        ConsoleUI::printError("CAUTION: FRAGILE ELECTRONICS CARGO - Packaging Type: " + fragile->getPackagingType());
        ConsoleUI::printLabelValue("Computed Transit Risk Rate", ConsoleUI::formatDouble(fragile->calculateShippingRisk() * 100.0) + "%");
    }

    PerishableGrocery* perish = dynamic_cast<PerishableGrocery*>(p);
    if (perish != nullptr) 
    {
        ConsoleUI::printError("REFRIGERATION REQUIRED: Maintain transport temperature at " + ConsoleUI::formatDouble(perish->getStorageTempRequired()) + "°C");
        ConsoleUI::printLabelValue("Cargo Expiration Date", perish->getExpiryDate().toString());
    }

    ConsoleUI::printDivider();
    bool confirm = ConsoleUI::promptConfirm("Confirm shipment and dispatch stock out of warehouse");
    
    if (confirm) 
    {
        // Reduce stock quantity
        p->reduceQuantity(qty);

        // Log action
        string logMsg = "DISPATCH CONFIRMED: Item ID " + p->getID() + " Qty: " + to_string(qty) + " shipped to " + pendingDispatch.deliveryAddress;
        productLog.recordAction(currentSystemDate.toString(), logMsg, p);

        // If inventory reaches 0, delete the product object and clear slot
        if (p->getQuantity() <= 0) 
        {
            // Find its slot and delete
            for (int sec = 0; sec < localWarehouse.sections.size(); ++sec) 
            {
                for (int slot = 0; slot < localWarehouse.sections[sec].getCapacity(); ++slot) 
                {
                    if (localWarehouse.sections[sec].slots[slot] == p) 
                    {
                        delete p;
                        localWarehouse.sections[sec].slots[slot] = nullptr;
                        break;
                    }
                }
            }
        }

        pendingDispatch.isActive = false;
        pendingDispatch.productRef = nullptr;

        ConsoleUI::printSuccess("Stock dispatched. Warehouse quantities and shelf slots updated.");
    } 
    else 
    {
        pendingDispatch.isActive = false;
        pendingDispatch.productRef = nullptr;
        ConsoleUI::printInfo("Shipment cancelled and staged manifest discarded.");
    }
    
    ConsoleUI::pause();
}

void WarehouseManager::printSupplierHistory() const 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Supplier Registry Logs");
    supplierLog.printAuditTrail();
    ConsoleUI::pause();
}

void WarehouseManager::printProductHistory() const 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Product Intake/Movement Transaction Logs");
    productLog.printAuditTrail();
    ConsoleUI::pause();
}

void WarehouseManager::clearHistoricalLogs() 
{
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("Wipe Audit Trails");
    bool confirm = ConsoleUI::promptConfirm("Are you sure you want to permanently clear all transaction logs");
    
    if (confirm) 
    {
        supplierLog.clearLogs();
        productLog.clearLogs();
        ConsoleUI::printSuccess("Audit trails successfully cleared from system RAM.");
    } 
    else 
    {
        ConsoleUI::printInfo("Log clear aborted.");
    }
    ConsoleUI::pause();
}
