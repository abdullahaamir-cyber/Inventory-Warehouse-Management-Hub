#include"Supplier.h"
#include<iostream>
using namespace std;

Supplier::Supplier(string id,string name,string terms){
    supplierID=id;
    companyName=name;
    performanceScore=100.0;
    contractTerms=terms;
}
void Supplier::logRestockOrder(string itemName,int qty,double transactionCost){
    cout<<"[LOG] Supplier "<<companyName<<" restocked "<<qty<<"x "<<itemName<<" | Cost: $"<<transactionCost<<endl;
    performanceScore+=1.0;
}
void Supplier::orderRestock(string itemName,int qty,double transactionCost){
    cout<<"[ORDER] Requesting "<<qty<<"x "<<itemName<<" from "<<companyName<<" | Expected Cost: $"<<transactionCost<<endl;
    logRestockOrder(itemName, qty,transactionCost)
}
void Supplier::generateInvoice(double billAmount)const{
    cout<<"=== INVOICE ===";<<endl
    cout<<"Supplier: "<<companyName<<" (ID: "<<supplierID<<")"<<endl;
    cout<<"Terms: "<<contractTerms<<endl;
    cout<<"Amount Due: $"<<billAmount<<endl;
}
string Supplier::getID()const{
     return supplierID;
     }
string Supplier::getName()const
{ return companyName;
 }
double Supplier::getPerformanceScore()const{
     return performanceScore;
     }
string Supplier::getContractTerms()const
{
     return contractTerms;
     }