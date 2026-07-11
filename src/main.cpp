#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h> 
using namespace std;


bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


void displayTime12Hours(int hour, int minute, int second) {
    string am_pm = (hour < 12) ? "AM" : "PM";
    if (hour > 12) hour -= 12;
    cout << "  Time: " << setw(2) << setfill('0') << hour << ":"
         << setw(2) << setfill('0') << minute << ":"
         << setw(2) << setfill('0') << second << " " << am_pm << endl;
}


void displayTime24Hours(int hour, int minute, int second) {
    cout << "  Time: " << setw(2) << setfill('0') << hour << ":"
         << setw(2) << setfill('0') << minute << ":"
         << setw(2) << setfill('0') << second << endl;
}


void displayDate(int day, int month, int year) {
    string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    string days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    int k = year % 100, j = year / 100;
    int dayOfWeek = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    cout << "  Day: " << days[dayOfWeek] << endl;
    cout << "  Date: " << months[month - 1] << " " << day << ", " << year << endl;
}


void showTimeAndDate() {
    int hour, minute, second, formatOption, day, month, year;
    char timezoneChoice;
    cout << "Enter Time (HH MM SS): ";
    cin >> hour >> minute >> second;

    
    if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60 || second < 0 || second >= 60) {
        cout << "Invalid time input.\n";
        return;
    }

    cout << "Select Time Format (1 for 24-hour, 2 for 12-hour): ";
    cin >> formatOption;

    if (formatOption != 1 && formatOption != 2) {
        cout << "Invalid time format choice.\n";
        return;
    }

    cout << "Enter Date (DD MM YYYY): ";
    cin >> day >> month >> year;

    
    if (day < 1 || month < 1 || month > 12 || year < 0) {
        cout << "Invalid date input.\n";
        return;
    }

    
    int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > daysInMonth[month - 1]) {
        cout << "Invalid day for the given month.\n";
        return;
    }

    cout << "Do you want to display time in a specific timezone format? (y/n): ";
    cin >> timezoneChoice;

    if (timezoneChoice == 'y' || timezoneChoice == 'Y') {
        char tzChoice;
        cout << "Select timezone (P for PST, E for EST): ";
        cin >> tzChoice;

        
        if (tzChoice == 'P' || tzChoice == 'p') {
            hour -= 8;
            if (hour < 0) hour += 24;  // Adjust for negative hours
            cout << "Timezone: Pacific Standard Time (PST)" << endl;
        } else if (tzChoice == 'E' || tzChoice == 'e') {
            hour -= 5;
            if (hour < 0) hour += 24;  // Adjust for negative hours
            cout << "Timezone: Eastern Standard Time (EST)" << endl;
        } else {
            cout << "Invalid timezone selection.\n";
        }
    }
  
    Sleep(1500);
    
    while (true) {
        system("cls");
         cout << "\nPress 'q' anytime to go back to menu\n";
        displayDate(day, month, year);
        if (formatOption == 1) {
            displayTime24Hours(hour, minute, second);
        } else {
            displayTime12Hours(hour, minute, second);
        }
        
        
        
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'q' || ch == 'Q') {
                return; 
            }
        }
        
        Sleep(1000); 

        second++;
        if (second == 60) {
            second = 0;
            minute++;
            if (minute == 60) {
                minute = 0;
                hour++;
                if (hour == 24) {
                    hour = 0;
                    day++;
                  
                    int daysInCurrentMonth = daysInMonth[month - 1];
                    if (day > daysInCurrentMonth) {
                        day = 1;
                        month++;
                        if (month > 12) {
                            month = 1;
                            year++;
                        }
                    }
                }
            }
        }
    }
}


void startStopwatch() {
    int seconds = 0, minutes = 0, hours = 0;
    char userChoice;
    while (true) {
        system("cls");
        cout << "Stopwatch: " << setw(2) << setfill('0') << hours << ":"
             << setw(2) << setfill('0') << minutes << ":"
             << setw(2) << setfill('0') << seconds << endl;
        cout << "Press 'p' to pause : 'r' to reset :   'q' to quit :" << endl;
        Sleep(1000); 
        seconds++;
        if (seconds == 60) {
            minutes++;
            seconds = 0;
            if (minutes == 60) {
                hours++;
                minutes = 0;
            }
        }
        if (_kbhit()) {
            userChoice = _getch();
            if (userChoice == 'p') {
                cout << "Stopwatch paused   Press :  'r' to resume :   'q' to quit :" << endl;
                while (_kbhit() || userChoice != 'r') {
                    userChoice = _getch();
                    if (userChoice == 'r') break;
                    if (userChoice == 'q') return;
                }
            } else if (userChoice == 'r') {
                seconds = 0;
                minutes = 0;
                hours = 0;
            } else if (userChoice == 'q') {
                return;
            }
        }
    }
}


