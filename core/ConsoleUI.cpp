#include "ConsoleUI.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

// ANSI Escape Codes defined via preprocessor macros
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Initialize Configurable UI Settings
int ConsoleUI::HEADER_PADDING = 6;
int ConsoleUI::DIVIDER_LENGTH = 100;
string ConsoleUI::PRIMARY_COLOR = BLUE;
string ConsoleUI::SECONDARY_COLOR = WHITE;
string ConsoleUI::SUCCESS_COLOR = GREEN;
string ConsoleUI::ERROR_COLOR = RED;
string ConsoleUI::LABEL_COLOR = YELLOW;

void ConsoleUI::clearScreen() { cout << "\033[2J\033[1;1H" << flush; }

void ConsoleUI::printDivider() 
{
    cout << SECONDARY_COLOR;
    for (int i = 0; i < DIVIDER_LENGTH; ++i) { cout << "─"; }
    cout << RESET << endl;
}

void ConsoleUI::printHeader(const string& title) 
{
    int width = DIVIDER_LENGTH;
    
    cout << endl << SECONDARY_COLOR << BOLD;
    
    // Top border
    cout << "┌";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┐" << endl;
    
    // Main Project Title 
    string mainTitle = "WAREHOUSE ENTERPRISE MANAGEMENT SYSTEM";

    // formula to center text
    int padTitle = (width - 2 - mainTitle.length()) / 2;
    if (padTitle < 0) padTitle = 0;

    cout << "│";
    // pad left side of text
    for (int i = 0; i < padTitle; ++i) cout << " ";
    
    cout << BOLD << PRIMARY_COLOR << mainTitle << RESET << SECONDARY_COLOR << BOLD;

    // pad right side of text
    int titlePrinted = padTitle + mainTitle.length();
    for (int i = 0; i < (width - 2 - titlePrinted); ++i) cout << " ";
    
    cout << "│" << endl;

    // Sub-header Centered (capitalized)
    string sub = title;
    for (auto& c : sub) c = toupper(c);

    int padSub = (width - 2 - sub.length()) / 2;
    if (padSub < 0) padSub = 0;
    
    cout << "│";
    // pad left side of text
    for (int i = 0; i < padSub; ++i) cout << " ";

    cout << RESET << SECONDARY_COLOR << sub << RESET << SECONDARY_COLOR << BOLD;

    // pad right side of text
    int subPrinted = padSub + sub.length();
    for (int i = 0; i < (width - 2 - subPrinted); ++i) cout << " ";
    
    cout << "│" << endl;

    // Bottom border of Header box
    cout << "└";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┘" << RESET << endl;
}

void ConsoleUI::pause() 
{
    cout << endl << LABEL_COLOR << "Press [Enter] to continue..." << RESET;
    cin.get();
    cout << endl;
}

void ConsoleUI::printSuccess(const string& message) 
{
    cout << SUCCESS_COLOR << BOLD << "[ ✓ ] " << RESET << SUCCESS_COLOR << message << RESET << endl;
}

void ConsoleUI::printError(const string& message) 
{
    cout << ERROR_COLOR << BOLD << "[ ✗ ] " << RESET << ERROR_COLOR << message << RESET << endl;
}

void ConsoleUI::printInfo(const string& message) 
{
    cout << BLUE << BOLD << "[ i ] " << RESET << SECONDARY_COLOR << message << RESET << endl;
}

void ConsoleUI::printLabelValue(const string& label, const string& value) 
{
    cout << LABEL_COLOR << label << ": " << RESET << SECONDARY_COLOR << value << RESET << endl;
}

string ConsoleUI::promptString(const string& prompt, bool required) 
{
    string input;
    while (true) 
    {
        cout << LABEL_COLOR << prompt << ": " << RESET;
        if (!getline(cin, input)) 
        {
            cin.clear();
            continue;
        }
        
        // Remove potential trailing carriage returns from files/redirected inputs
        if (!input.empty() && input.back() == '\r') {
            input.pop_back();
        }

        if (required && input.empty()) {
            printError("This field cannot be empty. Please try again.");
            continue;
        }
        break;
    }
    return input;
}

int ConsoleUI::promptInt(const string& prompt, int minVal, int maxVal) 
{
    string line;
    int value;
    while (true) 
    {
        cout << LABEL_COLOR << prompt << " (" << minVal << " - " << maxVal << "): " << RESET;
        if (!getline(cin, line)) 
        {
            cin.clear();
            continue;
        }
        
        stringstream ss(line);
        if (ss >> value && ss.eof()) 
        {
            if (value >= minVal && value <= maxVal) 
            {
                break;
            }
        }
        printError("Invalid integer input or out of bounds. Please try again.");
    }
    return value;
}

