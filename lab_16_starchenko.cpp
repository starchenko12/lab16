#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;

    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int daysInMonth(int month, int year) {
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return -1; 
        }
    }

    bool validateDate(int year, int month, int day) {
        if (year < 0) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > daysInMonth(month, year)) return false;
        return true;
    }

public:
    Date(int year, int month, int day) {
        if (validateDate(year, month, day)) {
            this->year = year;
            this->month = month;
            this->day = day;
        }
        else {
            cout << "Invalid date entered!" << endl;
            this->year = 0;
            this->month = 1;
            this->day = 1;
        }
    }

    void setYear(int year) {
        if (validateDate(year, this->month, this->day)) {
            this->year = year;
        }
        else {
            cout << "Invalid year entered!" << endl;
        }
    }

    void setMonth(int month) {
        if (validateDate(this->year, month, this->day)) {
            this->month = month;
        }
        else {
            cout << "Invalid month entered!" << endl;
        }
    }

    void setDay(int day) {
        if (validateDate(this->year, this->month, day)) {
            this->day = day;
        }
        else {
            cout << "Invalid day entered!" << endl;
        }
    }

    void addDays(int days) {
        while (days > 0) {
            int daysInCurrentMonth = daysInMonth(this->month, this->year);
            if (this->day + days <= daysInCurrentMonth) {
                this->day += days;
                break;
            }
            else {
                days -= (daysInCurrentMonth - this->day + 1);
                this->day = 1;
                if (this->month == 12) {
                    this->month = 1;
                    this->year++;
                }
                else {
                    this->month++;
                }
            }
        }
    }

    void addMonths(int months) {
        int newMonth = this->month + months;
        this->year += newMonth / 12;
        this->month = newMonth % 12;
        if (this->month == 0) {
            this->month = 12;
            this->year--;
        }
        if (this->day > daysInMonth(this->month, this->year)) {
            this->day = daysInMonth(this->month, this->year);
        }
    }

    void addYears(int years) {
        this->year += years;
        if (this->month == 2 && this->day == 29 && !isLeapYear(this->year)) {
            this->day = 28;
        }
    }

    void displayDate() const {
        cout << "Date: " << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << endl;
    }
};

class Weekday : public Date {
private:
    string getDayOfWeek(int y, int m, int d) const {
        static const string daysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
        if (m < 3) {
            m += 12;
            y--;
        }
        int K = y % 100;
        int J = y / 100;
        int f = d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J;
        return daysOfWeek[f % 7];
    }

public:
    Weekday(int year, int month, int day) : Date(year, month, day) {}

    void displayDayOfWeek() const {
        cout << "Day of the week: " << getDayOfWeek(year, month, day) << endl;
    }
};

int main() {
    Date date(2023, 6, 15);
    date.displayDate();

    date.setYear(2024);
    date.displayDate();

    date.setMonth(2);
    date.displayDate();

    date.setDay(29);
    date.displayDate();

    date.addDays(10);
    date.displayDate();

    date.addMonths(2);
    date.displayDate();

    date.addYears(1);
    date.displayDate();

    Weekday weekday(2024, 2, 29);
    weekday.displayDate();
    weekday.displayDayOfWeek();

    return 0;
}
