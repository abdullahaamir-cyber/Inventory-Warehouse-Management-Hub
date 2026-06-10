#ifndef TRANSACTION_LOG_H
#define TRANSACTION_LOG_H

#include "DynamicArray.h"
#include "ConsoleUI.h"
#include <string>

template <typename T>
class TransactionLog {
private:
    DynamicArray<std::string> timestamps;
    DynamicArray<std::string> actions;
    DynamicArray<T> entities;

public:
    void recordAction(const std::string& time, const std::string& action, const T& entity) {
        timestamps.push_back(time);
        actions.push_back(action);
        entities.push_back(entity);
    }

    void printAuditTrail() const {
        ConsoleUI::printHeader("System Audit Trail Log");
        if (actions.empty()) {
            ConsoleUI::printInfo("No transaction logs recorded yet in simulated memory.");
            return;
        }
        for (int i = 0; i < actions.size(); i++) {
            ConsoleUI::printLabelValue("[" + timestamps[i] + "] ACTION", actions[i]);
        }
    }

    void clearLogs() {
        timestamps.clear();
        actions.clear();
        entities.clear();
        ConsoleUI::printSuccess("System database clearance complete: all transaction log trails cleared.");
    }
};

#endif