#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

void split(const std::string& input, std::vector<std::string>& output, char delim) {
    std::string temp;
    for (auto ch : input) {
        if (ch == delim || ch == '\n') {
            output.push_back(temp);
            temp.clear();
        } else {
            temp.push_back(ch);
        }
    }
    if (!temp.empty()) {
        output.push_back(temp);
    }
}

class DateBase {
 public:
    void Add(std::string& date, std::string& event);
    std::string Delete(std::string& date, std::string& event);
    std::string Delete(std::string& date_str);
    std::vector<std::string> Find(std::string& date_str)const ;
    std::vector<std::string> Print() const;

 private:
    class Date {
     public:
        Date();
        explicit Date(std::string& date);
        std::string GetDate() const;
        bool operator<(const Date& rhs) const;
        bool operator==(const Date& rhs) const;
     private:
        int day, month, year;
    };

    std::map<Date, std::set<std::string>> data;

};

DateBase::Date::Date() : day(0), month(0), year(0) {}

DateBase::Date::Date(std::string& date) {
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

bool DateBase::Date::operator<(const DateBase::Date& rhs) const {
    if (this->year == rhs.year) {
        if (this->month == rhs.month) {
            return this->day < rhs.day;
        } else {
            return this->month < rhs.month;
        }
    } else {
        return this->year < rhs.year;
    }
}

bool DateBase::Date::operator==(const DateBase::Date& rhs) const {
    return ((this->year == rhs.year) && (this->month == rhs.month) && (this->day == rhs.day));
}

std::string DateBase::Date::GetDate() const {
    std::string res;
    std::string y_s, m_s, d_s;
    y_s = std::to_string(year);
    m_s = std::to_string(month);
    d_s = std::to_string(day);

    for(int i = y_s.size(); i < 4; ++i) {
        res += '0';
    }
    res += y_s + '-';
    if (m_s.size() == 1) {
        res += '0';
    }
    res += m_s + '-';
    if (d_s.size() == 1) {
        res += '0';
    }
    res += d_s;
    return res;
}

int main() {
    DateBase DB;
    std::string input;
    while(std::getline(cin, input)) {
        if (input == "\n" || input.empty()) {
            continue;
        }
        std::vector<std::string> splitted;
        split(input, splitted, ' ');
        std::string command = splitted[0];
        if (command == "Add") {
            if (splitted.size() != 3) {
                continue;
            }
            try {
                DB.Add(splitted[1], splitted[2]);
            } catch(std::exception& exc) {
                cout << exc.what() << endl;
            }
        } else if (command == "Del") {
            if (splitted.size() == 2) {
                try {
                    cout << DB.Delete(splitted[1]) << endl;
                } catch(std::exception& exc) {
                    cout << exc.what() << endl;
                }
            } else if (splitted.size() == 3) {
                try {
                    cout << DB.Delete(splitted[1], splitted[2]) << endl;
                } catch(std::exception& exc) {
                    cout << exc.what() << endl;
                }
            } else {
                continue;
            }
        } else if (command == "Find") {
            if (splitted.size() == 2) {
                try {
                    for(const auto& line : DB.Find(splitted[1])) {
                        cout << line << endl;
                    }
                } catch(std::exception& exc) {
                    cout << exc.what() << endl;
                }
            } else {
                continue;
            }
        } else if (command == "Print") {
            if (splitted.size() == 1) {
                try {
                    for(const auto& line : DB.Print()) {
                        cout << line << endl;
                    }
                } catch(std::exception& exc) {
                    cout << exc.what() << endl;
                }
            } else {
                continue;
            }
        } else {
            cout <<"Unknown command: " << command << endl;
        }
    }
    return 0;
}


void DateBase::Add(std::string& date_str, std::string& event) {
    Date date;
    try {
        date = Date(date_str);
    } catch (...) {
        throw;
    }
    data[date].insert(event);
}

std::string DateBase::Delete(std::string& date_str, std::string& event) {
    Date date;
    try {
        date = Date(date_str);
    } catch (...) {
        throw;
    }
    auto date_it = data.find(date);
    if (date_it != data.end()) {
        auto event_it = date_it->second.find(event);
        if (event_it != date_it->second.end()) {
            date_it->second.erase(event_it);
            return "Deleted successfully";
        }
    }
    return "Event not found";
}

std::string DateBase::Delete(std::string& date_str) {
    Date date;
    try {
        date = Date(date_str);
    } catch (...) {
        throw;
    }
    int n = 0;
    auto it = data.find(date);
    if (it != data.end()) {
        n = it->second.size();
        data.erase(it);
    }
    return ("Deleted " + std::to_string(n) + " events");
}

std::vector<std::string> DateBase::Find(std::string& date_str) const {
    std::vector<std::string> out;
    Date date;
    try {
        date = Date(date_str);
    } catch (...) {
        throw;
    }
    auto it = data.find(date);
    if (it != data.end()) {
        for (const auto& event : it->second) {
            out.push_back(event);
        }
    }
    return out;
}

std::vector<std::string> DateBase::Print() const {
    std::vector<std::string> out;
    for (const auto& d_pair : data) {
        for (const auto& event : d_pair.second) {
            out.emplace_back(d_pair.first.GetDate() + " " + event);
        }
    }
    return out;
}
