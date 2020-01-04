#pragma once

#include <iostream>
#include <string>

using std::ostream;
using std::string;

class Date {
 public:
    Date();
    explicit Date(const string& date);
    void ParseDate(const string& date);
    friend ostream operator<<(ostream& os);

 private:
    int day, month, year;
};
