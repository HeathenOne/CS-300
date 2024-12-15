//============================================================================
// Name        : Project Two
// Author      : Dylan Carter
// Version     : 1.0
// Copyright   : 
// Description : Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Define a structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;

    Course() = default;

    Course(const string& number, const string& courseTitle, const vector<string>& prereqs)
        : courseNumber(number), title(courseTitle), prerequisites(prereqs) {
    }
};

// Define the hash table for storing courses
unordered_map<string, Course> courses;

//============================================================================
// Function declarations 
//============================================================================

unordered_map<string, Course> loadCourses(const string& csvPath);
Course createCourse(const string& courseNumber, const string& name, const vector<string>& prerequisites);
void printCourseInfo(const string& courseNumber);
void displayCourseList();
void displayMenu();

// Utility function to convert a string to uppercase
string toUpperCase(const string& str);

//============================================================================
// Function implementations 
//============================================================================

/**
 * Function: loadCourses
 * Purpose: Loads courses from the CSV file into the hash table.
 */
unordered_map<string, Course> loadCourses(const string& csvPath) {
    unordered_map<string, Course> coursesHashTable;
    ifstream file(csvPath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << csvPath << endl;
        return coursesHashTable;
    }

    string line;
    while (getline(file, line)) {
        stringstream stream(line);
        string courseNumber, title, prereq;
        getline(stream, courseNumber, ',');
        getline(stream, title, ',');

        vector<string> prerequisites;
        while (getline(stream, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        Course course = createCourse(courseNumber, title, prerequisites);
        coursesHashTable[courseNumber] = course; // Add to hash table
    }

    file.close();
    cout << "Courses loaded successfully from " << csvPath << "!" << endl;
    return coursesHashTable;
}

/**
 * Function: createCourse
 * Purpose: Creates a new Course object.
 */
Course createCourse(const string& courseNumber, const string& name, const vector<string>& prerequisites) {
    return Course(courseNumber, name, prerequisites);
}

/**
 * Function: printCourseInfo
 * Purpose: Prints details for a specific course.
 */
void printCourseInfo(const string& courseNumber) {
    string upperCourseNumber = toUpperCase(courseNumber);
    auto it = courses.find(upperCourseNumber);
    if (it == courses.end()) {
        cerr << "Course not found: " << courseNumber << endl;
        return;
    }

    const Course& course = it->second;
    cout << "\n" << course.courseNumber << ": " << course.title << endl;
    cout << "Prerequisites:  ";
    if (course.prerequisites.empty()) {
        cout << "None" << endl;
    }
    else {
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

/**
 * Function: displayCourseList
 * Purpose: Prints all courses in alphanumeric order.
 */
void displayCourseList() {
    if (courses.empty()) {
        cout << "No courses loaded. Please load the course data first." << endl;
        return;
    }

    vector<string> sortedKeys;
    for (const auto& pair : courses) {
        sortedKeys.push_back(pair.first);
    }

    sort(sortedKeys.begin(), sortedKeys.end());

    cout << "\nCourse List:" << endl;
    for (const auto& courseNumber : sortedKeys) {
        const auto& course = courses[courseNumber];
        cout << course.courseNumber << ", " << course.title << endl;
    }
}

/**
 * Function: displayMenu
 * Purpose: Displays the menu to the user.
 */
void displayMenu() {
    cout << "\nWelcome to the course planner." << endl;
    cout << "1. Load Courses" << endl;
    cout << "2. Display Course List" << endl;
    cout << "3. Display Course Information" << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

// Utility function to convert a string to uppercase
string toUpperCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

//============================================================================
// Main function 
//============================================================================

int main() {
    string csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
    int choice = 0;

    while (choice != 9) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            courses = loadCourses(csvPath);
            break;
        case 2:
            displayCourseList();
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourseInfo(courseNumber);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