double ConsoleUI::promptDouble(const string& prompt, double minVal) 
{
    string line;
    double value;
    while (true) 
    {
        cout << LABEL_COLOR << prompt << " (Min: " << minVal << "): " << RESET;
        if (!getline(cin, line)) 
        {
            cin.clear();
            continue;
        }
        
        stringstream ss(line);
        if (ss >> value && ss.eof()) {
            if (value >= minVal) {
                break;
            }
        }
        printError("Invalid decimal value. Please try again.");
    }
    return value;
}

bool ConsoleUI::promptConfirm(const string& prompt) 
{
    while (true) 
    {
        string ans = promptString(prompt + " (y/n)", true);
        if (ans == "y" || ans == "Y" || ans == "yes" || ans == "Yes") 
        {
            return true;
        }
        if (ans == "n" || ans == "N" || ans == "no" || ans == "No") 
        {
            return false;
        }
        printError("Please enter 'y' for Yes or 'n' for No.");
    }
}

int ConsoleUI::showMenu(const string& menuTitle, const DynamicArray<string>& options) 
{
    clearScreen();
    printHeader(menuTitle);
    
    int width = DIVIDER_LENGTH;

    // Top border of Menu Box
    cout << SECONDARY_COLOR << BOLD << "┌";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┐" << endl;

    cout << "│";
    for (int i = 0; i < width - 2; ++i) cout << " ";
    cout << "│" << endl;

    for (size_t i = 0; i < options.size(); ++i) 
    {
        int textLen = 4 + to_string(i + 1).length() + options[i].length();
        
        cout << "│" << RESET << " " << SECONDARY_COLOR << BOLD << "[" << (i + 1) << "] " 
             << RESET << SECONDARY_COLOR << options[i];
             
        int spaces = width - 2 - textLen;
        if (spaces < 0) spaces = 0;
        for (int s = 0; s < spaces; ++s) cout << " ";
        cout << SECONDARY_COLOR << BOLD << "│" << endl;
    }

    // Bottom border of Menu Box
    cout << "│";
    for (int i = 0; i < width - 2; ++i) cout << " ";
    cout << "│" << endl;
    cout << "└";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┘" << RESET << endl;

    printDivider();
    cout << endl;
    
    return promptInt("Select an option", 1, options.size());
}

void ConsoleUI::printTable(const DynamicArray<string>& headers, const DynamicArray<int>& widths, const DynamicArray<DynamicArray<string>>& rows) 
{
    if (headers.empty()) return;

    // Top border
    cout << SECONDARY_COLOR << BOLD;
    cout << "┌";
    for (size_t i = 0; i < headers.size(); ++i) 
    {
        for (int j = 0; j < widths[i] + 2; ++j) cout << "─";
        if (i < headers.size() - 1) cout << "┬";
    }
    cout << "┐" << endl;

    // Headers
    cout << "│";
    for (size_t i = 0; i < headers.size(); ++i) 
    {
        cout << " " << BOLD << SECONDARY_COLOR << left << setw(widths[i]) << headers[i] << RESET << SECONDARY_COLOR << " │";
    }
    cout << endl;

    // Divider separating headers and rows
    cout << "├";
    for (size_t i = 0; i < headers.size(); ++i) 
    {
        for (int j = 0; j < widths[i] + 2; ++j) cout << "─";
        if (i < headers.size() - 1) cout << "┼";
    }
    cout << "┤" << endl;

    // Data rows
    for (size_t r = 0; r < rows.size(); ++r) 
    {
        cout << "│";
        for (size_t c = 0; c < headers.size(); ++c) 
        {
            string val = "";
            if (c < rows[r].size()) 
            {
                val = rows[r][c];
            }
            cout << " " << SECONDARY_COLOR << left << setw(widths[c]) << val << RESET << SECONDARY_COLOR << " │";
        }
        cout << endl;
    }

    // Bottom border
    cout << "└";
    for (size_t i = 0; i < headers.size(); ++i) 
    {
        for (int j = 0; j < widths[i] + 2; ++j) cout << "─";
        if (i < headers.size() - 1) cout << "┴";
    }
    cout << "┘" << RESET << endl;
}

string ConsoleUI::formatDouble(double val) {
    stringstream ss;
    ss << fixed << setprecision(2) << val;
    return ss.str();
}