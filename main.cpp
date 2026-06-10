#include "engine/WarehouseManager.h"
#include "core/ConsoleUI.h"
#include <iostream>

using namespace std;

Date currentSystemDate(9, 6, 2026);

int main() 
{
    // Enable ANSI console formatting
    ConsoleUI::clearScreen();
    
    // Instantiate our controller
    WarehouseManager manager;

    // Load registered suppliers and products from database files on boot
    manager.loadSystemData();

    // Launch main UI control loop
    manager.runMainMenu();

    // Auto-save database to files upon exit
    manager.saveSystemData();

    ConsoleUI::clearScreen();
    ConsoleUI::printSuccess("System shut down cleanly. All transaction logs and database changes saved.");
    
    return 0;
}