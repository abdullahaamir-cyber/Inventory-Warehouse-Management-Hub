#include "Supplier.h"
#include "ConsoleUI.h"

using namespace std;

Supplier::Supplier(string id, string name, string terms) 
{
    supplierID = id;
    companyName = name;
    performanceScore = 100.0;
    contractTerms = terms;
}

void Supplier::logRestockOrder(string itemName, int qty, double transactionCost) 
{
    ConsoleUI::printSuccess("Supplier " + companyName + " restocked " + to_string(qty) + "x " + itemName 
         + " | Cost: $" + ConsoleUI::formatDouble(transactionCost));
    performanceScore += 1.0;
}

void Supplier::orderRestock(string itemName, int qty, double transactionCost) 
{
    ConsoleUI::printInfo("Requesting " + to_string(qty) + "x " + itemName + " from " + companyName 
         + " | Expected Cost: $" + ConsoleUI::formatDouble(transactionCost));
    logRestockOrder(itemName, qty, transactionCost);
}

void Supplier::generateInvoice(double billAmount) const 
{
    ConsoleUI::printHeader("Supplier Invoice Detail");
    ConsoleUI::printLabelValue("Supplier ID / Name", companyName + " [" + supplierID + "]");
    ConsoleUI::printLabelValue("Terms of Contract", contractTerms);
    ConsoleUI::printLabelValue("Grand Invoice Total", "$" + ConsoleUI::formatDouble(billAmount));
    ConsoleUI::printDivider();
}

string Supplier::getID() const 
{
    return supplierID;
}

string Supplier::getName() const 
{ 
    return companyName;
}

double Supplier::getPerformanceScore() const 
{
    return performanceScore;
}

string Supplier::getContractTerms() const 
{
    return contractTerms;
}