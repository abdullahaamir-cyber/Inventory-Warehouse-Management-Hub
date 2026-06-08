#ifndef WAREHOUSE_MANAGER_H
#define WAREHOUSE_MANAGER_H

#include <string>
#include "../core/DynamicArray.h"
#include "../core/Warehouse.h"
#include "../core/Supplier.h"
#include "../core/TransactionLog.h"
#include "../modules/Product.h"
#include "../core/Date.h"

// Struct for the 2-step order dispatch process
struct StagedManifest {
    bool isActive = false;
    Product* productRef = nullptr;
    int quantityRequested = 0;
    std::string deliveryAddress;
};

class WarehouseManager {
    friend class FileHandler;
private:
    Warehouse localWarehouse;
    DynamicArray<Supplier> systemSuppliers;
    
    // Templated logs
    TransactionLog<Product*> productLog;
    TransactionLog<Supplier> supplierLog;
    
    StagedManifest pendingDispatch;
    Date currentSystemDate; // Custom date system managed by the admin/user

public:
    WarehouseManager();
    ~WarehouseManager();

    
    void loadSystemData();
    void saveSystemData();

    
    void runMainMenu();

    void viewRegisteredSuppliers() const;  
    void registerNewSupplier();
    void removeSupplier(); // Added to match expanded supplier requirements
    void processIncomingShipment();

    void viewWarehouseLayout() const;
    void inspectSpecificSlot();
    void transferStock();

    
    void viewGlobalInventoryStats() const; // Added for top-level inventory statistics
    void runGlobalExpiryAudit();
    void runRiskAssessment();
    void executeSeasonalClearance();
    void changeSystemDate(); // Added to allow admin to alter simulated current date

    
    void createDispatchOrder(); 
    void viewPendingManifests();
    
    
    void printSupplierHistory() const;     
    void printProductHistory() const;      
    void clearHistoricalLogs();            
};

#endif