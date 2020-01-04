#include "date.h"

Date::Date()
    : day(0)
    , month(0)
    , year(0)
{}

Date::Date(const string& date)
  : day(0)
    , month(0)
    , year(0)
{
    ParseDate(date);
}

void Date::ParseDate(const string& date) {
    for (auto ch : date) {
        if (ch != '-' && ch != '+' && !isdigit(ch)) {
            throw std::invalid_argument("Wrong date format: " + date);
        }
    }
    int beg = 0, end = 0;
    for (int i = 1; i < date.size(); ++i) {
        if (date[i] == '-') {
            beg = i;
            break;
        }
    }
    for (int i = static_cast<int>(date.size()) - 1; i >= 0; --i) {
        if (date[i] == '-') {
            end = i;
            if (i > 0 && date[i - 1] == '-') {
                end = i - 1;
            }
            break;
        }
    }
    if (beg >= end) {
        throw std::invalid_argument("Wrong date format: " + date);
    }
    try {
        year = std::stoi(date.substr(0, beg));
        month = std::stoi(date.substr(beg + 1, end));
        day = std::stoi(date.substr(end + 1, date.size()));
    } catch (...) {
        throw std::invalid_argument("Wrong date format: " + date);
    }
    if (month <= 0 || month > 12) {
        throw std::invalid_argument("Month value is invalid: " + std::to_string(month));
    }
    if (day <= 0 || day > 31) {
        throw std::invalid_argument("Day value is invalid: " + std::to_string(day));
    }
}


