#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace std;

// Class to represent a task
class Task {
public:
    string title;
    string date;
    int importance;

    Task(string t, string d, int i) : title(t), date(d), importance(i) {}

    void display() const {  // Make display() a const member function
        cout << setw(20) << left << title << setw(15) << date << setw(10) << importance << endl;
    }
};

// Function to input tasks
void inputTasks(vector<Task>& tasks) {
    int n;
    cout << "Enter number of tasks: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string title, date;
        int importance;
        cout << "Enter title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter importance (1-10): ";
        cin >> importance;
        tasks.emplace_back(title, date, importance);
    }
}

// Function to sort tasks by date and importance
bool compareTasks(const Task& a, const Task& b) {
    if (a.date == b.date)
        return a.importance > b.importance;
    return a.date < b.date;
}

void sortTasks(vector<Task>& tasks) {
    sort(tasks.begin(), tasks.end(), compareTasks);
}

// Function to display tasks
void displayTasks(const vector<Task>& tasks) {
    cout << setw(20) << left << "Title" << setw(15) << "Date" << setw(10) << "Importance" << endl;
    cout << string(45, '-') << endl;
    for (const auto& task : tasks) {
        task.display();
    }
}

// Function to display the menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add tasks\n";
    cout << "2. Display tasks\n";
    cout << "3. Display calendar\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// Function to get current month calendar
void displayCalendar() {
    time_t t = time(0);   // Get current time
    struct tm * now = localtime(&t);

    int year = now->tm_year + 1900;
    int month = now->tm_mon + 1;
    
    cout << "Calendar for " << month << "/" << year << endl;

    // Print the days of the week
    cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

    // Find out the first day of the month
    struct tm first_day = {0};
    first_day.tm_year = now->tm_year;
    first_day.tm_mon = now->tm_mon;
    first_day.tm_mday = 1;
    mktime(&first_day);

    // Print initial spaces
    for (int i = 0; i < first_day.tm_wday; ++i) {
        cout << "    ";
    }

    // Print the days of the month
    int days_in_month = 31; // Default to 31 days
    switch (month) {
        case 4: case 6: case 9: case 11: days_in_month = 30; break;
        case 2: days_in_month = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28; break;
    }

    for (int day = 1; day <= days_in_month; ++day) {
        cout << setw(3) << day << " ";
        if ((day + first_day.tm_wday) % 7 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

int main() {
    vector<Task> tasks;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            inputTasks(tasks);
            sortTasks(tasks);
            break;
        case 2:
            displayTasks(tasks);
            break;
        case 3:
            displayCalendar();
            break;
        case 4:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
