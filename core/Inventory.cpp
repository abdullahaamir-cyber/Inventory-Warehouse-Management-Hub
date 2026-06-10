#include"Inventory.h"
#include<stdexpect>
#include<iostream>
using namespace std;

Inventory::Inventory(string type, int maxCapacity){
    sectionType=type;
    capacity=maxCapacity;
    slots=new Product*[capacity];
    for(int i=0;i<capacity;i++)
        slots[i]=nullptr;
}
Inventory::~Inventory(){
    for(int i=0;i<capacity;i++)
        delete slots[i];
    delete[] slots;
}
Inventory::Inventory(const Inventory& other){
    sectionType=other.sectionType;
    capacity=other.capacity;
    slots=new Product*[capacity];
    for(int i=0;i<capacity;i++)
        slots[i]=other.slots[i]?other.slots[i]->clone():nullptr;
}
Inventory& Inventory::operator=(const Inventory& other) {
    if(this==&other)
         return*this;
    for(int i=0;i<capacity;i++)
        delete slots[i];
    delete[] slots;
    sectionType=other.sectionType;
    capacity=other.capacity;
    slots=new Product*[capacity];
    for(int i=0;i<capacity;i++)
        slots[i]=other.slots[i]?other.slots[i]->clone():nullptr;
    return *this;
}
bool Inventory::addStockToSlot(Product* p)
 {
    for(int i=0;i<capacity;i++)
     {
        if (slots[i]==nullptr)
         {
            slots[i] = p;
            return true;
        }
    }
    return false;
}
bool Inventory::removeStockFromSlot(int index) {
    if (index<0||index>=capacity||slots[index] ==nullptr)
        return false;
    delete slots[index];
    slots[index]=nullptr;
    return true;
}
Product& Inventory::operator[](int index) const {
    if (index<0||index>=capacity||slots[index]==nullptr)
        throw std::runtime_error("Slot is empty or index out of range.");
    return *slots[index];
}
Product& Inventory::operator[](int index) {
    if (index<0||index>=capacity||slots[index]==nullptr)
        throw std::runtime_error("Slot is empty or index out of range.");
    return *slots[index];

}
void Inventory::sortByID() {
    for(int i=0;i<capacity-1;i++)
    {
        for(int j=0;j<capacity-i-1;j++) 
        {
            if(slots[j]==nullptr && slots[j+1]!=nullptr)
             {
                Product* temp=slots[j];
                slots[j]=slots[j+1];
                slots[j+1]=temp;
            } 
            else if(slots[j]!=nullptr && slots[j+1]!=nullptr)
             {
                if (slots[j]->getID()>slots[j+1]->getID())
                 {
                    Product* temp=slots[j];
                    slots[j]=slots[j+1];
                    slots[j+1]=temp;
                }
            }
        }
    }
}
string Inventory::getSectionType()const 
{ 
    return sectionType;
}
int Inventory::getCapacity()const 
{
     return capacity; 
    }