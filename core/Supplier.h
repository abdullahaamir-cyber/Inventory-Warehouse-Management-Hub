#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>

// Partner supplying products to the warehouse
class Supplier {
    friend class FileHandler;
private:
    std::string supplierID;
    std::string companyName;
    double performanceScore;
    std::string contractTerms;

public:
    Supplier() : supplierID(""), companyName(""), performanceScore(100.0), contractTerms("Net 30") {}
    Supplier(std::string id, std::string name, std::string terms = "Net 30");

    // Order/intake logging
    void logRestockOrder(std::string itemName, int qty, double transactionCost);
    void orderRestock(std::string itemName, int qty, double transactionCost);
    void generateInvoice(double billAmount) const;
    
    // Getters
    std::string getID() const;
    std::string getName() const;
    double getPerformanceScore() const;
    std::string getContractTerms() const;
};

#endif