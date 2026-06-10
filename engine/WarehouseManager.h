#ifndef WAREHOUSE_MANAGER_H
#define WAREHOUSE_MANAGER_H

#include <string>
#include "../core/DynamicArray.h"
#include "../core/Warehouse.h"
#include "../core/Supplier.h"
#include "../core/TransactionLog.h"
#include "../modules/Product.h"
#include "../core/Date.h"

// Struct for staging orders before final confirmation
struct StagedManifest {
    bool isActive = false;
    Product* productRef = nullptr;
    int quantityRequested = 0;
    std::string deliveryAddress;
};

// Main controller for warehouse operations, logs, and simulated dates
class WarehouseManager {
    friend class FileHandler;
private:
    Warehouse localWarehouse;
    DynamicArray<Supplier> systemSuppliers;
    
    // Templated logs for products and suppliers
    TransactionLog<Product*> productLog;
    TransactionLog<Supplier> supplierLog;
    
    StagedManifest pendingDispatch;
    Date currentSystemDate;

public:
    WarehouseManager();
    ~WarehouseManager();

    // Data persistence
    void loadSystemData();
    void saveSystemData();

    // Main controller loop
    void runMainMenu();

    // Supplier management
    void viewRegisteredSuppliers() const;  
    void registerNewSupplier();
    void removeSupplier(); 
    void processIncomingShipment();

    // Warehouse shelf layout
    void viewWarehouseLayout() const;
    void inspectSpecificSlot();
    void transferStock();

    // Auditing and scheduling operations
    void viewGlobalInventoryStats() const;
    void runGlobalExpiryAudit();
    void runRiskAssessment();
    void executeSeasonalClearance();
    void changeSystemDate();

    // Two-step dispatch operations
    void createDispatchOrder(); 
    void viewPendingManifests();
    
    // Audit logs
    void printSupplierHistory() const;     
    void printProductHistory() const;      
    void clearHistoricalLogs();            
};

#endif