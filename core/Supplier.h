#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>

class Supplier {
private:
    std::string supplierID;
    std::string companyName;
    double performanceScore;
    std::string contractTerms; // Added to match rubric spec

public:
    Supplier() : supplierID(""), companyName(""), performanceScore(100.0), contractTerms("Net 30") {}
    Supplier(std::string id, std::string name, std::string terms = "Net 30");

    void logRestockOrder(std::string itemName, int qty, double transactionCost);
    void orderRestock(std::string itemName, int qty, double transactionCost); // Added to match rubric spec
    void generateInvoice(double billAmount) const;
    
    std::string getID() const;
    std::string getName() const;
    double getPerformanceScore() const;
    std::string getContractTerms() const;
};

#endif