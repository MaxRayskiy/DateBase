#pragma once

#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

class Date {
 public:
    Date();
    explicit Date(const string& date);

    [[nodiscard]] string GetDate() const;


    bool operator<(const Date& rhs) const;
    bool operator<=(const Date& rhs) const;
    bool operator>(const Date& rhs) const;
    bool operator>=(const Date& rhs) const;
    bool operator==(const Date& rhs) const;
    bool operator!=(const Date& rhs) const;

 private:
    int day, month, year;
};

ostream operator<<(ostream& os, const Date& date);

Date ParseDate(istream& is) {
    string date;
    is >> date;
    return Date(date);
}