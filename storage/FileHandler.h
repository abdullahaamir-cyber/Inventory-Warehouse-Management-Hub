#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include "../engine/WarehouseManager.h"

// Utility class for database CSV backup operations
class FileHandler {
public:
    // Supplier data serialization
    static void loadSuppliers(WarehouseManager& engine, const std::string& filename);
    static void saveSuppliers(const WarehouseManager& engine, const std::string& filename);
    
    // Product data serialization
    static void loadProducts(WarehouseManager& engine, const std::string& filename);
    static void saveProducts(const WarehouseManager& engine, const std::string& filename);
};

#endif