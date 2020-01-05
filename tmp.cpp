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



};

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
