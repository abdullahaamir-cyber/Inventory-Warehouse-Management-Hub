#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
class WarehouseManager; 

class FileHandler 
{
public:
    
    static void loadSuppliers(WarehouseManager& engine, const std::string& filename);
    static void saveSuppliers(const WarehouseManager& engine, const std::string& filename);
    
    static void loadProducts(WarehouseManager& engine, const std::string& filename);
    static void saveProducts(const WarehouseManager& engine, const std::string& filename);
};

#endif