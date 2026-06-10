#include "engine/WarehouseManager.h"
#include "core/ConsoleUI.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

using namespace std;

Date currentSystemDate(9, 6, 2026);

int main() 
{
    #ifdef _WIN32
    // Force UTF-8 Output encoding on Windows consoles to render box-drawing characters
    SetConsoleOutputCP(CP_UTF8);

    // Enable Virtual Terminal Processing for ANSI colors/screen clears
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) 
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) 
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
    #endif

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