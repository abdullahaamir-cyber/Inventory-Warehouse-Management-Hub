#ifndef TRANSACTION_LOG_H
#define TRANSACTION_LOG_H

#include <iostream>
#include "DynamicArray.h"
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
        std::cout << "\n--- SYSTEM AUDIT TRAIL ---\n";
        if (actions.empty()) {
            std::cout << "No logs recorded yet.\n";
            return;
        }
        for (size_t i = 0; i < actions.size(); i++) {
            std::cout << "[" << timestamps[i] << "] ACTION: " << actions[i] << "\n";
        }
    }

    // <-- ADDED: Empties the DynamicArrays to support your "Clear Historical logs" option
    void clearLogs() {
        timestamps.clear();
        actions.clear();
        entities.clear();
        std::cout << "[SYSTEM]: All historical logs have been permanently cleared.\n";
    }
};

#endif