void startTimer() {
    int hours, minutes, seconds;
    char userChoice;
    cout << "Enter timer time (HH MM SS): ";
    cin >> hours >> minutes >> seconds;
    while (hours >= 0) {
        system("cls");
        cout << "Timer: " << setw(2) << setfill('0') << hours << ":"
             << setw(2) << setfill('0') << minutes << ":"
             << setw(2) << setfill('0') << seconds << endl;
        cout << "Press 'p' to pause :   'r' to reset :   'q' to quit :" << endl;
        Sleep(1000); 
        seconds--;
        if (seconds < 0) {
            seconds = 59;
            minutes--;
            if (minutes < 0) {
                minutes = 59;
                hours--;
            }
        }
        if (hours == 0 && minutes == 0 && seconds == 0) {
            cout << "Time's up!" << endl;
            Beep(523, 1000); 
            return;
        }
        if (_kbhit()) {
            userChoice = _getch();
            if (userChoice == 'p') {
                cout << "Timer paused. Press 'r' to resume or 'q' to quit." << endl;
                while (_kbhit() || userChoice != 'r') {
                    userChoice = _getch();
                    if (userChoice == 'r') break;
                    if (userChoice == 'q') return;
                }
            } else if (userChoice == 'r') {
                cout << "Timer reset." << endl;
                startTimer();
                return;
            } else if (userChoice == 'q') {
                return;
            }
        }
    }
}


int calculateDayOfWeek(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int k = year % 100;
    int j = year / 100;
    int dayOfWeek = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (dayOfWeek + 6) % 7;
}


  void displayCalendar(int month, int year) {
    string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    string dayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    
    int startDay = calculateDayOfWeek(1, month, year);

    system("cls");
    cout << "\n   " << months[month - 1] << " " << year << endl;
    cout << "-----------------------------------" << endl;

    for (int i = 0; i < 7; i++) {
        cout << setw(5) << dayNames[i];
    }
    cout << endl;
    cout << "-----------------------------------" << endl;

    
    int col = startDay;
    for (int i = 0; i < startDay; i++) {
        cout << setw(5) << " ";
    }

    
    for (int d = 1; d <= daysInMonth[month - 1]; d++) {
        cout << setw(5) << d;
        col++;
        if (col % 7 == 0) {
            cout << endl;
        }
    }

    cout << "\n\n";
    cout << "Press any key to go back to menu...";
    _getch();                    
}
    
    


void reminder() {
    int currentHour, currentMinute, currentSecond;
    int targetHour, targetMinute, targetSecond;
    string message;

    cout << "Enter the current time (24-hour format): \n";
    cout << "Hour (0-23): ";
    cin >> currentHour;
    cout << "Minute (0-59): ";
    cin >> currentMinute;
    cout << "Second (0-59): ";
    cin >> currentSecond;

    cout << "\nEnter the time for your reminder (24-hour format): \n";
    cout << "Hour (0-23): ";
    cin >> targetHour;
    cout << "Minute (0-59): ";
    cin >> targetMinute;
    cout << "Second (0-59): ";
    cin >> targetSecond;

    cout << "\nEnter the message for your reminder: ";
    cin.ignore(); 
    getline(cin, message);

    while (true) {
        system("cls");  

        cout << "Current Time: "
             << setw(2) << setfill('0') << currentHour << ":"
             << setw(2) << setfill('0') << currentMinute << ":"
             << setw(2) << setfill('0') << currentSecond << endl;
        
        if (currentHour == targetHour && currentMinute == targetMinute && currentSecond == targetSecond) {
            cout << "\n*** Reminder: " << message << " ***" << endl;
            Beep(523, 1000); 
            break;
        }

        currentSecond++;
        if (currentSecond == 60) {
            currentSecond = 0;
            currentMinute++;
            if (currentMinute == 60) {
                currentMinute = 0;
                currentHour++;
                if (currentHour == 24) {
                    currentHour = 0;
                }
            }
        }

        Sleep(1000);  
    }
}


int main() {
    int choice;
    do{
    
    cout << "==============================\n";
    cout << "Select an option: \n";
    cout << "==============================\n";
    cout << "1. Display Time, Date & Time Zone\n";
    cout << "2. Start Stopwatch\n";
    cout << "3. Start Timer\n";
    cout << "4. Display Calendar\n";
    cout << "5. Set Reminder\n";
    cout << "6. Exit\n";
    cout << "==============================\n";
    cout << "Enter your choice (1-6): ";
    cin >> choice;

    switch (choice) {
        case 1:
            showTimeAndDate();
            break;
        case 2:
            startStopwatch();
            break;
        case 3:
            startTimer();
            break;
        case 4: {
            int month, year;
            
    
            cout << "Enter month (1-12): ";
            cin >> month;
            cout << "Enter year: ";
            cin >> year;
            
    
            if (month < 1 || month > 12 || year < 1) {
                    cout << "Invalid month or year!\n";
                    Sleep(1500);
                } else {
                    displayCalendar(month, year);
                }
                break;
        }
        case 5:
            reminder();
            break;
        case 6:
            cout << "Exiting program.\n";
            break;
		default:
            cout << "Invalid choice.\n";
            break;
    }
}while(choice!=6);
return 0;
}
