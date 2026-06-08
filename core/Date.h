#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}

    // Parse YYYY-MM-DD
    static Date parseString(const std::string& dateStr) {
        int d = 1, m = 1, y = 2026;
        char dash1, dash2;
        std::stringstream ss(dateStr);
        ss >> y >> dash1 >> m >> dash2 >> d;
        return Date(d, m, y);
    }

    std::string toString() const {
        std::stringstream ss;
        ss << year << "-" 
           << std::setfill('0') << std::setw(2) << month << "-" 
           << std::setfill('0') << std::setw(2) << day;
        return ss.str();
    }

    // Comparison operators
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator<=(const Date& other) const {
        return (*this < other) || (*this == other);
    }

    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getDay() const { return day; }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.toString();
        return os;
    }
};

#endif