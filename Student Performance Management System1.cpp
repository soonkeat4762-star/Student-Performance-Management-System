// Student Performance Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <vector> // Include vector header
#include <mysql.h>
#include <map>
#include <vector>
#include <cmath>
#include <utility>

#include <sstream> // Include for ostringstream
#include <thread>
#include <chrono>
#include <cctype>
#include <conio.h>  // For _getch() and _kbhit()
#include <regex> // For regex validation
#include <limits> // For numeric_limits
#include <fstream> // For file operations
#include <set>
#include <fstream>


#define NOMINMAX


using namespace std;


// Function declarations
void login(int lecturerId, const string& fullName);
void registerUser(int lecturerId, const string& fullName);
void registerAdmin(int lecturerId, const string& fullName); // Registration page for Admin
void registerLecturer(int lecturerId, const string& fullName); // Registration page  for Lecturer
void registerStudent(int lecturerId, const string& fullName); // Registration page for Student
void adminPage(int lecturerId, const string& fullName);
void lecturerPage(int lecturerId, const string& fullName);
void inputStudentMarks(int lecturerId, const string& fullName);
void updateStudentMarks(int lecturerId, const string& fullName);
void viewStudentMarksAndGrades(int lecturerId, const string& fullName);
void downloadMarksRecords(int lecturerId, const string& fullName);
void studentPage(const string& fullName, int studentId, int lecturerId);
void manageAccounts(int lecturerId, const string& fullName);
void setCourse(int lecturerId, const string& fullName);
void viewInformation(int lecturerId, const string& fullName);
void viewAssignedCourses(int studentId, const string& fullName, int lecturerId);
void viewGrades(int studentId, const string& fullName, int lecturerId);
void provideFeedback(int studentId, const string& fullName, int lecturerId);
void trimString(string& str);
void courseMenu(int lecturerId, const string& fullName);
void viewCourses();
void editCourses();
void deleteCourses();
void ViewCourses(int lecturerId, const string& fullName);
void searchCourseByCode(int lecturerId, const string& fullName);
void manageLecturerAccounts(int lecturerId, const string& fullName);
void viewAllStudents(int lecturerId, const string& fullName);
void deleteLecturerAccount(int lecturerId, const string& fullName);
void deleteStudentAccount(int lecturerId, const string& fullName);
void editLecturerAccount(int lecturerId, const string& fullName);
void editStudentAccount(int lecturerId, const string& fullName);
void searchStudentAccount(int lecturerId, const string& fullName);
void searchLecturerAccount(int lecturerId, const string& fullName);
void manageStudentAccounts(int lecturerId, const string& fullName);
void viewAllLecturers(int lecturerId, const string& fullName);
void assignCourseForStudent(int lecturerId, const string& fullName);
void viewAssignedStudents(const string& courseId);
void manageStudentAssignments(const string& courseId, const string& fullname, int lecturerId);
void assignStudentMajorAndYear(int lecturerId, const string& fullName);
void clearInputBuffer();
void viewStudentAssignedCourses(int lecturerId, const string& fullName);
void viewStudentAssignedCoursesInformation(int lecturerId, const string& fullName);
void assignCoursesToLecturer(int lecturerId, const string& fullName);
void viewCourseFeedback(int lecturerId, const string& fullName);
void viewCourseFeedbackForAdmin(int lecturerId, const string& fullName);
void viewSystemFeedback(int lecturerId, const string& fullName);
void setGradeRanges(int lecturerId, const string& fullName);
void viewGradeRanges(int lecturerId, const string& fullName);
void viewGradeRanges1(int lecturerId, const string& fullName);
void viewAllStudentsinformation(int lecturerId, const string& fullName);
void viewAllLecturersinformation(int lecturerId, const string& fullName);
static void printError(const string& message);
static void printSuccess(const string& message);
static void printLine();
void displayUpdatedMarks(int courseId);
void viewLecturerCourses(int lecturerId, const string& fullName);
void assignDepartmentToLecturer(int lecturerId, const string& fullName);
void viewLecturerDepartment(int lecturerId, const string& fullName);
// Function prototypes
void printOverallSummary(const map<string, double>& courseTotals);
double printCourseSummary(const string& courseName, double pblTotal, double exercise, double finalExam);
string getGradeForScore(double score);
void analyzeGradeDistributionByScoreType(int courseId);
void analyzeOverallGradeDistribution(int courseId);
//void analyzePassFailDistribution(int courseId);


// Global variables
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

class db_response {
public:
    static void ConnectionFunction() {
        conn = mysql_init(0);
        if (!conn) {
            cout << "DATABASE CONNECTION : ";
            cout << "Failed to initialize MySQL library!" << endl;
            exit(1); // Exit the program
        }

        conn = mysql_real_connect(conn, "localhost", "root", "", "student performance management system", 3306, NULL, 0);
        if (!conn) {
            cout << "DATABASE CONNECTION : ";
            cout << "\033[31mFailed to connect to the database: please check your database connection and turn on your port database \033[0m" << mysql_error(conn) << "\033[0m" << endl;
            mysql_close(conn);
            exit(1); // Exit the program
        }
        cout << "DATABASE CONNECTION : ";
        cout << "\033[32mDatabase Connected Successfully \033[0m" << endl;
        cout << endl;

        // Print border
        for (int i = 0; i < 120; ++i) {
            cout << "=";
        }
        cout << endl;
    }
};

int main(int lecturerId, const string& fullName) {
    system("cls"); // Clear the screen before displaying the main menu

    // Database response (connection or not)
    db_response db; // Create an instance of the db_response class
    db.ConnectionFunction(); // Call the function to establish a database connection

    while (true) {
        system("cls");

        cout << string(120, '=') << endl;
        int menu; // Declare menu variable
        // Centered title for the system
        cout << setw((120 - 38) / 2) << "" << "WELCOME TO STUDENT PERFORMANCE" << endl;
        cout << setw((120 - 23) / 2) << "" << "MANAGEMENT SYSTEM" << endl;
        cout << string(120, '=') << endl;

        // Display menu items with spacing for readability
        cout << "\n  1. Log In" << endl;
        cout << "  2. Register New Account" << endl;
        cout << "  3. Exit" << endl;

        cout << string(120, '-') << endl;
        cout << "Please enter your choice: ";
        cin >> menu; // Get user input

        // Process user input
        switch (menu) {
        case 1:
            login(lecturerId, fullName); // Call login function
            break;
        case 2:
            registerUser(lecturerId, fullName); // Call registerUser function
            break;
        case 3:
            cout << "Program Exiting..." << endl;
            cout.flush(); // Ensure the output buffer is flushed
            mysql_close(conn); // Close the database connection
            exit(0);
        default:
            cout << "Invalid choice. Please choose between 1 - 3. Press Enter to continue...";
            (void)_getch(); // Wait for user to acknowledge the message
            break;
        }
    }

    return 0;
}

static void showLoadingScreen(const string& message, int duration = 3) {
    cout << message << endl;
    cout << "\n";
    for (int i = 0; i < duration * 3; ++i) { // Adjust iterations for timing
        cout << "\rLoading"; // \r brings the cursor back to the start of the line
        for (int j = 0; j <= (i % 4); ++j) {
            cout << "."; // Add dots to simulate progress
        }
        cout << flush; // Flush the output to show changes immediately
        this_thread::sleep_for(chrono::milliseconds(250)); // Delay for a short time
    }
    system("cls"); // Clear the screen after loading
}

// Function to center text
void printCentered(const string& text, int consoleWidth) {
    int padding = (consoleWidth - text.length()) / 2;
    cout << string(padding, ' ') << text << endl;
}


// Function for user registration
void registerUser(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    int userTypeChoice;

    // Display user type options with better formatting
    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("USER REGISTRATION PAGE", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << "\nChoose the type of user you want to register:\n" << endl;
    cout << "[1] Admin" << endl;
    cout << "[2] Lecturer" << endl;
    cout << "[3] Student" << endl;
    cout << "[4] Return to Main Page" << endl;
    cout << "[5] Exit" << endl;
    cout << string(120, '-') << endl;
    cout << "Please enter your choice:  ";
    cin >> userTypeChoice;

    switch (userTypeChoice) {
    case 1:
        registerAdmin(lecturerId, fullName); // Redirect to Admin registration page
        break;
    case 2:
        registerLecturer(lecturerId, fullName); // Redirect to Lecturer registration page
        break;
    case 3:
        registerStudent(lecturerId, fullName); // Redirect to Student registration page
        break;
    case 4:
        main(lecturerId, fullName); // Redirect to Main page
        return;
    case 5:
        cout << "Exiting registration..." << endl;
        mysql_close(conn);
        exit(0);
    default:
        cout << "Invalid choice. Please try again." << endl;
        (void)_getch();
        system("cls");
        registerUser(lecturerId, fullName); // Recursively call to retry
        return;
    }
}


// Email validation function
bool isEmailValid(const string& email) {
    const regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

// Phone number validation function
bool isPhoneNumberValid(const string& phone) {
    const regex pattern(R"(^\d{10,15}$)"); // 10-15 digits
    return regex_match(phone, pattern);
}

// Check if username or email is unique in the database
bool isFieldUnique(const string& field, const string& value) {
    string query = "SELECT COUNT(*) FROM users WHERE " + field + " = '" + value + "'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        return stoi(row[0]) == 0; // Field is unique if COUNT == 0
    }
    return false; // Database error
}

void printError(const string& message) {
    cout << "\033[31m" << message << "\033[0m" << endl; // Red color for errors
    this_thread::sleep_for(chrono::seconds(3));
}
void printWarning(const string& message) {
    cout << "\033[33m" << message << "\033[0m" << endl; // Yellow color for warnings
    this_thread::sleep_for(chrono::seconds(3));
}
void printLine() {
    cout << string(120, '-') << endl;
}



void printSuccess(const string& message) {
    cout << "\033[32m" << message << "\033[0m" << endl; // Green color for success
    this_thread::sleep_for(chrono::seconds(3));
}

void registerAdmin(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls");

    string username, password, firstName, lastName, email, phoneNumber;
    bool usernameValid = false, passwordValid = false, emailValid = false;
    bool firstNameValid = false, lastNameValid = false, phoneNumberValid = false;

    while (!usernameValid || !passwordValid || !emailValid || !firstNameValid || !lastNameValid || !phoneNumberValid) {
        system("cls");

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("ADMIN REGISTRATION PAGE", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;


        // Display previously validated inputs
        if (usernameValid) cout << "Enter Username: " << username << endl;
        else {
            cout << "Enter Username: ";
            getline(cin >> ws, username);
            if (username.empty() || !isFieldUnique("username", username)) {
                printError("Notice: The username is empty or already taken. Please choose another one.");
                continue;
            }
            usernameValid = true;
        }

        if (passwordValid) cout << "Enter Password (minimum 6 characters): " << string(password.length(), '*') << endl;
        else {
            cout << "Enter Password (minimum 6 characters):  ";
            password = ""; // Clear the password variable
            char ch;

            while ((ch = _getch()) != '\r') { // Press Enter to end input
                if (ch == '\b') { // Check if Backspace key is pressed
                    if (!password.empty()) {
                        password.pop_back(); // Remove the last character from the password
                        cout << "\b \b";     // Remove the last '*' from the console
                    }
                }
                else if (isprint(ch)) { // Check if input is a printable character
                    password += ch; // Add the character to the password
                    cout << '*';    // Display a '*'
                }
            }

            cout << endl; // Move to the next line after input

            if (password.empty() || password.length() < 6) {
                printError("Notice: Password must be at least 6 characters long. Please try again.");
                continue;
            }
            passwordValid = true; // Set flag to true once validation is passed
        }

        if (emailValid) cout << "Enter Email: " << email << endl;
        else {
            cout << "Enter Email: ";
            getline(cin >> ws, email);
            if (!isEmailValid(email) || !isFieldUnique("email", email)) {
                printError("Notice: The email is invalid or already exists. Please use a valid and unique email.");
                continue;
            }
            emailValid = true;
        }

        if (firstNameValid) cout << "Enter First Name: " << firstName << endl;
        else {
            cout << "Enter First Name: ";
            getline(cin >> ws, firstName);
            if (firstName.empty()) {
                printError("Notice: First name cannot be empty. Please enter a valid first name.");
                continue;
            }
            firstNameValid = true;
        }

        if (lastNameValid) cout << "Enter Last Name: " << lastName << endl;
        else {
            cout << "Enter Last Name: ";
            getline(cin >> ws, lastName);
            if (lastName.empty()) {
                printError("Notice: Last name cannot be empty. Please enter a valid last name.");
                continue;
            }
            lastNameValid = true;
        }

        if (phoneNumberValid) cout << "Enter Phone Number: " << phoneNumber << endl;
        else {
            cout << "Enter Phone Number (10-15 digits): ";
            getline(cin >> ws, phoneNumber);
            if (!isPhoneNumberValid(phoneNumber)) {
                printError("Notice: Phone number must be 10-15 digits long and contain only numbers. Please try again.");
                continue;
            }
            phoneNumberValid = true;
        }
    }

    // Insert data into the database
    string query = "INSERT INTO users (user_type, username, password, first_name, last_name, email, phone_number) "
        "VALUES ('Admin', '" + username + "', '" + password + "', '" + firstName + "', '" + lastName +
        "', '" + email + "', '" + phoneNumber + "')";

    qstate = mysql_query(conn, query.c_str());
    cout << string(120, '-') << endl;

    if (!qstate) {
        printSuccess("Admin registration successful!\n");
        showLoadingScreen("\033[32mRedirecting to main Page\033[0m");
        main(lecturerId, fullName); // Redirect
    }
    else {
        printError("Registration failed: " + string(mysql_error(conn)));
        cout << "Press Enter to retry registration...";
        (void)_getch();
        registerAdmin(lecturerId, fullName);
    }
}

void registerLecturer(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls");

    string username, password, firstName, lastName, email, phoneNumber;
    bool usernameValid = false, passwordValid = false, emailValid = false;
    bool firstNameValid = false, lastNameValid = false, phoneNumberValid = false;

    while (!usernameValid || !passwordValid || !emailValid || !firstNameValid || !lastNameValid || !phoneNumberValid) {
        system("cls");

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("LECTURER REGISTRATION PAGE", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Display previously validated inputs
        if (usernameValid) cout << "Enter Username: " << username << endl;
        else {
            cout << "Enter Username: ";
            getline(cin >> ws, username);
            if (username.empty() || !isFieldUnique("username", username)) {
                printError("Notice: The username is empty or already taken. Please choose another one.");
                continue;
            }
            usernameValid = true;
        }

        if (passwordValid) cout << "Enter Password (minimum 6 characters): " << string(password.length(), '*') << endl;
        else {
            cout << "Enter Password (minimum 6 characters):  ";
            password = ""; // Clear the password variable
            char ch;

            while ((ch = _getch()) != '\r') { // Press Enter to end input
                if (ch == '\b') { // Check if Backspace key is pressed
                    if (!password.empty()) {
                        password.pop_back(); // Remove the last character from the password
                        cout << "\b \b";     // Remove the last '*' from the console
                    }
                }
                else if (isprint(ch)) { // Check if input is a printable character
                    password += ch; // Add the character to the password
                    cout << '*';    // Display a '*'
                }
            }

            cout << endl; // Move to the next line after input

            if (password.empty() || password.length() < 6) {
                printError("Notice: Password must be at least 6 characters long. Please try again.");
                continue;
            }
            passwordValid = true; // Set flag to true once validation is passed
        }

        if (emailValid) cout << "Enter Email: " << email << endl;
        else {
            cout << "Enter Email: ";
            getline(cin >> ws, email);
            if (!isEmailValid(email) || !isFieldUnique("email", email)) {
                printError("Notice: The email is invalid or already exists. Please use a valid and unique email.");
                continue;
            }
            emailValid = true;
        }

        if (firstNameValid) cout << "Enter First Name: " << firstName << endl;
        else {
            cout << "Enter First Name: ";
            getline(cin >> ws, firstName);
            if (firstName.empty()) {
                printError("Notice: First name cannot be empty. Please enter a valid first name.");
                continue;
            }
            firstNameValid = true;
        }

        if (lastNameValid) cout << "Enter Last Name: " << lastName << endl;
        else {
            cout << "Enter Last Name: ";
            getline(cin >> ws, lastName);
            if (lastName.empty()) {
                printError("Notice: Last name cannot be empty. Please enter a valid last name.");
                continue;
            }
            lastNameValid = true;
        }

        if (phoneNumberValid) cout << "Enter Phone Number: " << phoneNumber << endl;
        else {
            cout << "Enter Phone Number (10-15 digits): ";
            getline(cin >> ws, phoneNumber);
            if (!isPhoneNumberValid(phoneNumber)) {
                printError("Notice: Phone number must be 10-15 digits long and contain only numbers. Please try again.");
                continue;
            }
            phoneNumberValid = true;
        }
    }

    // Insert data into the database
    string query = "INSERT INTO users (user_type, username, password, first_name, last_name, email, phone_number) "
        "VALUES ('Lecturer', '" + username + "', '" + password + "', '" + firstName + "', '" + lastName +
        "', '" + email + "', '" + phoneNumber + "')";

    qstate = mysql_query(conn, query.c_str());
    cout << string(120, '-') << endl;

    if (!qstate) {
        printSuccess("Lecturer registration successful!\n");
        showLoadingScreen("\033[32mRedirecting to main Page\033[0m");
        main(lecturerId, fullName); // Redirect
    }
    else {
        printError("Registration failed: " + string(mysql_error(conn)));
        cout << "Press Enter to retry registration...";
        (void)_getch();
        registerLecturer(lecturerId, fullName);
    }
}

// Implementation of Student registration page
// Student Registration Page
void registerStudent(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls");

    string username, password, firstName, lastName, email, phoneNumber;
    bool usernameValid = false, passwordValid = false, emailValid = false;
    bool firstNameValid = false, lastNameValid = false, phoneNumberValid = false;

    while (!usernameValid || !passwordValid || !emailValid || !firstNameValid || !lastNameValid || !phoneNumberValid) {
        system("cls");

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("STUDENT REGISTRATION PAGE", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Display previously validated inputs
        if (usernameValid) cout << "Enter Username: " << username << endl;
        else {
            cout << "Enter Username: ";
            getline(cin >> ws, username);
            if (username.empty() || !isFieldUnique("username", username)) {
                printError("Notice: The username is empty or already taken. Please choose another one.");
                continue;
            }
            usernameValid = true;
        }

          if (passwordValid) cout << "Enter Password (minimum 6 characters): " << string(password.length(), '*') << endl;
        else {
            cout << "Enter Password (minimum 6 characters):  ";
            password = ""; // Clear the password variable
            char ch;

            while ((ch = _getch()) != '\r') { // Press Enter to end input
                if (ch == '\b') { // Check if Backspace key is pressed
                    if (!password.empty()) {
                        password.pop_back(); // Remove the last character from the password
                        cout << "\b \b";     // Remove the last '*' from the console
                    }
                }
                else if (isprint(ch)) { // Check if input is a printable character
                    password += ch; // Add the character to the password
                    cout << '*';    // Display a '*'
                }
            }

            cout << endl; // Move to the next line after input

            if (password.empty() || password.length() < 6) {
                printError("Notice: Password must be at least 6 characters long. Please try again.");
                continue;
            }
            passwordValid = true; // Set flag to true once validation is passed
        }

        if (emailValid) cout << "Enter Email: " << email << endl;
        else {
            cout << "Enter Email: ";
            getline(cin >> ws, email);
            if (!isEmailValid(email) || !isFieldUnique("email", email)) {
                printError("Notice: The email is invalid or already exists. Please use a valid and unique email.");
                continue;
            }
            emailValid = true;
        }

        if (firstNameValid) cout << "Enter First Name: " << firstName << endl;
        else {
            cout << "Enter First Name: ";
            getline(cin >> ws, firstName);
            if (firstName.empty()) {
                printError("Notice: First name cannot be empty. Please enter a valid first name.");
                continue;
            }
            firstNameValid = true;
        }

        if (lastNameValid) cout << "Enter Last Name: " << lastName << endl;
        else {
            cout << "Enter Last Name: ";
            getline(cin >> ws, lastName);
            if (lastName.empty()) {
                printError("Notice: Last name cannot be empty. Please enter a valid last name.");
                continue;
            }
            lastNameValid = true;
        }

        if (phoneNumberValid) cout << "Enter Phone Number: " << phoneNumber << endl;
        else {
            cout << "Enter Phone Number (10-15 digits): ";
            getline(cin >> ws, phoneNumber);
            if (!isPhoneNumberValid(phoneNumber)) {
                printError("Notice: Phone number must be 10-15 digits long and contain only numbers. Please try again.");
                continue;
            }
            phoneNumberValid = true;
        }
    }

    // Insert the student data into the database
    string query = "INSERT INTO users (user_type, username, password, first_name, last_name, email, phone_number) "
        "VALUES ('Student', '" + username + "', '" + password + "', '" + firstName + "', '" + lastName +
        "', '" + email + "', '" + phoneNumber + "')";

    qstate = mysql_query(conn, query.c_str());
    cout << string(120, '-') << endl;

    if (!qstate) {
        printSuccess("Student registration successful!\n");
        showLoadingScreen("\033[32mRedirecting to main Page\033[0m");
        main(lecturerId, fullName); // Redirect
    }
    else {
        printError("Registration failed: " + string(mysql_error(conn)));
        cout << "Press Enter to retry registration...";
        (void)_getch();
        registerStudent(lecturerId, fullName);
    }
}

void login(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string username;
    string password = ""; // Initialize as an empty string
    char ch; // Character for reading user input
    bool loginSuccess = false;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("LOGIN PAGE", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << "  Please enter your login details below" << endl;
    cout << string(120, '-') << endl;
    cout << "  Enter Username: ";
    cin.ignore(); // Clear the newline character from the buffer
    getline(cin, username);
    cout << "  Enter Password: ";

    // Mask password input with '*'
    while (true) {
        ch = _getch(); // Read a character without echoing to the console
        if (ch == 13) { // Enter key (ASCII code 13)
            break; // Stop when Enter is pressed
        }
        else if (ch == 8) { // Backspace key (ASCII code 8)
            if (!password.empty()) {
                password.pop_back(); // Remove the last character from password
                cout << "\b \b"; // Move the cursor back, print a space, and move back again
            }
        }
        else {
            password += ch; // Append the character to the password
            cout << '*'; // Display '*' in place of the character
        }
    }

    cout << endl;
    cout << string(120, '-') << endl;
    cout << endl;

    // Query to check the credentials and retrieve user details
    string query = "SELECT user_type, first_name, last_name, user_id FROM users LEFT JOIN students ON users.user_id = students.student_id "
        "WHERE username = '" + username + "' AND password = '" + password + "'";

    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            row = mysql_fetch_row(res);
            string userType = row[0];    // Get user type
            string firstName = row[1];  // Get first name
            string lastName = row[2];   // Get last name
            string fullName = firstName + " " + lastName;
            int studentId = (row[3] != nullptr) ? stoi(row[3]) : -1; // Get student_id or set -1 if NULL
            int lecturerId = (row[3] != nullptr) ? stoi(row[3]) : -1; // Get student_id or set -1 if NULL
            loginSuccess = true;

            showLoadingScreen("\033[32mLogin successful!Redirecting to your dashboard\033[0m");

            // Redirect to the corresponding dashboard
            if (userType == "admin") {
                adminPage(lecturerId, fullName); // Pass full name to Admin page
            }
            else if (userType == "lecturer") {
                // lecturerPage(fullName); // Pass full name to Lecturer page
                lecturerPage(lecturerId, fullName);
                return;
            }
            else if (userType == "student") {
                studentPage(fullName, studentId, lecturerId); // Pass full name and student_id to Student page
            }
        }
        else {
            cout << "\033[31m\nInvalid username or password. Please try again.\033[0m" << endl;
            (void)_getch();
            main(lecturerId, fullName);
        }
    }
    else {
        cout << "\nQuery Execution Problem: " << mysql_error(conn) << endl;
    }

    if (!loginSuccess) {
        cout << "\nLogin failed. Press Enter to return to the main menu..." << endl;
        (void)_getch();
        system("cls");
    }
}

void adminPage(int lecturerId, const string& fullName) {
    int choice;
    while (true) {
        //showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen
        cout << string(120, '=') << endl; // Top border  
        int width = static_cast<int>((120 - 38) / 2 + 5); // Ensure calculations are within integer range
        cout << setw(width) << "" << "ADMIN DASHBOARD" << endl;// Centered title
        cout << string(120, '=') << endl; // Bottom border
        cout << "\nWelcome, " << fullName << "!" << endl; // Welcome message
        cout << string(120, '-') << endl; // Separator line
        cout << "1. Manage Student and Lecturer Accounts" << endl;
        cout << "2. Set Course into the System" << endl;
        cout << "3. Assign Course for Student" << endl;
        cout << "4. Assign Major and Enrollment Year" << endl;
        cout << "5. Assign Department for Lecturer" << endl;
        cout << "6. Assign Course for Lecturer" << endl;
        cout << "7. Set Grade Score With Marks" << endl;
        cout << "8. View Information" << endl;
        cout << "9. Logout and Return to Main Page" << endl;
        cout << string(120, '-') << endl; // Separator line
        cout << "Please enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear buffer after numeric input

        switch (choice) {
        case 1:
            manageAccounts(lecturerId, fullName); // Function to manage student and lecturer accounts
            break;
        case 2:
            setCourse(lecturerId, fullName); // Function to set courses into the system
            break;
        case 3:
            assignCourseForStudent(lecturerId, fullName);
            break;
        case 4:
            assignStudentMajorAndYear(lecturerId, fullName);
            break;
        case 5:
            assignDepartmentToLecturer(lecturerId, fullName);
            break;

        case 6:
            assignCoursesToLecturer(lecturerId, fullName);
            break;
        case 7:
            setGradeRanges(lecturerId, fullName);
            break;
        case 8:
            viewInformation(lecturerId, fullName); // Function to view student and lecturer account details
            break;
        case 9:
            //cout << "Logging out...\n";
            showLoadingScreen("\033[32mLogging out... Please wait.\033[0m");
            main(lecturerId, fullName);

        default:
            cout << "Invalid choice. Please try again." << endl;
            (void)_getch();
            adminPage(lecturerId, fullName);
            continue;
        }

    }
}

/*void RedirectToMainMenu(); {
          system("cls");
          cout << "Redirecting to the main menu..." << endl;
          std::this_thread::sleep_for(std::chrono::seconds(1));
          login(lecturerId,fullName); // Redirect back to the login screen
      }*/
void viewGradeRanges(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    // Title for the view
    cout << string(120, '=') << endl;
    cout << setw((120 - 22) / 2) << "" << "VIEW GRADE RANGES" << endl;
    cout << string(120, '=') << endl;

    // SQL query to fetch grade ranges
    const char* query = R"(
        SELECT 
            grade_id,
            grade, 
            min_score, 
            max_score 
        FROM 
            grade_definitions;
    )";

    // Execute the query
    qstate = mysql_query(conn, query);
    if (qstate) {
        cerr << "Query execution failed: " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        cerr << "Failed to retrieve query result: " << mysql_error(conn) << endl;
        return;
    }

    // Display grade ranges in a new format
    cout << left << setw(20) << "Grade ID" << setw(20) << "Grade"
        << setw(20) << "Min Score" << "Max Score" << endl;
    cout << string(120, '-') << endl;

    while ((row = mysql_fetch_row(res))) {
        cout << left << setw(20) << row[0]  // Grade ID
            << setw(20) << row[1]          // Grade
            << setw(20) << row[2]          // Min Score
            << row[3] << endl;            // Max Score
    }

    mysql_free_result(res);

}

// Function to view and manage grade ranges
void viewGradeRanges1(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW GRADE RANGES", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // SQL query to fetch grade ranges
    const char* query = R"(
        SELECT 
            grade_id,
            grade, 
            min_score, 
            max_score 
        FROM 
            grade_definitions;
    )";

    // Execute the query
    qstate = mysql_query(conn, query);
    if (qstate) {
        cerr << "Query execution failed: " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        cerr << "Failed to retrieve query result: " << mysql_error(conn) << endl;
        return;
    }

    ofstream outFile;
    bool saveToFile = false;
    char saveChoice;

    // Display grade ranges in a table format
    cout << left << setw(20) << "Grade ID" << setw(20) << "Grade"
        << setw(20) << "Min Score" << "Max Score" << endl;
    cout << string(120, '-') << endl;

    outFile.open("grade_ranges.txt");
    outFile << left << setw(20) << "Grade ID" << setw(20) << "Grade"
        << setw(20) << "Min Score" << "Max Score" << endl;
    outFile << string(120, '-') << endl;

    while ((row = mysql_fetch_row(res))) {
        cout << left << setw(20) << row[0]  // Grade ID
            << setw(20) << row[1]          // Grade
            << setw(20) << row[2]          // Min Score
            << row[3] << endl;             // Max Score

        outFile << left << setw(20) << row[0]  // Grade ID
            << setw(20) << row[1]          // Grade
            << setw(20) << row[2]          // Min Score
            << row[3] << endl;             // Max Score
    }
    printLine();
    outFile.close();

    mysql_free_result(res);

    cout << "\nWould you like to save the data into a file? (y/n): ";
    cin >> saveChoice;

    if (tolower(saveChoice) == 'y') {
        saveToFile = true;
        cout << "Data has been saved to 'grade_ranges.txt'." << endl;
    }

    cout << "Please press any key to continue to the previous page..." << endl;
    (void)_getch();
    viewInformation(lecturerId, fullName);
}

void assignDepartmentToLecturer(int lecturerId, const string& fullName) {
    char continueAssign = 'y';
    do {
        system("cls"); // Clear the screen

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("ASSIGN DEPARTMENT TO LECTURER", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Step 1: Display available lecturers who have not been assigned a department
        cout << "\nAvailable Lecturers (Not Assigned to Any Department):\n";
        printLine();
        cout << left << setw(15) << "Lecturer ID" << setw(30) << "Lecturer Name" << endl;
        cout << string(consoleWidth, '-') << endl;

        // Query to fetch lecturers without an assigned department
        string query =
            "SELECT u.user_id, CONCAT(u.first_name, ' ', u.last_name) AS lecturer_name "
            "FROM users u "
            "WHERE u.user_type = 'lecturer' AND NOT EXISTS ("
            "    SELECT 1 FROM department d WHERE d.lecturer_id = u.user_id"
            ")";

        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(15) << row[0]   // Lecturer ID
                        << setw(30) << row[1] << endl; // Lecturer Name
                }
                cout << string(consoleWidth, '-') << endl;

                // Step 2: Input Lecturer ID
                string lecturerId1;
                cout << "Enter Lecturer ID to assign a department: ";
                cin >> lecturerId1;

                // Step 3: Display Academic Departments
                cout << "\nAcademic Departments:\n";
                printLine();
                cout << left << setw(5) << "No." << setw(10) << "Code" << setw(50) << "Department Name" << endl;
                cout << string(consoleWidth, '-') << endl;

                // List of Academic Departments
                vector<pair<string, string>> departments = {
                    {"FST", "Faculty of Science and Technology "},
                    {"FKP", "Faculty of Entrepreneurship and Business "},
                    {"FKE", "Faculty of Electrical Engineering "},
                    {"FKM", "Faculty of Mechanical Engineering "},
                    {"FKAB", "Faculty of Civil and Environmental Engineering "},
                    {"FOM", "Faculty of Medicine "},
                    {"FSK", "Faculty of Health Sciences "},
                    {"FBMK", "Faculty of Language and Communication "},
                    {"FKOM", "Faculty of Computer Science and Information Technology"},
                    {"FPPSM", "Faculty of Management and Human Resource Development "}
                };

                // Display departments
                for (size_t i = 0; i < departments.size(); ++i) {
                    cout << left << setw(5) << (i + 1) // Department number
                        << setw(10) << departments[i].first
                        << setw(50) << departments[i].second << endl;
                }
                cout << string(consoleWidth, '-') << endl;

                // Step 4: Input Department Number
                int departmentNumber;
                cout << "Enter Department Number to assign: ";
                cin >> departmentNumber;

                // Step 5: Validate and Assign Department
                if (departmentNumber >= 1 && departmentNumber <= departments.size()) {
                    // Get selected department details
                    string departmentCode = departments[departmentNumber - 1].first;
                    string departmentName = departments[departmentNumber - 1].second;

                    // Corrected SQL query
                    string assignQuery = "INSERT INTO department (department_name, lecturer_id, department_short_name) "
                        "VALUES ('" + departmentName + "', " + lecturerId1 + ", '" + departmentCode + "')";
                    qstate = mysql_query(conn, assignQuery.c_str());

                    if (!qstate) {
                        cout << "\033[32mSuccessfully assigned Department '" << departmentName
                            << "' to Lecturer ID: " << lecturerId1 << "!\033[0m" << endl;
                    }
                    else {
                        cout << "\033[31mError assigning department: " << mysql_error(conn) << "\033[0m" << endl;
                    }
                }
                else {
                    cout << "\033[33mInvalid Department Number entered: " << departmentNumber << ".\033[0m" << endl;
                }

            }
            else {
                cout << "\033[33mAll lecturers have been assigned to departments.\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mError fetching lecturers: " << mysql_error(conn) << "\033[0m" << endl;
        }

        // Prompt to continue assigning
        cout << "\nWould you like to assign another lecturer? (y/n): ";
        cin >> continueAssign;

    } while (tolower(continueAssign) == 'y'); // Continue if the admin enters 'y'

    cout << "\nReturning to Admin Dashboard...\n\n";
    showLoadingScreen("Please Wait....");
    adminPage(lecturerId, fullName);
}


// Similar modifications for other functions
void assignCoursesToLecturer(int lecturerId, const string& fullName) {
    while (true) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen

        int lecturerId, courseId;
        string lecturerName, courseName;

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("ASSIGN COURSES TO LECTURER", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Query: Get the list of lecturers with their departments
        cout << "\nLecturer Details:\n";
        cout << string(120, '-') << endl;
        cout << left << setw(10) << "User ID"
            << setw(30) << "Full Name"
            << setw(15) << "Dept Code"
            << setw(40) << "Dept Name" << endl;
        cout << string(120, '-') << endl;


        string lecturerQuery =
            "SELECT u.user_id, CONCAT(u.first_name, ' ', u.last_name) AS name, "
            "d.department_short_name, d.department_name "
            "FROM users u "
            "LEFT JOIN department d ON u.user_id = d.lecturer_id "
            "WHERE u.user_type = 'lecturer'";

        qstate = mysql_query(conn, lecturerQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]   // User ID
                    << setw(30) << row[1]          // Full Name
                    << setw(15) << (row[2] ? row[2] : "N/A")  // Dept Code
                    << setw(40) << (row[3] ? row[3] : "N/A")  // Dept Name
                    << endl;
            }
        }
        else {
            cout << "\nError retrieving lecturers: " << mysql_error(conn) << endl;
            return;
        }

        cout << string(120, '-') << endl;
        cout << "Enter the lecturer's ID: ";
        cin >> lecturerId;
        cin.ignore();


        // Get the lecturer name
        lecturerName = ""; // Default empty
        string lecturerNameQuery = "SELECT CONCAT(first_name, ' ', last_name) FROM users WHERE user_id = " + to_string(lecturerId);
        qstate = mysql_query(conn, lecturerNameQuery.c_str());
        if (!qstate) {
            res = mysql_store_result(conn);
            if ((row = mysql_fetch_row(res))) {
                lecturerName = row[0];
            }
        }

        if (lecturerName.empty()) {
            cout << "\nInvalid Lecturer ID. Returning to main menu...\n";
            return;
        }

        // Query: Get available courses for the lecturer
        cout << "\nAvailable Courses:\n";
        cout << string(120, '-') << endl;
        cout << left << setw(20) << "Course ID"
            << setw(40) << "Course Name" << endl;
        cout << string(120, '-') << endl;

        string courseQuery =
            "SELECT c.course_id, c.course_name "
            "FROM courses c "
            "WHERE c.course_id NOT IN ("
            "    SELECT course_id "
            "    FROM course_lecturer "
            "    WHERE lecturer_id = " + to_string(lecturerId) +
            ")";

        qstate = mysql_query(conn, courseQuery.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(20) << row[0]  // Course ID
                        << setw(40) << row[1] << endl; // Course Name
                }
            }
            else {
                cout << "\033[33mNo available courses to assign for this lecturer.\033[0m" << endl;
            }
        }
        else {
            cout << "\nError retrieving courses: " << mysql_error(conn) << endl;
            return;
        }

        cout << string(120, '-') << endl;

        cout << "Enter the course ID to assign: ";
        cin >> courseId;
        cin.ignore();

        // Get course name
        courseName = "";
        string courseNameQuery = "SELECT course_name FROM courses WHERE course_id = " + to_string(courseId);
        qstate = mysql_query(conn, courseNameQuery.c_str());
        if (!qstate) {
            res = mysql_store_result(conn);
            if ((row = mysql_fetch_row(res))) {
                courseName = row[0];
            }
        }

        if (courseName.empty()) {
            cout << "\nInvalid Course ID. Returning to main menu...\n";
            return;
        }

        // Assign course to lecturer
        string assignQuery = "INSERT INTO course_lecturer (course_id, lecturer_id) VALUES (" + to_string(courseId) + ", " + to_string(lecturerId) + ")";
        qstate = mysql_query(conn, assignQuery.c_str());

        if (!qstate) {
            cout << "\nAssignment Details:\n";
            cout << string(120, '-') << endl;
            cout << left << setw(15) << "Lecturer Name"
                << setw(40) << "Assigned Course" << endl;
            cout << string(120, '-') << endl;
            cout << left << setw(15) << lecturerName
                << setw(40) << courseName << endl;
            cout << string(120, '-') << endl;
            cout << "\nStatus: Assignment Successful!" << endl;
        }
        else {
            cout << "\nError assigning course: " << mysql_error(conn) << endl;
            return;
        }

        // Ask if the admin wants to assign another course
        char choice;
        cout << "\nDo you want to assign another course? (Y/N): ";
        cin >> choice;
        cin.ignore();
        if (tolower(choice) != 'y') {
            adminPage(lecturerId, fullName);
        }
        if (tolower(choice) == 'n' || tolower(choice) == 'N') {
            adminPage(lecturerId, fullName);
        }
    }
}

// Function to manage student accounts
void manageStudentAccounts(int lecturerId, const string& fullName) {
    while (true) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("STUDENT ACCOUNT MANAGEMENT", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        int choice;
        cout << "1. View All Students" << endl;
        cout << "2. Edit Student Account" << endl;
        cout << "3. Delete Student Account" << endl;
        cout << "4. Search Student Account" << endl;
        cout << "5. Return to User Management" << endl;
        cout << string(120, '-') << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewAllStudents(lecturerId, fullName);
            break;
        case 2:
            editStudentAccount(lecturerId, fullName);
            break;
        case 3:
            deleteStudentAccount(lecturerId, fullName);
            break;
        case 4:
            searchStudentAccount(lecturerId, fullName);
            break;
        case 5:
            manageAccounts(lecturerId, fullName);
            return; // Exit to previous menu
        default:
            cout << "Invalid choice. Please try again." << endl;
            (void)_getch();
            break;
        }
    }
}
// Function to manage student and lecturer accounts
void manageAccounts(int lecturerId, const string& fullName) {
    while (true) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("MANAGEMENT USER", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        int chViewInformation;
        cout << "1. Manage Student Account " << endl;
        cout << "2. Manage Lecturer Account" << endl;
        cout << "3. Return To Admin Page" << endl;
        cout << string(120, '-') << endl;
        cout << "Please enter your choice: ";
        cin >> chViewInformation;

        switch (chViewInformation) {
        case 1:
            manageStudentAccounts(lecturerId, fullName); // Manage student accounts
            break;
        case 2:
            manageLecturerAccounts(lecturerId, fullName); // Manage lecturer accounts
            break;
        case 3:
            adminPage(lecturerId, fullName); // Return to Admin Page
            return; // Exit the loop
        default:
            cout << "Invalid choice. Please try again." << endl;
            (void)_getch();
            break;
        }
    }
}

void setGradeRanges(int lecturerId, const string& fullName) {
    int grade_id;
    string grade;
    int min_score, max_score;
    char choice1 = 'n';

    // Define valid grade range
    const vector<string> validGrades = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-" };

    do {
        // Display current grade ranges
        viewGradeRanges(lecturerId, fullName);

        // Print title
        const int consoleWidth = 120;
        cout << string(consoleWidth, '=') << endl;
        printCentered("SET GRADE RANGES", consoleWidth);
        cout << string(consoleWidth, '=') << endl;

        // Prompt user to enter Grade ID
        cout << "Enter Grade ID to update (or 0 to add new, -1 to exit): ";
        cin >> grade_id;

        // Validate input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            printWarning("Invalid input! Please enter a numeric value for Grade ID.");
            continue;
        }

        // Check if user chose to exit
        if (grade_id == -1) {
            cout << "Exiting grade range setting..." << endl;
            break;
        }

        // If user chooses to add a new range
        if (grade_id == 0) {
            while (true) {
                cout << "Enter New Grade (e.g., A+, A, B): ";
                cin >> grade;

                // Check if the entered grade is valid
                if (find(validGrades.begin(), validGrades.end(), grade) == validGrades.end()) {
                    printWarning("Invalid grade! Please enter a valid grade (e.g., A+, A, B).");
                    continue; // Go back to entering grade
                }

                // Check if grade already exists
                string gradeCheckQuery = "SELECT * FROM grade_definitions WHERE grade = '" + grade + "'";
                qstate = mysql_query(conn, gradeCheckQuery.c_str());
                if (!qstate) {
                    MYSQL_RES* res = mysql_store_result(conn);
                    if (res && mysql_num_rows(res) > 0) {
                        printWarning("Notes: The grade '" + grade + "' already exists. Please enter a different grade.");
                        mysql_free_result(res);
                        continue; // Go back to entering grade
                    }
                    mysql_free_result(res);
                }
                else {
                    cout << "Query execution failed: " << mysql_error(conn) << endl;
                    continue; // Go back to entering grade
                }

                break; // Input is valid and not duplicate, exit loop
            }
        }

        bool validInput = false; // Add a flag variable to ensure valid input
        while (!validInput) {   // Internal loop for handling score input
            // Enter minimum score
            cout << "Enter Minimum Score: ";
            cin >> min_score;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                printWarning("Invalid input! Please enter a numeric value for Minimum Score.");
                continue; // Go back to "Enter Minimum Score"
            }

            // Enter maximum score
            cout << "Enter Maximum Score: ";
            cin >> max_score;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                printWarning("Invalid input! Please enter a numeric value for Maximum Score.");
                continue; // Go back to "Enter Minimum Score"
            }

            // Check if minimum score is greater than maximum score
            if (min_score > max_score) {
                printWarning("Notes: Minimum score cannot be greater than Maximum score.");
                continue; // Go back to "Enter Minimum Score"
            }

            // Check if the score range overlaps
            string checkQuery = "SELECT * FROM grade_definitions WHERE "
                "(min_score <= " + to_string(max_score) + " AND max_score >= " + to_string(min_score) + ")";

            qstate = mysql_query(conn, checkQuery.c_str());
            if (!qstate) {
                MYSQL_RES* res = mysql_store_result(conn);
                if (res && mysql_num_rows(res) > 0) {
                    printWarning("Notes: The score range overlaps with an existing range. Please adjust the scores.");

                    // Print conflicting rows (debugging information)
                    MYSQL_ROW row;
                    while ((row = mysql_fetch_row(res))) {
                        // Construct the warning message with overlapping range details
                        string warningMessage = "Overlapping range: Grade ID " + string(row[0]) +
                            ", Min Score: " + string(row[2]) +
                            ", Max Score: " + string(row[3]);

                        // Use printWarning to display the message in yellow color
                        printWarning(warningMessage);
                    }

                    mysql_free_result(res);
                    continue; // Go back to "Enter Minimum Score"
                }
                mysql_free_result(res);
            }
            else {
                cout << "Query execution failed: " << mysql_error(conn) << endl;
                continue; // Go back to "Enter Minimum Score"
            }

            // If input is valid and no conflicts, exit loop
            validInput = true;
        }

        // Construct insert or update query
        string query;
        if (grade_id == 0) {
            query = "INSERT INTO grade_definitions (grade, min_score, max_score) VALUES ('" +
                grade + "', " + to_string(min_score) + ", " + to_string(max_score) + ");";
        }
        else {
            query = "UPDATE grade_definitions SET min_score=" + to_string(min_score) +
                ", max_score=" + to_string(max_score) + " WHERE grade_id=" + to_string(grade_id) + ";";
        }

        // Execute query
        qstate = mysql_query(conn, query.c_str());
        if (qstate) {
            cout << "Query execution failed: " << mysql_error(conn) << endl;
            continue;
        }
        else {
            printSuccess("Grade range has been successfully set.");
            viewGradeRanges(lecturerId, fullName); // Display the updated table
        }

        // Prompt user if they want to continue
        cout << "Do you want to enter another grade range? (y/n): ";
        cin >> choice1;

        // Validate input
        while (choice1 != 'y' && choice1 != 'Y' && choice1 != 'n' && choice1 != 'N') {
            printWarning("Invalid input! Please enter 'y' to continue or 'n' to exit: ");
            cin >> choice1;
        }

    } while (choice1 == 'y' || choice1 == 'Y');

    // Return to admin page upon completion
    adminPage(lecturerId, fullName);
}


// Function to manage lecturer accounts
void manageLecturerAccounts(int lecturerId, const string& fullName) {
    while (true) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("LECTURER ACCOUNT MANAGEMENT", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        int choice;
        cout << "1. View All Lecturers" << endl;
        cout << "2. Edit Lecturer Account" << endl;
        cout << "3. Delete Lecturer Account" << endl;
        cout << "4. Search Lecturer Account" << endl;
        cout << "5. Return to User Management" << endl;
        cout << string(120, '-') << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewAllLecturers(lecturerId, fullName);
            break;
        case 2:
            editLecturerAccount(lecturerId, fullName);
            break;
        case 3:
            deleteLecturerAccount(lecturerId, fullName);
            break;
        case 4:
            searchLecturerAccount(lecturerId, fullName);
            break;
        case 5:
            manageAccounts(lecturerId, fullName);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            (void)_getch();
            break;
        }
    }
}

void assignCourseForStudent(int lecturerId, const string& fullName) {
    while (true) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("ASSIGN COURSE FOR STUDENT", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Step 1: Display all available courses
        cout << "\nAvailable Courses:\n";
        cout << endl;
        cout << string(120, '-') << endl;

        string query = "SELECT course_id, course_code, course_name, credits FROM courses";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                // Display course details
                cout << left << setw(20) << "Course ID" << setw(20) << "Course Code"
                    << setw(50) << "Course Name" << "Credits" << endl;
                cout << string(120, '-') << endl;
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(20) << row[0]  // Course ID
                        << setw(20) << row[1]          // Course Code
                        << setw(50) << row[2]          // Course Name
                        << row[3] << endl;             // Credits
                }
                cout << string(120, '-') << endl;

                // Step 2: Prompt admin to select a course
                string courseId;
                cout << "\nEnter the Course ID to manage assignments (or type 'exit' to return): ";
                cin >> courseId;
                if (courseId == "exit") {
                    adminPage(lecturerId, fullName);
                }

                // Step 3: Proceed to manage student assignments for the selected course
                manageStudentAssignments(courseId, fullName, lecturerId);
            }
            else {
                cout << "\033[33mNo courses found in the system.\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mError retrieving courses: " << mysql_error(conn) << "\033[0m" << endl;
        }

        cout << "\nPress any key to return to the Assign Course page...";
        (void)_getch();
    }
}

void manageStudentAssignments(const string& courseId, const string& fullname, int lecturerId) {
    while (true) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("MANAGE STUDENT ASSIGNMENTS", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Step 1: Display students not assigned to the course
        cout << "\nStudents Not Assigned to Course:\n";
        cout << string(120, '-') << endl;
        cout << endl;
        string query = "SELECT u.user_id, u.first_name, u.last_name, u.email "
            "FROM users u "
            "WHERE u.user_type = 'student' AND NOT EXISTS "
            "(SELECT 1 FROM scores s WHERE s.student_id = u.user_id AND s.course_id = " + courseId + ")";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                // Display unassigned students
                cout << left << setw(10) << "User ID" << setw(20) << "First Name"
                    << setw(20) << "Last Name" << "Email" << endl;
                cout << string(120, '-') << endl;
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(10) << row[0]  // User ID
                        << setw(20) << row[1]          // First Name
                        << setw(20) << row[2]          // Last Name
                        << row[3] << endl;             // Email
                }
                cout << string(120, '-') << endl;

                // Step 2: Prompt admin to assign a student
                string studentId;
                cout << "\nEnter the Student ID to assign to the course (or type 'exit' to return): ";
                cin >> studentId;
                if (studentId == "exit") return; // Exit back to course selection

                // Insert assignment into the scores table
                query = "INSERT INTO scores (student_id, course_id) "
                    "VALUES (" + studentId + ", " + courseId + ")";
                qstate = mysql_query(conn, query.c_str());
                if (!qstate) {
                    cout << "\033[32mStudent assigned to course successfully!\033[0m" << endl;
                }
                else {
                    cout << "\033[31mError assigning student to course: " << mysql_error(conn) << "\033[0m" << endl;
                }

                // Step 3: View assigned students
                viewAssignedStudents(courseId);

                // Ask admin if they want to assign another student
                char choice;
                cout << "\nDo you want to assign another student? (Y/N): ";
                cin >> choice;
                if (tolower(choice) != 'y') {
                    adminPage(lecturerId, fullname);
                }
            }
            else {
                cout << "\033[33mAll students are already assigned to this course.\033[0m" << endl;
                return;
            }
        }
        else {
            cout << "\033[31mError retrieving unassigned students: " << mysql_error(conn) << "\033[0m" << endl;
        }
    }
}

void viewAssignedStudents(const string& courseId) {

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("STUDENTS ASSIGNED TO COURSE", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;
    // cout << "\nStudents Assigned to Course:\n";
    printLine();
    string query = "SELECT u.user_id, u.first_name, u.last_name, u.email "
        "FROM users u "
        "JOIN scores s ON u.user_id = s.student_id "
        "WHERE s.course_id = " + courseId;
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Display assigned students
            cout << left << setw(10) << "User ID" << setw(20) << "First Name"
                << setw(20) << "Last Name" << "Email" << endl;
            cout << string(120, '-') << endl;
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(20) << row[1]          // First Name
                    << setw(20) << row[2]          // Last Name
                    << row[3] << endl;             // Email
            }
            cout << string(120, '-') << endl;
        }
        else {
            cout << "\033[33mNo students are assigned to this course yet.\033[0m" << endl;
        }
    }
    else {
        cout << "\033[31mError retrieving assigned students: " << mysql_error(conn) << "\033[0m" << endl;
    }
}

void clearInputBuffer() {
    cin.clear(); // Clear any error flags
    cin.ignore(10000, '\n'); // Ignore up to 10,000 characters or until newline
}
void assignStudentMajorAndYear(int lecturerId, const string& fullName) {
    while (true) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen

        string studentId, major, matrixNumber;
        int enrollmentYear;
        int majorChoice;

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("ASSIGN MAJOR AND ENROLLMENT YEAR", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Query: Get unassigned students
        string query = "SELECT u.user_id, u.first_name, u.last_name, u.email "
            "FROM users u "
            "LEFT JOIN students s ON u.user_id = s.student_id "
            "WHERE u.user_type = 'student' AND s.student_id IS NULL";
        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                // Display Student List
                cout << left << setw(10) << "User ID"
                    << setw(20) << "First Name"
                    << setw(20) << "Last Name"
                    << setw(30) << "Email" << endl;
                cout << string(120, '-') << endl;

                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(10) << row[0]  // User ID
                        << setw(20) << row[1]          // First Name
                        << setw(20) << row[2]          // Last Name
                        << setw(30) << row[3] << endl; // Email
                }
            }
            else {
                cout << "No unassigned students found.\n";
                cout << "\nPress any key to return to Admin Page...";
                (void)_getch();
                adminPage(lecturerId, fullName);
                return;
            }
        }
        else {
            cout << "Error retrieving unassigned students: " << mysql_error(conn) << endl;
            cout << "\nPress any key to return...";
            (void)_getch();
            return;
        }

        // Prompt admin to select a student
        cout << string(120, '=') << endl;
        cout << "Enter the Student ID to assign (or type 'exit' to return): ";
        cin.clear(); // Clear input buffer
        getline(cin, studentId);

        if (studentId == "exit") {
            adminPage(lecturerId, fullName);
            return;
        }

        // Display Major Options
        cout << "\nSelect a Major from the following list:\n";
        cout << string(120, '-') << endl;
        string majors[] = {
            "Business Administration", "Accounting and Finance", "Computer Science",
            "Software Engineering", "Information Technology", "Mechanical Engineering",
            "Civil Engineering", "Electrical and Electronic Engineering", "Medicine",
            "Nursing", "Pharmacy", "Psychology", "International Relations",
            "Economics", "Education", "Mass Communication", "Tourism and Hospitality Management",
            "Architecture", "Environmental Science", "Law", "Data Science",
            "Artificial Intelligence", "Cybersecurity", "Marketing",
            "International Business", "Logistics and Supply Chain Management", "Biomedical Science",
            "Biotechnology", "Food Science and Technology", "Physics", "Mathematics",
            "Chemistry", "Biology", "Environmental Engineering", "Graphic Design",
            "Film and Media Studies", "Animation and Game Design", "Political Science",
            "Sociology", "Human Resource Management"
        };

        for (int i = 0; i < 40; ++i) {
            cout << "(" << i + 1 << ") " << majors[i] << endl;
        }

        cout << string(120, '-') << endl;
        cout << "Enter the number corresponding to the Major: ";
        cin >> majorChoice;
        cin.ignore(); // Clear buffer

        if (majorChoice < 1 || majorChoice > 40) {
            cout << "Invalid choice. Please try again.\n";
            (void)_getch();
            continue;
        }

        major = majors[majorChoice - 1];

        // Input Enrollment Year
        cout << "Enter the Enrollment Year for the student: ";
        cin >> enrollmentYear;
        cin.ignore(); // Clear buffer again

        // Generate Matrix Number
        string yearSuffix = to_string(enrollmentYear).substr(2); // Get last two digits of the year
        string matrixQuery = "SELECT COUNT(*) FROM students WHERE enrollment_year = " + to_string(enrollmentYear);
        qstate = mysql_query(conn, matrixQuery.c_str());

        int matrixCount = 0;
        if (!qstate) {
            res = mysql_store_result(conn);
            if ((row = mysql_fetch_row(res))) {
                matrixCount = stoi(row[0]);
            }
        }
        matrixCount++; // Increment for the new student
        matrixNumber = "MAT" + yearSuffix + to_string(matrixCount);

        // Check if the student already exists in the `students` table
        string checkQuery = "SELECT * FROM students WHERE student_id = '" + studentId + "'";
        qstate = mysql_query(conn, checkQuery.c_str());
        res = mysql_store_result(conn);

        if (res->row_count > 0) {
            // Update existing record
            string updateQuery = "UPDATE students SET major = '" + major +
                "', enrollment_year = " + to_string(enrollmentYear) +
                ", matrix_number = '" + matrixNumber + "'"
                " WHERE student_id = '" + studentId + "'";
            qstate = mysql_query(conn, updateQuery.c_str());

            if (!qstate) {
                cout << "\033[32mStudent information updated successfully!\033[0m\n";
            }
            else {
                cout << "\033[31mError updating student information: " << mysql_error(conn) << "\033[0m\n";
            }
        }
        else {
            // Insert new record
            string insertQuery = "INSERT INTO students (student_id, major, enrollment_year, matrix_number) "
                "VALUES ('" + studentId + "', '" + major + "', " + to_string(enrollmentYear) + ", '" + matrixNumber + "')";
            qstate = mysql_query(conn, insertQuery.c_str());

            if (!qstate) {
                cout << "\033[32mStudent information assigned successfully!\033[0m\n";
            }
            else {
                cout << "\033[31mError assigning student information: " << mysql_error(conn) << "\033[0m\n";
            }
        }

        // Display Updated Information
        query = "SELECT s.student_id, u.first_name, u.last_name, s.major, s.enrollment_year, s.matrix_number "
            "FROM students s "
            "JOIN users u ON s.student_id = u.user_id "
            "WHERE s.student_id = '" + studentId + "'";
        qstate = mysql_query(conn, query.c_str());
        if (!qstate) {
            res = mysql_store_result(conn);
            if ((row = mysql_fetch_row(res))) {
                cout << "\nUpdated Student Information:\n";
                cout << string(120, '-') << endl;
                cout << left << setw(10) << "ID"
                    << setw(20) << "First Name"
                    << setw(20) << "Last Name"
                    << setw(30) << "Major"
                    << setw(20) << "Enrollment Year"
                    << setw(20) << "Matrix Number" << endl;
                cout << string(120, '-') << endl;
                cout << left << setw(10) << row[0]
                    << setw(20) << row[1]
                    << setw(20) << row[2]
                    << setw(30) << row[3]
                    << setw(20) << row[4]
                    << setw(20) << row[5] << endl;
                cout << string(120, '-') << endl;
            }
        }

        // Ask if the admin wants to assign another student
        char choice;
        cout << "\nDo you want to assign another student? (Y/N): ";
        cin >> choice;
        cin.ignore(); // Clear buffer
        if (tolower(choice) != 'y') {
            adminPage(lecturerId, fullName);
            return;
        }
    }
}

// Function to view all students
void viewAllStudents(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("ALL STUDENT ACCOUNTS", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Query records where user_type is 'student'
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'student'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Print the table header
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            // Vector to store data for potential download
            vector<string> studentData;

            // Print each row of data
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(20) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(25) << row[4]          // Email
                    << setw(15) << row[5] << endl; // Phone Number

                // Format row for file output
                ostringstream oss;
                oss << left << setw(10) << row[0]
                    << setw(15) << row[1]
                    << setw(20) << row[2]
                    << setw(15) << row[3]
                    << setw(25) << row[4]
                    << setw(15) << row[5] << endl;

                studentData.push_back(oss.str());
            }
            printLine();

            // Ask if the user wants to download the data
            cout << "\nDo you want to download the student data to a file? (Y/N): ";
            char choice;
            cin >> choice;
            if (tolower(choice) == 'y') {
                // Create and write to a file
                ofstream outFile("student_data.txt");
                if (outFile.is_open()) {
                    // Write table header
                    outFile << left << setw(10) << "User ID"
                        << setw(15) << "Username"
                        << setw(20) << "First Name"
                        << setw(15) << "Last Name"
                        << setw(25) << "Email"
                        << setw(15) << "Phone Number" << endl;
                    outFile << string(120, '-') << endl;

                    // Write student data
                    for (const string& line : studentData) {
                        outFile << line;
                    }
                    outFile.close();
                    printSuccess("Student data has been successfully downloaded to 'student_data.txt'.\n");
                }
                else {
                    cout << "Error: Unable to create file.\n";
                }
            }
        }
        else {
            cout << "No students found." << endl;
        }
    }
    else {
        cout << "Error retrieving students: " << mysql_error(conn) << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    manageStudentAccounts(lecturerId, fullName);
}


// Function to view all students
void viewAllStudentsinformation(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("ALL STUDENT ACCOUNTS", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Query records where user_type is 'student'
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'student'";
    qstate = mysql_query(conn, query.c_str());

    vector<vector<string>> studentData; // Store student data for file saving

    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0) {
            // Print the table header
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            // Print each row of data and store for saving
            while ((row = mysql_fetch_row(res))) {
                vector<string> rowData;
                for (int i = 0; i < 6; ++i) { // 6 columns: user_id, username, etc.
                    rowData.push_back(row[i] ? row[i] : "N/A");
                }
                studentData.push_back(rowData);

                cout << left << setw(10) << row[0]   // User ID
                    << setw(15) << row[1]           // Username
                    << setw(20) << row[2]           // First Name
                    << setw(15) << row[3]           // Last Name
                    << setw(25) << row[4]           // Email
                    << setw(15) << row[5] << endl;  // Phone Number
            }
            printLine();
        }
        else {
            cout << "No students found." << endl;
        }
    }
    else {
        cout << "Error retrieving students: " << mysql_error(conn) << endl;
    }

    // Ask user if they want to save the file
    char saveChoice;
    cout << "\nDo you want to save this information into a file? (Y/N): ";
    cin >> saveChoice;

    if (toupper(saveChoice) == 'Y') {
        ofstream outFile("students_list.txt");

        // Write table header
        outFile << left << setw(10) << "User ID"
            << setw(15) << "Username"
            << setw(20) << "First Name"
            << setw(15) << "Last Name"
            << setw(25) << "Email"
            << setw(15) << "Phone Number" << endl;
        outFile << string(120, '-') << endl;

        // Write student data to the file
        for (const auto& row : studentData) {
            outFile << left << setw(10) << row[0]   // User ID
                << setw(15) << row[1]           // Username
                << setw(20) << row[2]           // First Name
                << setw(15) << row[3]           // Last Name
                << setw(25) << row[4]           // Email
                << setw(15) << row[5] << endl;  // Phone Number
        }

        outFile.close();
        cout << "\033[32mStudent list saved successfully to 'students_list.txt'.\033[0m" << endl;
    }
    else {
        cout << "\nReturning to the previous menu..." << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    viewInformation(lecturerId, fullName); // Return to the main menu
}


// Function to view all lecturers
void viewAllLecturers(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("ALL LECTURER ACCOUNTS", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Query records where user_type is 'lecturer'
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'lecturer'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Print the table header
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            // Vector to store data for potential download
            vector<string> lecturerData;

            // Print each row of data
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(20) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(25) << row[4]          // Email
                    << setw(15) << row[5] << endl; // Phone Number

                // Format row for file output
                ostringstream oss;
                oss << left << setw(10) << row[0]
                    << setw(15) << row[1]
                    << setw(20) << row[2]
                    << setw(15) << row[3]
                    << setw(25) << row[4]
                    << setw(15) << row[5] << endl;

                lecturerData.push_back(oss.str());
            }
            printLine();

            // Ask if the user wants to download the data
            cout << "\nDo you want to download the lecturer data to a file? (Y/N): ";
            char choice;
            cin >> choice;
            if (tolower(choice) == 'y') {
                // Create and write to a file
                ofstream outFile("lecturer_data.txt");
                if (outFile.is_open()) {
                    // Write table header
                    outFile << left << setw(10) << "User ID"
                        << setw(15) << "Username"
                        << setw(20) << "First Name"
                        << setw(15) << "Last Name"
                        << setw(25) << "Email"
                        << setw(15) << "Phone Number" << endl;
                    outFile << string(120, '-') << endl;

                    // Write lecturer data
                    for (const string& line : lecturerData) {
                        outFile << line;
                    }
                    outFile.close();
                    printSuccess("Lecturer data has been successfully downloaded to 'lecturer_data.txt'.\n");
                }
                else {
                    cout << "Error: Unable to create file.\n";
                }
            }
        }
        else {
            cout << "No lecturers found." << endl;
        }
    }
    else {
        cout << "Error retrieving lecturers: " << mysql_error(conn) << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    manageLecturerAccounts(lecturerId, fullName);
}

// Function to view all lecturers

void viewAllLecturersinformation(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("ALL LECTURER ACCOUNTS", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Query records where user_type is 'lecturer'
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'lecturer'";
    qstate = mysql_query(conn, query.c_str());

    vector<vector<string>> lecturerData; // Store data for saving to file

    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Print the table header
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            // Print each row of data and store it in the vector
            while ((row = mysql_fetch_row(res))) {
                vector<string> rowData;
                for (int i = 0; i < 6; i++) { // 6 columns
                    rowData.push_back(row[i] ? row[i] : "N/A");
                }
                lecturerData.push_back(rowData);

                cout << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(20) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(25) << row[4]          // Email
                    << setw(15) << row[5] << endl; // Phone Number
            }
            printLine();
        }
        else {
            cout << "No lecturers found." << endl;
        }
    }
    else {
        cout << "Error retrieving lecturers: " << mysql_error(conn) << endl;
    }

    // Step: Ask to save into file
    char saveChoice;
    cout << "\nDo you want to save this information into a file? (Y/N): ";
    cin >> saveChoice;

    if (toupper(saveChoice) == 'Y') {
        ofstream outFile("lecturers_information.txt");

        // Write table header
        outFile << left << setw(10) << "User ID"
            << setw(15) << "Username"
            << setw(20) << "First Name"
            << setw(15) << "Last Name"
            << setw(25) << "Email"
            << setw(15) << "Phone Number" << endl;
        outFile << string(120, '-') << endl;

        // Write each row to the file
        for (const auto& row : lecturerData) {
            outFile << left << setw(10) << row[0]
                << setw(15) << row[1]
                << setw(20) << row[2]
                << setw(15) << row[3]
                << setw(25) << row[4]
                << setw(15) << row[5] << endl;
        }

        outFile.close();
        cout << "\033[32mLecturer information saved successfully to 'lecturers_information.txt'.\033[0m" << endl;
    }
    else {
        cout << "\nReturning to the previous page..." << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    viewInformation(lecturerId, fullName);
}
void editStudentAccount(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string userId, newFirstName, newLastName, newEmail, newPhoneNumber, newUsername, newPassword;
    int choice; // To capture the choice of what to edit
    int selectedOption = 0; // Track selected option: 0 = Yes, 1 = No
    char editAnother; // Variable to decide if the user wants to edit another student

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("EDIT STUDENT ACCOUNT", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;
    cout << endl;

    // Query records where user_type is 'student'
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'student'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            printLine();
            // Print the table header
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            // Print each row of data
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(20) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(25) << row[4]          // email
                    << setw(15) << row[5] << endl; // Phone Number
            }
            printLine();
        }
        else {
            cout << "No students found." << endl;
        }
    }
    else {
        cout << "Error retrieving students: " << mysql_error(conn) << endl;
    }
    cout << endl;

    do {
        // Get student ID
        cout << "Enter Student User ID to edit: ";
        cin.ignore(); // Clear any leftover input
        getline(cin, userId);

        // Check if the student exists
        string query = "SELECT * FROM users WHERE user_id = '" + userId + "' AND user_type = 'student'";
        qstate = mysql_query(conn, query.c_str());
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                // Ask what part the user wants to edit
                cout << string(120, '-');
                cout << "Which part of the student account would you like to edit?" << endl;
                cout << endl;
                cout << "1. First Name and Last Name" << endl;
                cout << "2. Email" << endl;
                cout << "3. Phone Number" << endl;
                cout << "4. Username" << endl;
                cout << "5. Password" << endl;
                cout << string(120, '-');
                cout << "Please Enter your choice (1-5): ";
                cin >> choice;
                cin.ignore(); // Clear the newline character left by cin
                cout << string(120, '-');
                // Based on the user's choice, update only the selected field
                switch (choice) {
                case 1:
                    // If the user chooses to edit both first name and last name
                    cout << "Enter New First Name: ";
                    getline(cin, newFirstName);
                    cout << endl;
                    cout << "Enter New Last Name: ";
                    getline(cin, newLastName);
                    query = "UPDATE users SET first_name = '" + newFirstName + "', last_name = '" + newLastName + "' WHERE user_id = '" + userId + "' AND user_type = 'student'";
                    break;
                case 2:
                    // Email update with uniqueness check
                    cout << "Enter New Email: ";
                    getline(cin, newEmail);

                    // Check if the new email already exists
                    query = "SELECT * FROM users WHERE email = '" + newEmail + "' AND user_id != '" + userId + "' AND user_type = 'student'";
                    qstate = mysql_query(conn, query.c_str());
                    if (!qstate) {
                        res = mysql_store_result(conn);
                        if (res->row_count > 0) {
                            cout << "\033[31mError: Email is already taken by another student.\033[0m" << endl;
                            return; // Return if email is not unique
                        }
                        else {
                            query = "UPDATE users SET email = '" + newEmail + "' WHERE user_id = '" + userId + "' AND user_type = 'student'";
                        }
                    }
                    break;
                case 3:
                    cout << "Enter New Phone Number: ";
                    getline(cin, newPhoneNumber);
                    query = "UPDATE users SET phone_number = '" + newPhoneNumber + "' WHERE user_id = '" + userId + "' AND user_type = 'student'";
                    break;
                case 4:
                    // Username update with uniqueness check
                    cout << "Enter New Username: ";
                    getline(cin, newUsername);

                    // Check if the new username already exists
                    query = "SELECT * FROM users WHERE username = '" + newUsername + "' AND user_id != '" + userId + "' AND user_type = 'student'";
                    qstate = mysql_query(conn, query.c_str());
                    if (!qstate) {
                        res = mysql_store_result(conn);
                        if (res->row_count > 0) {
                            cout << "\033[31mError: Username is already taken by another student.\033[0m" << endl;
                            return; // Return if username is not unique
                        }
                        else {
                            query = "UPDATE users SET username = '" + newUsername + "' WHERE user_id = '" + userId + "' AND user_type = 'student'";
                        }
                    }
                    break;
                case 5:
                    cout << "Enter New Password: ";
                    getline(cin, newPassword);
                    query = "UPDATE users SET password = '" + newPassword + "' WHERE user_id = '" + userId + "' AND user_type = 'student'";
                    break;
                default:
                    cout << "Invalid choice. Returning to menu." << endl;
                    return; // Exit if the user chooses an invalid option
                }

                // Execute the update query
                qstate = mysql_query(conn, query.c_str());
                if (!qstate) {
                    cout << "\033[32mStudent account updated successfully!\033[0m" << endl;
                }
                else {
                    cout << "\033[31mError updating student account: " << mysql_error(conn) << "\033[0m" << endl;
                }
            }
            else {
                cout << "\033[31mNo student found with User ID: " << userId << "\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
        }


        // Ask if the user wants to edit another student's account
        cout << "\nDo you want to edit another student's account? (Y/N): ";
        cin >> editAnother;
        cin.ignore(); // Clear any leftover newline character

    } while (editAnother == 'Y' || editAnother == 'y'); // Continue if the user chooses 'Y'

    // After finishing all edits, return to the manageStudentAccounts page


    // After the user presses a key, return to the manageStudentAccounts function
    manageStudentAccounts(lecturerId, fullName);
}

void deleteStudentAccount(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string userId;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("DELETE STUDENT ACCOUNT", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;
    cout << endl;
    // Display all students
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'student'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            printLine();
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]
                    << setw(15) << row[1]
                    << setw(20) << row[2]
                    << setw(15) << row[3]
                    << setw(25) << row[4]
                    << setw(15) << row[5] << endl;
            }
            printLine();
        }
        else {
            cout << "No students found." << endl;
        }
    }
    else {
        cout << "Error retrieving students: " << mysql_error(conn) << endl;
    }
    cout << endl;

    // Get student User ID to delete
    cout << "Enter Student User ID to delete: ";
    cin.ignore();
    getline(cin, userId);

    // Check if the student exists
    query = "SELECT u.user_id, u.username, u.first_name, u.last_name, u.email, u.phone_number, s.major "
        "FROM users u INNER JOIN students s ON u.user_id = s.student_id "
        "WHERE u.user_id = '" + userId + "' AND u.user_type = 'student'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            row = mysql_fetch_row(res);
            cout << "\nStudent Details:\n";
            cout << string(120, '-') << endl;
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number"
                << setw(20) << "Major" << endl;
            cout << string(120, '-') << endl;
            cout << left << setw(10) << row[0]
                << setw(15) << row[1]
                << setw(20) << row[2]
                << setw(15) << row[3]
                << setw(25) << row[4]
                << setw(15) << row[5]
                << setw(20) << row[6] << endl;
            printLine();

            // Query for enrolled courses
            query = "SELECT c.course_id, c.course_name, c.credits "
                "FROM courses c INNER JOIN scores sc ON c.course_id = sc.course_id "
                "WHERE sc.student_id = '" + userId + "'";
            qstate = mysql_query(conn, query.c_str());
            if (!qstate) {
                res = mysql_store_result(conn);
                int courseCount = res->row_count; // Get the total number of courses
                if (courseCount > 0) {
                    cout << endl;
                    cout << "\nThis student is enrolled in " << courseCount << " courses.\n";
                    cout << endl;
                    cout << string(120, '-');
                    cout << "\nCourses Enrolled:\n";
                    cout << string(120, '-') << endl;
                    cout << left << setw(15) << "Course ID"
                        << setw(40) << "Course Name"
                        << setw(20) << "Credits" << endl;
                    cout << string(120, '-') << endl;
                    while ((row = mysql_fetch_row(res))) {
                        cout << left << setw(15) << row[0]  // Course ID
                            << setw(40) << row[1]          // Course Name
                            << setw(20) << row[2] << endl; // Credits

                    }
                }
                else {
                    cout << "No courses found for this student.\n";
                }
            }
            else {
                cout << "Error retrieving courses: " << mysql_error(conn) << endl;
            }
            printLine();

            // Query for feedback
            query = "SELECT feedback_type, feedback_text FROM feedback WHERE user_id = '" + userId + "'";
            qstate = mysql_query(conn, query.c_str());
            if (!qstate) {
                res = mysql_store_result(conn);
                if (res->row_count > 0) {
                    cout << "\nFeedback Details:\n";
                    cout << string(120, '-') << endl;
                    cout << left << setw(20) << "Feedback Type"
                        << setw(100) << "Feedback Text" << endl;
                    cout << string(120, '-') << endl;
                    while ((row = mysql_fetch_row(res))) {
                        cout << left << setw(20) << row[0]
                            << setw(100) << row[1] << endl;

                    }
                }
                else {
                    cout << "No feedback found for this student.\n";
                }
            }
            else {
                cout << "Error retrieving feedback: " << mysql_error(conn) << endl;
            }
            printLine();
            // Confirm deletion
            char confirm;
            cout << "\nAre you sure you want to delete this student and all associated data (courses, scores, feedback, etc.)? (Y/N): ";
            cin >> confirm;
            if (tolower(confirm) == 'y') {
                query = "DELETE FROM scores WHERE student_id = '" + userId + "'";
                mysql_query(conn, query.c_str());
                query = "DELETE FROM feedback WHERE user_id = '" + userId + "'";
                mysql_query(conn, query.c_str());
                query = "DELETE FROM students WHERE student_id = '" + userId + "'";
                mysql_query(conn, query.c_str());
                query = "DELETE FROM users WHERE user_id = '" + userId + "' AND user_type = 'student'";
                qstate = mysql_query(conn, query.c_str());
                if (!qstate) {
                    cout << "\033[32mStudent account and associated data deleted successfully!\033[0m" << endl;
                }
                else {
                    cout << "\033[31mError deleting student account: " << mysql_error(conn) << "\033[0m" << endl;
                }
            }
            else {
                cout << "\nDeletion canceled. Returning to menu...\n";
            }
        }
        else {
            cout << "\033[31mNo student found with User ID: " << userId << "\033[0m" << endl;
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    manageStudentAccounts(lecturerId, fullName);
}

void searchStudentAccount(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string searchInput;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("SEARCH STUDENT ACCOUNT", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Prompt the user to input a single alphabet or part of a full name
    cout << "Enter part of the student's full name to search (e.g., first or last name): ";
    cin.ignore(); // Clear the input buffer
    getline(cin, searchInput);

    // Trim the input
    searchInput.erase(0, searchInput.find_first_not_of(" \t\n\r"));
    searchInput.erase(searchInput.find_last_not_of(" \t\n\r") + 1);

    // Query to find students whose full name matches or contains the input
    string query = "SELECT user_id, CONCAT(first_name, ' ', last_name) AS full_name "
        "FROM users WHERE user_type = 'student' AND "
        "CONCAT(first_name, ' ', last_name) LIKE '%" + searchInput + "%'";

    qstate = mysql_query(conn, query.c_str());

    // Check if the query was successful
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Display the matching student names
            cout << "\nMatching Students Found:\n";
            cout << string(50, '-') << endl;
            cout << left << setw(10) << "User ID" << setw(30) << "Full Name" << endl;
            cout << string(50, '-') << endl;

            vector<int> userIds; // Store user IDs for validation
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0] // User ID
                    << setw(30) << row[1] << endl; // Full Name
                userIds.push_back(atoi(row[0])); // Convert User ID to int and store
            }
            cout << string(50, '-') << endl;

            // Prompt the user to select a User ID
            int selectedId;
            cout << "\nEnter the User ID of the student to view details: ";
            cin >> selectedId;

            // Validate the selected User ID
            if (find(userIds.begin(), userIds.end(), selectedId) != userIds.end()) {
                // Query to get full details of the selected student
                string detailQuery = "SELECT user_id, username, first_name, last_name, "
                    "CONCAT(first_name, ' ', last_name) AS full_name, email, phone_number "
                    "FROM users WHERE user_id = '" + to_string(selectedId) + "'";

                qstate = mysql_query(conn, detailQuery.c_str());
                if (!qstate) {
                    res = mysql_store_result(conn);
                    if ((row = mysql_fetch_row(res))) {
                        // Display the student details (without password)
                        cout << "\nStudent Account Details:\n";
                        cout << string(120, '-') << endl;
                        cout << left << setw(10) << "User ID"
                            << setw(15) << "Username"
                            << setw(30) << "Full Name"
                            << setw(30) << "Email"
                            << setw(15) << "Phone Number" << endl;
                        cout << string(120, '-') << endl;
                        cout << left << setw(10) << row[0]  // User ID
                            << setw(15) << row[1]          // Username
                            << setw(30) << row[4]          // Full Name
                            << setw(30) << row[5]          // Email
                            << setw(15) << row[6] << endl; // Phone Number
                        cout << string(120, '-') << endl;

                        // Display student's major
                        string studentId = row[0]; // user_id from 'users' table
                        query = "SELECT major FROM students WHERE student_id = '" + studentId + "'";
                        qstate = mysql_query(conn, query.c_str());
                        if (!qstate) {
                            res = mysql_store_result(conn);
                            if (res->row_count > 0) {
                                row = mysql_fetch_row(res);
                                cout << "\nMajor: " << row[0] << endl;
                            }
                        }

                        query =
                            "SELECT DISTINCT c.course_id, c.course_name, c.credits "
                            "FROM scores s "
                            "JOIN courses c ON s.course_id = c.course_id "
                            "WHERE s.student_id = '" + to_string(selectedId) + "' "
                            "ORDER BY c.course_id ASC";

                        qstate = mysql_query(conn, query.c_str());

                        if (!qstate) {
                            res = mysql_store_result(conn);
                            int subjectCount = mysql_num_rows(res); // Count the rows directly
                            cout << "\nThis student is enrolled in " << subjectCount << " subjects." << endl;

                            if (subjectCount > 0) {
                                cout << "\nCourses Enrolled:\n";
                                cout << string(120, '-') << endl;
                                cout << left << setw(15) << "Course ID"
                                    << setw(40) << "Course Name"
                                    << setw(20) << "Credits" << endl;
                                cout << string(120, '-') << endl;

                                while ((row = mysql_fetch_row(res))) {
                                    string courseId = row[0] ? row[0] : "N/A";
                                    string courseName = row[1] ? row[1] : "N/A";
                                    string credits = row[2] ? row[2] : "N/A";

                                    cout << left << setw(15) << courseId
                                        << setw(40) << courseName
                                        << setw(20) << credits
                                        << endl;

                                }
                                printLine();
                            }
                        }
                        else {
                            cout << "\033[31mError retrieving courses: " << mysql_error(conn) << "\033[0m" << endl;
                        }

                        // Display feedback from the student
                        query = "SELECT feedback_text, feedback_type FROM feedback WHERE user_id = '" + to_string(selectedId) + "'";
                        qstate = mysql_query(conn, query.c_str());
                        if (!qstate) {
                            res = mysql_store_result(conn);
                            int feedbackCount = res->row_count;
                            cout << "\nThis student has provided " << feedbackCount << " feedback(s)." << endl;

                            if (feedbackCount > 0) {
                                cout << "\nFeedback Details:\n";
                                cout << string(120, '-') << endl;
                                cout << left << setw(20) << "Feedback Type"
                                    << setw(100) << "Feedback Text" << endl;
                                cout << string(120, '-') << endl;
                                while ((row = mysql_fetch_row(res))) {
                                    cout << left << setw(20) << row[1]    // Feedback Type
                                        << setw(100) << row[0]          // Feedback Text
                                        << endl;
                                }
                                printLine();
                            }
                        }
                    }
                }
                else {
                    cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
                }
            }
            else {
                cout << "\033[31mInvalid User ID selected.\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mNo students found matching the name: " << searchInput << "\033[0m" << endl;
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
    }

    // Prompt to return to the main menu
    cout << "\nPress any key to return to the previous menu...";
    (void)_getch();
    manageStudentAccounts(lecturerId, fullName);
}

void editLecturerAccount(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string userId, newFirstName, newLastName, newEmail, newPhoneNumber, newUsername, newPassword;
    int choice; // To capture the choice of what to edit
    int selectedOption = 0; // Track selected option: 0 = Yes, 1 = No

    char editAnother; // Variable to decide if the user wants to edit another lecturer

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("EDIT LECTURER ACCOUNT", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;
    cout << endl;

    printLine();
    // Query records where user_type is 'lecturer'
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'lecturer'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Print the table header
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(20) << "First Name"
                << setw(15) << "Last Name"
                << setw(25) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            // Print each row of data
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(20) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(25) << row[4]          // email
                    << setw(15) << row[5] << endl; // Phone Number
            }
            printLine();
        }
        else {
            cout << "No lecturers found." << endl;
        }
    }
    else {
        cout << "Error retrieving lecturers: " << mysql_error(conn) << endl;
    }
    cout << endl;

    do {
        // Get lecturer ID
        cout << "Enter Lecturer User ID to edit: ";
        cin.ignore(); // Clear any leftover input
        getline(cin, userId);

        // Check if the lecturer exists
        query = "SELECT * FROM users WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
        qstate = mysql_query(conn, query.c_str());
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                // Ask what part the user wants to edit
                cout << string(120, '-');
                cout << "Which part of the lecturer account would you like to edit?" << endl;
                cout << endl;
                cout << "1. First Name and Last Name" << endl;
                cout << "2. Email" << endl;
                cout << "3. Phone Number" << endl;
                cout << "4. Username" << endl;
                cout << "5. Password" << endl;
                cout << string(120, '-');
                cout << "Please Enter your choice (1-5): ";
                cin >> choice;
                cin.ignore(); // Clear the newline character left by cin
                cout << string(120, '-');

                // Based on the user's choice, update only the selected field
                switch (choice) {
                case 1:
                    // If the user chooses to edit both first name and last name
                    cout << "Enter New First Name: ";
                    getline(cin, newFirstName);
                    cout << endl;
                    cout << "Enter New Last Name: ";
                    getline(cin, newLastName);
                    query = "UPDATE users SET first_name = '" + newFirstName + "', last_name = '" + newLastName + "' WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
                    break;
                case 2:
                    // Email update with uniqueness check
                    cout << "Enter New Email: ";
                    getline(cin, newEmail);

                    // Check if the new email already exists
                    query = "SELECT * FROM users WHERE email = '" + newEmail + "' AND user_id != '" + userId + "' AND user_type = 'lecturer'";
                    qstate = mysql_query(conn, query.c_str());
                    if (!qstate) {
                        res = mysql_store_result(conn);
                        if (res->row_count > 0) {
                            cout << "\033[31mError: Email is already taken by another lecturer.\033[0m" << endl;
                            return; // Return if email is not unique
                        }
                        else {
                            query = "UPDATE users SET email = '" + newEmail + "' WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
                        }
                    }
                    break;
                case 3:
                    cout << "Enter New Phone Number: ";
                    getline(cin, newPhoneNumber);
                    query = "UPDATE users SET phone_number = '" + newPhoneNumber + "' WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
                    break;
                case 4:
                    // Username update with uniqueness check
                    cout << "Enter New Username: ";
                    getline(cin, newUsername);

                    // Check if the new username already exists
                    query = "SELECT * FROM users WHERE username = '" + newUsername + "' AND user_id != '" + userId + "' AND user_type = 'lecturer'";
                    qstate = mysql_query(conn, query.c_str());
                    if (!qstate) {
                        res = mysql_store_result(conn);
                        if (res->row_count > 0) {
                            cout << "\033[31mError: Username is already taken by another lecturer.\033[0m" << endl;
                            return; // Return if username is not unique
                        }
                        else {
                            query = "UPDATE users SET username = '" + newUsername + "' WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
                        }
                    }
                    break;
                case 5:
                    cout << "Enter New Password: ";
                    getline(cin, newPassword);
                    query = "UPDATE users SET password = '" + newPassword + "' WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
                    break;
                default:
                    cout << "Invalid choice. Returning to menu." << endl;
                    return; // Exit if the user chooses an invalid option
                }

                // Execute the update query
                qstate = mysql_query(conn, query.c_str());
                if (!qstate) {
                    cout << "\033[32mLecturer account updated successfully!\033[0m" << endl;
                }
                else {
                    cout << "\033[31mError updating lecturer account: " << mysql_error(conn) << "\033[0m" << endl;
                }
            }
            else {
                cout << "\033[31mNo lecturer found with User ID: " << userId << "\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
        }

        // Ask if the user wants to edit another lecturer's account
        cout << "\nDo you want to edit another lecturer's account? (Y/N): ";
        cin >> editAnother;
        cin.ignore(); // Clear any leftover newline character

    } while (editAnother == 'Y' || editAnother == 'y'); // Continue if the user chooses 'Y'

    // After finishing all edits, return to the manageStudentAccounts page
    manageLecturerAccounts(lecturerId, fullName); // Go back to the manageStudentAccounts page
}

void deleteLecturerAccount(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string userId;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("DELETE LECTURER ACCOUNT", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Query to retrieve all lecturers
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'lecturer'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Display lecturer details as a table
            cout << "\nLecturer Details:\n";
            cout << string(120, '-') << endl;
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(15) << "First Name"
                << setw(15) << "Last Name"
                << setw(30) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(15) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(30) << row[4]          // Email
                    << setw(15) << row[5] << endl; // Phone Number
            }
            cout << string(120, '-') << endl;
        }
        else {
            cout << "\033[31mNo lecturers found.\033[0m" << endl;
            cout << "\nPress any key to return...";
            (void)_getch();
            return;
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
        return;
    }

    // Get the Lecturer User ID to delete
    cout << "\nEnter Lecturer User ID to delete: ";
    cin.ignore(); // Clear any leftover input
    getline(cin, userId);

    // Query to check if the lecturer exists
    query = "SELECT user_id, username, first_name, last_name, email, phone_number "
        "FROM users WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Display lecturer details for confirmation
            row = mysql_fetch_row(res);
            cout << "\nLecturer Details:\n";
            cout << string(120, '-') << endl;
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(15) << "First Name"
                << setw(15) << "Last Name"
                << setw(30) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;
            cout << left << setw(10) << row[0]  // User ID
                << setw(15) << row[1]          // Username
                << setw(15) << row[2]          // First Name
                << setw(15) << row[3]          // Last Name
                << setw(30) << row[4]          // Email
                << setw(15) << row[5] << endl; // Phone Number
            cout << string(120, '-') << endl;

            // Query to find the department for the selected lecturer
            string departmentQuery = "SELECT CONCAT('Department: ', d.department_name, ' (', d.department_short_name, ')') AS department "
                "FROM users u INNER JOIN department d ON u.user_id = d.lecturer_id "
                "WHERE u.user_id = '" + userId + "' AND u.user_type = 'lecturer'";

            qstate = mysql_query(conn, departmentQuery.c_str());
            if (!qstate) {
                res = mysql_store_result(conn);
                if ((row = mysql_fetch_row(res))) {
                    // Display the department information
                    cout << row[0] << endl; // This will print "Department: longname department (short name department)"
                }
                else {
          
                printWarning("Notes: No department found for the selected lecturer.\n");
            
                }
            }
            else {
                cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
            }

            // Show the courses the lecturer is teaching
            query = "SELECT c.course_id, c.course_name FROM course_lecturer cl "
                "JOIN courses c ON cl.course_id = c.course_id "
                "WHERE cl.lecturer_id = '" + userId + "'";
            qstate = mysql_query(conn, query.c_str());
            if (!qstate) {
                res = mysql_store_result(conn);
                int courseCount = res->row_count;
                cout << "\nThis lecturer is teaching " << courseCount << " courses." << endl;

                if (courseCount > 0) {
                    cout << "\nCourses Assigned to Lecturer:\n";
                    cout << string(120, '-') << endl;
                    cout << left << setw(15) << "Course ID"
                        << setw(40) << "Course Name" << endl;
                    cout << string(120, '-') << endl;

                    while ((row = mysql_fetch_row(res))) {
                        cout << left << setw(15) << row[0]   // Course ID
                            << setw(40) << row[1] << endl; // Course Name
                    }
                    cout << string(120, '-') << endl;
                }
            }
            else {
                cout << "\033[31mError executing query to retrieve courses: " << mysql_error(conn) << "\033[0m" << endl;
            }

            // Confirm deletion
            char confirm;
            cout << "\nAre you sure you want to delete this lecturer and all associated data (courses, feedback, etc.)? (Y/N): ";
            cin >> confirm;

            if (tolower(confirm) == 'y') {
                // Delete all records associated with the lecturer
                query = "DELETE FROM course_lecturer WHERE lecturer_id = '" + userId + "'";
                mysql_query(conn, query.c_str()); // Delete lecturer's courses

                query = "DELETE FROM feedback WHERE user_id = '" + userId + "'";
                mysql_query(conn, query.c_str()); // Delete feedback

                // Delete department associated with the lecturer
                query = "DELETE FROM department WHERE lecturer_id = '" + userId + "'";
                mysql_query(conn, query.c_str()); // Delete department

                query = "DELETE FROM users WHERE user_id = '" + userId + "' AND user_type = 'lecturer'";
                qstate = mysql_query(conn, query.c_str()); // Delete lecturer's account

                if (!qstate) {
                    cout << "\033[32mLecturer account and associated data (including department) deleted successfully!\033[0m" << endl;
                }
                else {
                    cout << "\033[31mError deleting lecturer account: " << mysql_error(conn) << "\033[0m" << endl;
                }
            }
            else {
                cout << "\nDeletion canceled. Returning to menu...\n";
            }

        }
        else {
            cout << "\033[31mNo lecturer found with User ID: " << userId << "\033[0m" << endl;
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    manageLecturerAccounts(lecturerId, fullName);
}

void searchLecturerAccount(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string searchInput;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("SEARCH LECTURER ACCOUNT", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Prompt the user to input a substring of the lecturer's full name
    cout << "Enter part of the Lecturer's full name to search (e.g., first or last name): ";
    cin.ignore(); // Clear the input buffer
    getline(cin, searchInput);

    // Trim the input
    searchInput.erase(0, searchInput.find_first_not_of(" \t\n\r"));
    searchInput.erase(searchInput.find_last_not_of(" \t\n\r") + 1);

    // Query to find lecturers whose full name matches or contains the input
    string query = "SELECT user_id, CONCAT(first_name, ' ', last_name) AS full_name "
        "FROM users WHERE user_type = 'lecturer' AND "
        "CONCAT(first_name, ' ', last_name) LIKE '%" + searchInput + "%'";

    qstate = mysql_query(conn, query.c_str());

    // Check if the query was successful
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Display the matching lecturer names
            cout << "\nMatching Lecturers Found:\n";
            cout << string(120, '-') << endl;
            cout << left << setw(10) << "User ID" << setw(30) << "Full Name" << endl;
            cout << string(120, '-') << endl;

            vector<string> userIds; // Store user IDs for validation
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(30) << row[1] << endl; // Full Name
                userIds.push_back(row[0]);
            }
            cout << string(120, '-') << endl;

            // Prompt the user to select a User ID
            string selectedId;
            cout << "\nEnter the User ID of the lecturer to view details: ";
            cin >> selectedId;

            // Validate the selected User ID
            if (find(userIds.begin(), userIds.end(), selectedId) != userIds.end()) {
                // Query to get full details of the selected lecturer
                string detailQuery = "SELECT user_id, username, first_name, last_name, "
                    "email, phone_number "
                    "FROM users WHERE user_id = '" + selectedId + "' AND user_type = 'lecturer'";

                qstate = mysql_query(conn, detailQuery.c_str());
                if (!qstate) {
                    res = mysql_store_result(conn);
                    if ((row = mysql_fetch_row(res))) {
                        // Display lecturer details
                        cout << "\nLecturer Details:\n";
                        cout << string(120, '-') << endl;
                        cout << left << setw(10) << "User ID"
                            << setw(15) << "Username"
                            << setw(15) << "First Name"
                            << setw(15) << "Last Name"
                            << setw(30) << "Email"
                            << setw(15) << "Phone Number" << endl;
                        cout << string(120, '-') << endl;
                        cout << left << setw(10) << row[0]  // User ID
                            << setw(15) << row[1]          // Username
                            << setw(15) << row[2]          // First Name
                            << setw(15) << row[3]          // Last Name
                            << setw(30) << row[4]          // Email
                            << setw(15) << row[5] << endl; // Phone Number
                        cout << string(120, '-') << endl;

                        // Query to find the department for the selected lecturer
                        string departmentQuery = "SELECT CONCAT('Department: ', d.department_name, ' (', d.department_short_name, ')') AS department "
                            "FROM users u INNER JOIN department d ON u.user_id = d.lecturer_id "
                            "WHERE u.user_id = '" + selectedId + "' AND u.user_type = 'lecturer'";

                        qstate = mysql_query(conn, departmentQuery.c_str());
                        if (!qstate) {
                            res = mysql_store_result(conn);
                            if ((row = mysql_fetch_row(res))) {
                                // Display the department information
                                cout << row[0] << endl; // This will print "Department: longname department (short name department)"
                            }
                            else {

                                printWarning("Notes: No department found for the selected lecturer.\n");
                            }
                        }
                        else {
                            cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
                        }

                        // Show the courses the lecturer is teaching
                        string coursesQuery = "SELECT c.course_id, c.course_name FROM course_lecturer cl "
                            "JOIN courses c ON cl.course_id = c.course_id "
                            "WHERE cl.lecturer_id = '" + selectedId + "'";
                        qstate = mysql_query(conn, coursesQuery.c_str());
                        if (!qstate) {
                            res = mysql_store_result(conn);
                            int courseCount = res->row_count;
                            cout << "\nThis lecturer is teaching " << courseCount << " courses." << endl;

                            if (courseCount > 0) {
                                cout << "\nCourses Assigned to Lecturer:\n";
                                cout << string(120, '-') << endl;
                                cout << left << setw(15) << "Course ID"
                                    << setw(40) << "Course Name" << endl;
                                cout << string(120, '-') << endl;

                                while ((row = mysql_fetch_row(res))) {
                                    cout << left << setw(15) << row[0]   // Course ID
                                        << setw(40) << row[1] << endl; // Course Name
                                }
                                cout << string(120, '-') << endl;
                            }
                        }
                        else {
                            cout << "\033[31mError executing query to retrieve courses: " << mysql_error(conn) << "\033[0m" << endl;
                        }
                    }
                }
                else {
                    cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
                }
            }
            else {
                cout << "\033[31mInvalid User ID selected.\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mNo lecturers found matching the name: " << searchInput << "\033[0m" << endl;
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
    }

    // Prompt to return to the main menu
    cout << "\nPress any key to return to the previous menu...";
    (void)_getch();
    manageLecturerAccounts(lecturerId, fullName);
}

// Define the trimString function
void trimString(string& str) {
    str.erase(0, str.find_first_not_of(" \t\n\r")); // Trim from start
    str.erase(str.find_last_not_of(" \t\n\r") + 1); // Trim from end
}

// Check if a field is unique in the database
bool isCourseFieldUnique(const string& field, const string& value) {
    string query = "SELECT COUNT(*) FROM courses WHERE " + field + " = '" + value + "'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        return stoi(row[0]) == 0; // Field is unique if COUNT == 0
    }
    return false; // Database error
}

void setCourse(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    string courseCode, courseName, creditsInput;
    int credits;

    while (true) {
        system("cls"); // Clear the screen before re-prompting

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("SET COURSE PAGE", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        // Input and validate course code
        cout << "Enter Course Code: ";
        getline(cin >> ws, courseCode);
        if (courseCode.empty() || !isCourseFieldUnique("course_code", courseCode)) {
            printError("Notice: The course code is empty or already exists. Please choose a unique course code.");
            continue;
        }

        // Input and validate course name
        cout << "Enter Course Name: ";
        getline(cin >> ws, courseName);
        if (courseName.empty()) {
            printError("Notice: Course name cannot be empty. Please enter a valid course name.");
            continue;
        }

        // Input and validate credits
        cout << "Enter Credits: ";
        getline(cin >> ws, creditsInput);

        try {
            credits = stoi(creditsInput);
            if (credits <= 0) {
                throw invalid_argument("Credits must be positive.");
            }
        }
        catch (const invalid_argument&) {
            printError("Notice: Credits must be a positive integer. Please try again.");
            continue;
        }

        // Insert the course into the courses table
        string query = "INSERT INTO courses (course_code, course_name, credits) "
            "VALUES ('" + courseCode + "', '" + courseName + "', " + to_string(credits) + ")";

        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            printSuccess("Course added successfully!\n");
            showLoadingScreen("\033[32mRedirecting to course menu...\033[0m");
            courseMenu(lecturerId, fullName); // Redirect
            break;
        }
        else {
            printError("Failed to add course: " + string(mysql_error(conn)));
            cout << "Press Enter to retry...";
            (void)_getch();
            setCourse(lecturerId, fullName);
        }
    }
}

void courseMenu(int lecturerId, const string& fullName) {
    while (true) {

        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen
        int choice;

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("COURSES MANAGEMENT MENU", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        cout << "1. View the courses added" << endl;
        cout << "2. Edit the courses added" << endl;
        cout << "3. Delete the courses added" << endl;
        cout << "4. Exit and back to Admin Page" << endl;
        cout << "5. Logout and back to Main Page" << endl;
        cout << string(120, '-') << endl;

        // Take user input
        cout << "Please enter your choice: ";
        cin >> choice;

        // Process the user input
        switch (choice) {
        case 1:
            // View the courses added
            viewCourses();
            break;

        case 2:
            // Edit the courses added
            editCourses();
            break;

        case 3:
            // Delete the courses added
            deleteCourses();
            break;

        case 4:
            // Exit and back to Admin Page
            cout << "Returning to Admin Page..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay
            adminPage(lecturerId, fullName); // Pass fullName back to Admin Page
            return; // Exit the courseMenu loop

        case 5:
            // Logout and back to Main Page
            cout << "Logging out and returning to Main Page..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay
            main(lecturerId, fullName);

        default:
            // Handle invalid input
            cout << "Invalid choice! Please choose between 1, 2, 3, 0, or 00." << endl;
            (void)_getch(); // Pause for user to see the message
            break;
        }
    }
}

// Function to edit courses 
void editCourses() {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string courseCode, newCourseName;
    int newCredits;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("EDIT COURSE", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << setw(20) << "Enter the course code to edit: ";
    cin.ignore();
    getline(cin, courseCode);

    cout << setw(20) << "Enter the new course name: ";
    getline(cin, newCourseName);

    cout << setw(20) << "Enter the new credits: ";
    cin >> newCredits;

    string query = "UPDATE courses SET course_name = '" + newCourseName +
        "', credits = " + to_string(newCredits) +
        " WHERE course_code = '" + courseCode + "'";

    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        cout << "\033[32mCourse updated successfully!\033[0m" << endl;
    }
    else {
        cout << "\033[31mError updating course: " << mysql_error(conn) << "\033[0m" << endl;
    }

    cout << "\n\033[34mPress any key to return to the course menu...\033[0m";
    (void)_getch();
}

// Function to view courses 
void viewCourses() {
    showLoadingScreen("Redirecting to Course List View.......");
    cout << "Please Wait...";
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("COURSE LIST VIEW", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // SQL Query to fetch courses
    string query = "SELECT course_id, course_code, course_name, credits FROM courses";

    qstate = mysql_query(conn, query.c_str());

    vector<vector<string>> courseData; // To store course data for saving to file

    if (!qstate) {
        res = mysql_store_result(conn); // Store the result of the query
        if (mysql_num_rows(res) > 0) {
            // Table headers
            cout << left << setw(10) << "ID"
                << setw(20) << "Course Code"
                << setw(50) << "Course Name"
                << "Credits" << endl;
            cout << string(120, '-') << endl;

            // Display rows and store data for file output
            while ((row = mysql_fetch_row(res))) {
                vector<string> rowData;
                for (int i = 0; i < 4; i++) { // 4 columns: ID, Code, Name, Credits
                    rowData.push_back(row[i] ? row[i] : "N/A");
                }
                courseData.push_back(rowData);

                cout << left << setw(10) << row[0]   // Course ID
                    << setw(20) << row[1]           // Course Code
                    << setw(50) << row[2]           // Course Name
                    << row[3] << endl;              // Credits
            }
            printLine();
        }
        else {
            cout << "No courses found." << endl;
        }
    }
    else {
        cout << "Error retrieving courses: " << mysql_error(conn) << endl;
    }

    // Step: Ask to save into file
    char saveChoice;
    cout << "\nDo you want to save this information into a file? (Y/N): ";
    cin >> saveChoice;

    if (toupper(saveChoice) == 'Y') {
        ofstream outFile("courses_list.txt");

        // Write table header
        outFile << left << setw(10) << "ID"
            << setw(20) << "Course Code"
            << setw(50) << "Course Name"
            << "Credits" << endl;
        outFile << string(120, '-') << endl;

        // Write each row of data to the file
        for (const auto& row : courseData) {
            outFile << left << setw(10) << row[0]   // Course ID
                << setw(20) << row[1]           // Course Code
                << setw(50) << row[2]           // Course Name
                << row[3] << endl;              // Credits
        }

        outFile.close();
        cout << "\033[32mCourse list saved successfully to 'courses_list.txt'.\033[0m" << endl;
    }
    else {
        cout << "\nReturning to the previous menu..." << endl;
    }

    // Return to the previous menu
    cout << "\nPress any key to return...";
    (void)_getch();
}

// Function to delete courses
void deleteCourses() {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string courseCode;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("DELETE COURSE", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Prompt the user to input the course code
    cout << "Enter the Course Code to delete: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, courseCode);

    // Trim the input to clean any leading or trailing spaces
    courseCode.erase(0, courseCode.find_first_not_of(" \t\n\r"));
    courseCode.erase(courseCode.find_last_not_of(" \t\n\r") + 1);

    // Validate that the course code is not empty
    if (courseCode.empty()) {
        cout << "\033[31mError: Course code cannot be empty.\033[0m" << endl;
        cout << "\nPress any key to return to the course menu...";
        (void)_getch();
        return;
    }

    // Query to search for the course by its course code
    string query = "SELECT course_code, course_name, credits FROM courses WHERE course_code = '" + courseCode + "'";
    qstate = mysql_query(conn, query.c_str());

    // Check if the query was successful
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Display the course details
            row = mysql_fetch_row(res);
            cout << "\nCourse Details Found:\n";
            cout << string(120, '-') << endl;
            cout << "Course Code: " << row[0] << endl;
            cout << "Course Name: " << row[1] << endl;
            cout << "Credits: " << row[2] << endl;
            cout << string(120, '-') << endl;

            // Ask for confirmation to delete
            char confirm;
            cout << "\nAre you sure you want to delete this course? (Y/N): ";
            cin >> confirm;
            if (tolower(confirm) == 'y') {
                // SQL query to delete the course
                string deleteQuery = "DELETE FROM courses WHERE course_code = '" + courseCode + "'";
                qstate = mysql_query(conn, deleteQuery.c_str());

                if (!qstate) {
                    cout << "\033[32mCourse \"" << courseCode << "\" deleted successfully!\033[0m" << endl;
                }
                else {
                    cout << "\033[31mError deleting course: " << mysql_error(conn) << "\033[0m" << endl;
                }
            }
            else {
                cout << "\n\033[33mOperation cancelled. Returning to course menu...\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mNo course found with the code: " << courseCode << "\033[0m" << endl;
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
    }

    // Prompt to return to the course menu
    cout << "\nPress any key to return to the course menu...";
    (void)_getch();
}

void viewStudentAssignedCourses(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("STUDENT ASSIGNED COURSES", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // SQL Query to retrieve the data
    string query = "SELECT s.student_id AS 'Student ID', "
        "CONCAT(u.first_name, ' ', u.last_name) AS 'Student Name', "
        "c.course_name AS 'Course Name', "
        "c.course_code AS 'Course Code', "
        "s.major AS 'Major' "
        "FROM students s "
        "JOIN users u ON s.student_id = u.user_id "
        "JOIN scores sc ON s.student_id = sc.student_id "
        "JOIN courses c ON sc.course_id = c.course_id";

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Print the table header
            cout << left << setw(15) << "Student ID"
                << setw(25) << "Student Name"
                << setw(30) << "Course Name"
                << setw(15) << "Course Code"
                << setw(20) << "Major" << endl;
            cout << string(120, '-') << endl;

            // Print each row of data
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(15) << row[0]  // Student ID
                    << setw(25) << row[1]          // Student Name
                    << setw(30) << row[2]          // Course Name
                    << setw(15) << row[3]          // Course Code
                    << setw(20) << row[4] << endl; // Major
            }
        }
        else {
            cout << "No assigned courses found for any students." << endl;
        }
    }
    else {
        cout << "Error retrieving assigned courses: " << mysql_error(conn) << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    adminPage(lecturerId, fullName);
}

void viewStudentAssignedCoursesInformation(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("STUDENT ASSIGNED COURSES", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // SQL Query to retrieve the data
    string query = "SELECT s.student_id AS 'Student ID', "
        "CONCAT(u.first_name, ' ', u.last_name) AS 'Student Name', "
        "c.course_name AS 'Course Name', "
        "c.course_code AS 'Course Code', "
        "s.major AS 'Major' "
        "FROM students s "
        "JOIN users u ON s.student_id = u.user_id "
        "JOIN scores sc ON s.student_id = sc.student_id "
        "JOIN courses c ON sc.course_id = c.course_id";

    qstate = mysql_query(conn, query.c_str());

    vector<vector<string>> assignedCourses; // Store data for saving to a file

    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0) {
            // Print the table header
            cout << left << setw(15) << "Student ID"
                << setw(25) << "Student Name"
                << setw(30) << "Course Name"
                << setw(15) << "Course Code"
                << setw(20) << "Major" << endl;
            cout << string(120, '-') << endl;

            // Print each row of data and store for saving
            while ((row = mysql_fetch_row(res))) {
                vector<string> rowData;
                for (int i = 0; i < 5; ++i) { // 5 columns: Student ID, Student Name, etc.
                    rowData.push_back(row[i] ? row[i] : "N/A");
                }
                assignedCourses.push_back(rowData);

                cout << left << setw(15) << row[0]  // Student ID
                    << setw(25) << row[1]          // Student Name
                    << setw(30) << row[2]          // Course Name
                    << setw(15) << row[3]          // Course Code
                    << setw(20) << row[4] << endl; // Major
            }
            printLine();
        }
        else {
            cout << "No assigned courses found for any students." << endl;
        }
    }
    else {
        cout << "Error retrieving assigned courses: " << mysql_error(conn) << endl;
    }

    // Ask the user if they want to save the file
    char saveChoice;
    cout << "\nDo you want to save this information into a file? (Y/N): ";
    cin >> saveChoice;

    if (toupper(saveChoice) == 'Y') {
        ofstream outFile("assigned_courses.txt");

        // Write table header
        outFile << left << setw(15) << "Student ID"
            << setw(25) << "Student Name"
            << setw(30) << "Course Name"
            << setw(15) << "Course Code"
            << setw(20) << "Major" << endl;
        outFile << string(120, '-') << endl;

        // Write data rows to the file
        for (const auto& row : assignedCourses) {
            outFile << left << setw(15) << row[0]  // Student ID
                << setw(25) << row[1]          // Student Name
                << setw(30) << row[2]          // Course Name
                << setw(15) << row[3]          // Course Code
                << setw(20) << row[4] << endl; // Major
        }

        outFile.close();
        cout << "\033[32mAssigned courses saved successfully to 'assigned_courses.txt'.\033[0m" << endl;
    }
    else {
        cout << "\nReturning to the previous menu..." << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    viewInformation(lecturerId, fullName); // Return to the previous menu
}

// Function to view student and lecturer account details
void viewInformation(int lecturerId, const string& fullName) {//viewInformation
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    int chViewInformation;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW INFORMATION MANAGEMENT", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << "1. View Courses " << endl;
    cout << "2. View Lecturer Account" << endl;
    cout << "3. View Student Account" << endl;
    cout << "4. View Assign Courses Student" << endl;
    cout << "5. View Student Course Feedback" << endl;
    cout << "6. View Student System Feedback" << endl;
    cout << "7. View Set Score" << endl;
    cout << "8. View Assign Course for Lecturer" << endl;
    cout << "9. View Assign Department for Lecturer" << endl;
    cout << "10. Return To Admin Page" << endl;
    cout << endl;
    cout << string(120, '-') << endl;
    cout << "Please enter your choice: ";
    cin >> chViewInformation;

    switch (chViewInformation) {
    case 1:
        ViewCourses(lecturerId, fullName);
        break;
    case 2:
        viewAllLecturersinformation(lecturerId, fullName);
        break;
    case 3:
        viewAllStudentsinformation(lecturerId, fullName);
        break;
    case 4:
        viewStudentAssignedCoursesInformation(lecturerId, fullName);
        break;
    case 5:
        viewCourseFeedbackForAdmin(lecturerId, fullName);
        break;
    case 6:
        viewSystemFeedback(lecturerId, fullName);
        break;
    case 7:
        viewGradeRanges1(lecturerId, fullName);
        break;
    case 8:
        viewLecturerCourses(lecturerId, fullName);
        break;
    case 9:
        viewLecturerDepartment(lecturerId, fullName);
        break;
    case 10:
        adminPage(lecturerId, fullName);
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        (void)_getch();
        viewInformation(lecturerId, fullName);
        break;
    }
}

void downloadLecturerDetails(const string& userId, const string& lecturerDetails, const string& department, const string& courseDetails) {
    string fileName = "lecturer_details_" + userId + ".txt";
    ofstream outFile(fileName);

    if (outFile.is_open()) {
        outFile << lecturerDetails << "\n";
        outFile << department << "\n";
        outFile << courseDetails << "\n";
        outFile.close();
        cout << "\033[32mData has been successfully downloaded to " << fileName << "\033[0m" << endl;
    }
    else {
        cout << "\033[31mFailed to create the file for download.\033[0m" << endl;
    }
}

void viewLecturerCourses(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW LECTURER COURSES", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // Query to retrieve all lecturers
    string query = "SELECT user_id, username, first_name, last_name, email, phone_number FROM users WHERE user_type = 'lecturer'";
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Use ostringstream to build the table for display and download
            ostringstream oss;

            // Display lecturer details as a table
            cout << "\nLecturer Details:\n";
            cout << string(120, '-') << endl;
            cout << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(15) << "First Name"
                << setw(15) << "Last Name"
                << setw(30) << "Email"
                << setw(15) << "Phone Number" << endl;
            cout << string(120, '-') << endl;

            oss << "Lecturer Details:\n";
            oss << string(120, '-') << "\n";
            oss << left << setw(10) << "User ID"
                << setw(15) << "Username"
                << setw(15) << "First Name"
                << setw(15) << "Last Name"
                << setw(30) << "Email"
                << setw(15) << "Phone Number" << "\n";
            oss << string(120, '-') << "\n";

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(15) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(30) << row[4]          // Email
                    << setw(15) << row[5] << endl; // Phone Number
             
                oss << left << setw(10) << row[0]  // User ID
                    << setw(15) << row[1]          // Username
                    << setw(15) << row[2]          // First Name
                    << setw(15) << row[3]          // Last Name
                    << setw(30) << row[4]          // Email
                    << setw(15) << row[5] << "\n"; // Phone Number
            }
            cout << string(120, '-') << endl;
            oss << string(120, '-') << "\n";

            // Ask the user if they want to download the file
            char downloadChoice;
            cout << "Do you want to download the lecturer details? (y/n): ";
            cin >> downloadChoice;

            if (tolower(downloadChoice) == 'y') {
                // Write the table to a file for download
                ofstream outFile("lecturer_courses.txt");
                if (outFile.is_open()) {
                    outFile << oss.str();
                    outFile.close();
                    cout << "\033[32mLecturer details have been downloaded to lecturer_courses.txt.\033[0m" << endl;
                }
                else {
                    cout << "\033[31mFailed to create download file.\033[0m" << endl;
                }
            }
            else {
                cout << "\033[33mDownload skipped.\033[0m" << endl;
            }
        }
        else {
            cout << "\033[31mNo lecturers found.\033[0m" << endl;
            cout << "\nPress any key to return...";
            (void)_getch();
            return;
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
        return;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    viewInformation(lecturerId, fullName);
}

void viewLecturerDepartment(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait...");
    system("cls"); // Clear the screen
    cout << string(120, '=') << endl; // Separator line
    int width = static_cast<int>((120 - 30) / 2 + 5); // Calculate centered width
    cout << setw(width) << "" << "VIEW DEPARTMENT LECTURER" << endl; // Centered title
    cout << string(120, '=') << endl;

    // Use ostringstream to build the table for display and download
    ostringstream oss;

    // Query: Get the list of lecturers with their departments
    cout << "\nLecturer Details:\n";
    cout << string(120, '-') << endl;
    cout << left << setw(10) << "User ID"
        << setw(30) << "Full Name"
        << setw(15) << "Dept Code"
        << setw(40) << "Dept Name" << endl;
    cout << string(120, '-') << endl;

    oss << "Lecturer Details:\n";
    oss << string(120, '-') << "\n";
    oss << left << setw(10) << "User ID"
        << setw(30) << "Full Name"
        << setw(15) << "Dept Code"
        << setw(40) << "Dept Name" << "\n";
    oss << string(120, '-') << "\n";

    // SQL Query
    string lecturerQuery =
        "SELECT u.user_id, CONCAT(u.first_name, ' ', u.last_name) AS name, "
        "d.department_short_name, d.department_name "
        "FROM users u "
        "LEFT JOIN department d ON u.user_id = d.lecturer_id "
        "WHERE u.user_type = 'lecturer'";

    qstate = mysql_query(conn, lecturerQuery.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        if (mysql_num_rows(res) > 0) {
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0]                        // User ID
                    << setw(30) << row[1]                                // Full Name
                    << setw(15) << (row[2] ? row[2] : "N/A")            // Dept Code
                    << setw(40) << (row[3] ? row[3] : "N/A")            // Dept Name
                    << endl;

                oss << left << setw(10) << row[0]                        // User ID
                    << setw(30) << row[1]                                // Full Name
                    << setw(15) << (row[2] ? row[2] : "N/A")            // Dept Code
                    << setw(40) << (row[3] ? row[3] : "N/A")            // Dept Name
                    << "\n";
            }
        }
        else {
            cout << "\033[33mNo lecturers found.\033[0m" << endl;
            oss << "No lecturers found.\n";
        }
    }
    else {
        cout << "\nError retrieving lecturers: " << mysql_error(conn) << endl;
        return;
    }

    cout << string(120, '-') << endl;
    oss << string(120, '-') << "\n";

    // Ask the user if they want to download the file
    char downloadChoice;
    cout << "Do you want to download the lecturer department details? (y/n): ";
    cin >> downloadChoice;

    if (tolower(downloadChoice) == 'y') {
        // Write the table to a file for download
        ofstream outFile("lecturer_department.txt");
        if (outFile.is_open()) {
            outFile << oss.str();
            outFile.close();
            cout << "\033[32mLecturer department details have been downloaded to lecturer_department.txt.\033[0m" << endl;
        }
        else {
            cout << "\033[31mFailed to create download file.\033[0m" << endl;
        }
    }
    else {
        cout << "\033[33mDownload skipped.\033[0m" << endl;
    }

    cout << "\nPress any key to return...";
    (void)_getch();
    viewInformation(lecturerId, fullName);
}


void viewSystemFeedback(int lecturerId, const string& fullName) {
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW SYSTEM FEEDBACK", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // SQL query to fetch required data
    const char* query = R"(
      SELECT 
    users.username AS student_username, 
    feedback.feedback_text AS feedback 
FROM feedback 
INNER JOIN users ON feedback.user_id = users.user_id 
WHERE feedback.feedback_type = 'System feedback';
    )";

    // Execute the query
    qstate = mysql_query(conn, query);
    if (qstate) {
        std::cerr << "Query execution failed: " << mysql_error(conn) << std::endl;
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Failed to retrieve query result: " << mysql_error(conn) << std::endl;
        return;
    }

    // Prepare to store feedback for saving into a file
    vector<pair<string, string>> feedbackData;

    // Print the results in a table format
    std::cout << "\nFeedback Details:\n";
    std::cout << std::string(120, '-') << std::endl;
    std::cout << std::left << std::setw(20) << "Student Username"
        << std::setw(40) << "Feedback" << std::endl;
    std::cout << std::string(120, '-') << std::endl;

    while ((row = mysql_fetch_row(res))) {
        string studentUsername = row[0] ? row[0] : "N/A";
        string feedbackText = row[1] ? row[1] : "N/A";

        // Save data for file
        feedbackData.push_back({ studentUsername, feedbackText });

        // Display feedback
        std::cout << std::left << std::setw(20) << studentUsername
            << std::setw(40) << feedbackText << std::endl;
    }
    std::cout << std::string(120, '-') << std::endl;

    mysql_free_result(res);

    // Ask the user if they want to save the file
    char saveChoice;
    std::cout << "\nDo you want to save this feedback into a file? (Y/N): ";
    std::cin >> saveChoice;

    if (toupper(saveChoice) == 'Y') {
        std::ofstream outFile("system_feedback.txt");

        // Write table headers
        outFile << "\nFeedback Details:\n";
        outFile << std::string(120, '-') << "\n";
        outFile << std::left << std::setw(20) << "Student Username"
            << std::setw(40) << "Feedback" << "\n";
        outFile << std::string(120, '-') << "\n";

        // Write feedback data
        for (const auto& feedback : feedbackData) {
            outFile << std::left << std::setw(20) << feedback.first  // Student Username
                << std::setw(40) << feedback.second // Feedback
                << "\n";
        }

        outFile << std::string(120, '-') << "\n";
        outFile.close();

        std::cout << "\033[32mFeedback has been successfully saved to 'system_feedback.txt'.\033[0m\n";
    }
    else {
        std::cout << "\nReturning to the previous menu..." << std::endl;
    }

    std::cout << "\nPress any key to return page View information...";
    (void)_getch();
    viewInformation(lecturerId, fullName);
}


void viewCourseFeedbackForAdmin(int lecturerId, const string& fullName) {
    //showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW COURSES FEEDBACK", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    // SQL query to fetch required data
    const char* query = R"(
       SELECT 
           users.username AS student_username, 
           CONCAT(lecturer.first_name, ' ', lecturer.last_name) AS lecturer_name, 
           courses.course_name AS course_title, 
           feedback.feedback_text AS feedback 
       FROM feedback 
       INNER JOIN users ON feedback.user_id = users.user_id 
       INNER JOIN courses ON feedback.course_id = courses.course_id 
       INNER JOIN course_lecturer ON courses.course_id = course_lecturer.course_id 
       INNER JOIN users AS lecturer ON course_lecturer.lecturer_id = lecturer.user_id 
       WHERE feedback.feedback_type = 'Course feedback';
    )";

    // Execute the query
    qstate = mysql_query(conn, query);
    if (qstate) {
        std::cerr << "Query execution failed: " << mysql_error(conn) << std::endl;
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Failed to retrieve query result: " << mysql_error(conn) << std::endl;
        return;
    }

    // Prepare to store feedback for saving into a file
    vector<vector<string>> feedbackData;

    // Print the results in a table format
 // Print the results in a table format
    std::cout << "\nFeedback Details:\n";
    std::cout << std::string(120, '-') << std::endl;
    std::cout << std::left << std::setw(20) << "Student Username"
        << std::setw(20) << "Lecturer Name"
        << std::setw(20) << "Course Title"
        << std::setw(40) << "Feedback" << std::endl;
    std::cout << std::string(120, '-') << std::endl;

    while ((row = mysql_fetch_row(res))) {
        string studentUsername = row[0];
        string lecturerName = row[1];
        string courseTitle = row[2];
        string feedbackText = row[3];

        // Save data for file
        feedbackData.push_back({ studentUsername, lecturerName, courseTitle, feedbackText });

        // Display feedback
        std::cout << std::left << std::setw(20) << studentUsername
            << std::setw(20) << lecturerName
            << std::setw(20) << courseTitle
            << std::setw(40) << feedbackText << std::endl;
    }
    std::cout << std::string(120, '-') << std::endl;

    // Ask the user if they want to save the file
    char saveChoice;
    std::cout << "\nDo you want to save this feedback into a file? (Y/N): ";
    std::cin >> saveChoice;

    if (toupper(saveChoice) == 'Y') {
        std::ofstream outFile("course_feedback.txt");

        // Write table headers
        outFile << "\nFeedback Details:\n";
        outFile << std::string(80, '-') << "\n";
        outFile << std::left << std::setw(20) << "Student Username"
            << std::setw(20) << "Lecturer Name"
            << std::setw(20) << "Course Title"
            << std::setw(40) << "Feedback" << "\n";
        outFile << std::string(80, '-') << "\n";

        // Write feedback data
        for (const auto& row : feedbackData) {
            outFile << std::left << std::setw(20) << row[0]  // Student Username
                << std::setw(20) << row[1]  // Lecturer Name
                << std::setw(20) << row[2]  // Course Title
                << std::setw(40) << row[3]  // Feedback
                << "\n";
            outFile << std::string(80, '-') << "\n";
        }

        outFile.close();
        std::cout << "\033[32mFeedback has been successfully saved to 'course_feedback.txt'.\033[0m\n";
    }
    else {
        std::cout << "\nReturning to the previous menu..." << std::endl;
    }

    std::cout << "\nPress any key to return page View information...\n\n";
    (void)_getch();
    viewInformation(lecturerId, fullName);
}


void ViewCourses(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    int chViewCourses;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW MANAGEMENT COURSES", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << "1. Search by Course Code" << endl;
    cout << "2. List All Course Code" << endl;
    cout << "3. Return to View Information Management" << endl;
    cout << "4. Logout and Exit" << endl;
    cout << endl;
    cout << string(120, '-') << endl;
    cout << "Please enter your choice: ";
    cin >> chViewCourses;
    switch (chViewCourses) {
    case 1:
        searchCourseByCode(lecturerId, fullName);
        break;
    case 2:
        courseMenu(lecturerId, fullName);
        break;
    case 3:
        viewInformation(lecturerId, fullName);
        break;
    case 4:
        // Logout and back to Main Page
        cout << "Logging out ..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay
        exit(0); // Exit the program
    default:
        cout << "Invalid choice. Please try again." << endl;
        (void)_getch();
        ViewCourses(lecturerId, fullName);
        break;
    }

}

// Page Search Code Courses
void searchCourseByCode(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen
    string courseCode;

    const int consoleWidth = 120; // Define the width of the console
    cout << string(consoleWidth, '=') << endl;
    printCentered("SEARCH COURSE BY COURSE CODE", consoleWidth);
    cout << string(consoleWidth, '=') << endl;

    // Prompt the user to input the course code
    cin.ignore(); // Clear the input buffer
    cout << "Enter the Course Code to search: ";

    getline(cin, courseCode);

    // Trim the input
    courseCode.erase(0, courseCode.find_first_not_of(" \t\n\r"));
    courseCode.erase(courseCode.find_last_not_of(" \t\n\r") + 1);

    // Query to search for the course by its course code
    string query = "SELECT course_code, course_name, credits FROM courses WHERE course_code = '" + courseCode + "'";

    qstate = mysql_query(conn, query.c_str());

    // Check if the query was successful
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            // Display the course details
            row = mysql_fetch_row(res);
            cout << "\nCourse Details Found:\n";
            cout << string(120, '-') << endl;
            cout << "Course Code: " << row[0] << endl;
            cout << "Course Name: " << row[1] << endl;
            cout << "Credits: " << row[2] << endl;
            cout << string(120, '-') << endl;
        }
        else {
            cout << "\033[31mNo course found with the code: " << courseCode << "\033[0m" << endl;
            cout << "Press any key to proceed to this page...";
            (void)_getch();
            searchCourseByCode(lecturerId, fullName);
        }
    }
    else {
        cout << "\033[31mError executing query: " << mysql_error(conn) << "\033[0m" << endl;
    }

    // Prompt to return to the course menu
    cout << "\nPress any key to return to the View courses...";
    (void)_getch();
    ViewCourses(lecturerId, fullName);
}

void lecturerPage(int lecturerId, const string& fullName) {
    string departmentName;

    // Fetch department name based on lecturerId
    string query = "SELECT department_name FROM department WHERE lecturer_id = " + to_string(lecturerId);
    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res && mysql_num_rows(res) > 0) {
            MYSQL_ROW row = mysql_fetch_row(res);
            departmentName = row[0]; // Get the department name
            mysql_free_result(res);
        }
        else {
            departmentName = "Unknown Department"; // Default if no department found
        }
    }
    else {
        cout << "\033[31mError fetching department name: " << mysql_error(conn) << "\033[0m\n";
        departmentName = "Error Fetching Department";
    }

    while (true) {
        system("cls");

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("LECTURER DASHBOARD", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        cout << "Welcome, " << fullName << "!" << endl; // Welcome message
        cout << endl;
        // Display department name
        cout << "Department: " << departmentName << endl;
       
        cout << string(120, '-') << endl; // Separator line
        cout << "1. Input Student Marks" << endl;
        cout << "2. Update Student Marks" << endl;
        cout << "3. View Student Marks and Grades" << endl;
        cout << "4. Download Marks Records" << endl;
        cout << "5. View Course Feedback From Student" << endl;
        cout << "6. Logout" << endl;
        cout << string(120, '-') << endl; // Separator line
        cout << "Please enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            inputStudentMarks(lecturerId,fullName);
            break;
        case 2:
            updateStudentMarks(lecturerId, fullName);
            break;
        case 3:
            viewStudentMarksAndGrades(lecturerId,fullName);
            break;
        case 4:
            downloadMarksRecords(lecturerId, fullName);
            break;
        case 5:
            viewCourseFeedback(lecturerId, fullName);
            break;
        case 6:
            showLoadingScreen("\033[32mLogging out... Please wait.\033[0m");
            main(lecturerId, fullName);
        default:
            cout << "\nInvalid choice. Please try again." << endl;
            (void)_getch(); // Pause for user to acknowledge

        }
    }
}

void viewCourseFeedback(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW COURSE FEEDBACK", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;
    cout << endl;

    // Query to retrieve course feedback for the lecturer's courses
    string query =
        "SELECT f.feedback_id, c.course_name, f.feedback_text, f.date_submitted "
        "FROM feedback f "
        "JOIN courses c ON f.course_id = c.course_id "
        "JOIN course_lecturer cl ON c.course_id = cl.course_id "
        "WHERE cl.lecturer_id = " + to_string(lecturerId) +
        " AND f.feedback_type = 'Course feedback' "
        "ORDER BY f.date_submitted DESC";
    printLine();
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);

        if (res->row_count > 0) {
            // Display feedback in a tabular format
            cout << left << setw(20) << "Feedback ID"
                << setw(30) << "Course Name"
                << setw(50) << "Feedback Text"
                << setw(20) << "Date Submitted" << endl;
            printLine();

            // Vector to store feedback for downloading
            vector<string> feedbackData;

            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(20) << row[0]  // Feedback ID
                    << setw(30) << row[1]          // Course Name
                    << setw(50) << row[2]          // Feedback Text
                    << setw(20) << row[3] << endl; // Date Submitted

                // Store feedback data for download in tabular format
                stringstream ss;
                ss << left << setw(20) << row[0]  // Feedback ID
                    << setw(30) << row[1]          // Course Name
                    << setw(50) << row[2]          // Feedback Text
                    << setw(20) << row[3] << endl; // Date Submitted
                feedbackData.push_back(ss.str());
            }
            printLine();

            // Ask the user if they want to download the feedback
            char downloadChoice;
            cout << "\nDo you want to download the feedback to a Notepad file? (Y/N): ";
            cin >> downloadChoice;

            if (tolower(downloadChoice) == 'y') {
                // Save feedback data to a fixed .txt file name
                string fileName = "course_feedback.txt";
                ofstream file(fileName);

                if (file.is_open()) {
                    // Write feedback data to the file
                    for (const auto& feedback : feedbackData) {
                        file << feedback; // Write each feedback entry to the file
                    }

                    file.close();
                    string successMessage = "\nFeedback successfully downloaded to: " + fileName + "\n";

                    // Pass the constructed message to printSuccess
                    printSuccess(successMessage);
                }
                else {
                    cout << "\033[31mError: Unable to create file.\033[0m\n";
                }
            }
        }
        else {
            cout << "No feedback available for your courses." << endl;
        }
    }
    else {
        cout << "Error fetching feedback: " << mysql_error(conn) << endl;
    }

    cout << "\nPress any key to return to the dashboard...";
    (void)_getch();
    cout << endl;
    showLoadingScreen("Please Wait.....");
    lecturerPage(lecturerId, fullName);
}


// Main function to input student marks
void inputStudentMarks(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait...");
    system("cls");

    int courseId, choice, scoreTypeId1, scoreID;
    float scoreValue;
    string matricNumber, keyAlphabet;

    // Step 1: Display Courses Assigned to Lecturer
    const int consoleWidth = 120; // Define the width of the console
    cout << string(consoleWidth, '=') << endl;
    printCentered("INPUT STUDENT MARKS", consoleWidth);
    cout << string(consoleWidth, '=') << endl;

    cout << "Courses Assigned to You:\n";
    printLine();
    string query = "SELECT c.course_id, c.course_name "
        "FROM courses c JOIN course_lecturer cl ON c.course_id = cl.course_id "
        "WHERE cl.lecturer_id = " + to_string(lecturerId);

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mWarning: No courses have been assigned to you.\033[0m" << endl;
            printLine();
            cout << "\nPress Enter to return to the menu...";
            (void)_getch();
            return;
        }

        cout << left << setw(15) << "Course ID" << setw(40) << "Course Name" << endl;
        printLine();
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(40) << row[1] << endl;
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching courses: " << mysql_error(conn) << "\033[0m\n";
        return;
    }

    // Step 2: Select Course
    cout << "\nEnter Course ID to Add Marks: ";
    cin >> courseId;
    cin.ignore(); // Clear input buffer

    // Step 3: Show Available Score Types
    cout << "\nAvailable Score Types:\n";
    printLine();
    query = "SELECT score_type_id, score_title FROM score_types";
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mWarning: No score types found.\033[0m" << endl;
            printLine();
            return;
        }

        cout << left << setw(15) << "Score Type ID" << setw(30) << "Title" << endl;
        printLine();
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(30) << row[1] << endl;
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching score types: " << mysql_error(conn) << "\033[0m\n";
        return;
    }

    cout << "\nEnter Score Type ID: ";
    cin >> scoreTypeId1;

    // Step 4: Ask for Student Search Method
    cout << "\nSelect a Search Method:\n";
    cout << "1. View All Students\n";
    cout << "2. Search by Matric Number\n";
    cout << "3. Search by Key Alphabet (Full Name)\n";
    printLine();
    cout << "Enter Choice: ";
    cin >> choice;
    cin.ignore(); // Clear input buffer

    string studentQuery;

    // Step 5: Build Query Based on User Choice
    if (choice == 1) { // View All Students
        studentQuery =
            "SELECT sc.score_id, s.student_id, s.matrix_number, "
            "CONCAT(u.first_name, ' ', u.last_name) AS full_name "
            "FROM students s "
            "INNER JOIN scores sc ON s.student_id = sc.student_id "
            "LEFT JOIN score_mark sm ON sc.score_id = sm.score_id AND sm.score_type = " + to_string(scoreTypeId1) + " "
            "INNER JOIN users u ON u.user_id = s.student_id "
            "WHERE sc.course_id = " + to_string(courseId) + " AND sm.mark IS NULL";
    }
    else if (choice == 2) { // Search by Matric Number
        cout << "Enter Matric Number: ";
        getline(cin, matricNumber);
        studentQuery =
            "SELECT sc.score_id, s.student_id, s.matrix_number, "
            "CONCAT(u.first_name, ' ', u.last_name) AS full_name "
            "FROM students s "
            "INNER JOIN scores sc ON s.student_id = sc.student_id "
            "LEFT JOIN score_mark sm ON sc.score_id = sm.score_id AND sm.score_type = " + to_string(scoreTypeId1) + " "
            "INNER JOIN users u ON u.user_id = s.student_id "
            "WHERE sc.course_id = " + to_string(courseId) + " AND sm.mark IS NULL "
            "AND s.matrix_number = '" + matricNumber + " AND sm.mark IS NULL";
    }
    else if (choice == 3) { // Search by Key Alphabet (Full Name)
        cout << "Enter Starting Alphabet for Student Full Names: ";
        getline(cin, keyAlphabet);
        studentQuery =
            "SELECT sc.score_id, s.student_id, s.matrix_number, "
            "CONCAT(u.first_name, ' ', u.last_name) AS full_name "
            "FROM students s "
            "INNER JOIN scores sc ON s.student_id = sc.student_id "
            "LEFT JOIN score_mark sm ON sc.score_id = sm.score_id AND sm.score_type = " + to_string(scoreTypeId1) + " "
            "INNER JOIN users u ON u.user_id = s.student_id "
            "WHERE sc.course_id = " + to_string(courseId) + " AND sm.mark IS NULL "
            "AND CONCAT(u.first_name, ' ', u.last_name) LIKE '" + keyAlphabet + "%'"" AND sm.mark IS NULL";
    }
    else {
        cout << "\033[31mInvalid choice!\033[0m" << endl;
        
    }

    // Execute the query and directly set scoreID
    if (mysql_query(conn, studentQuery.c_str()) == 0) { // Execute the query
        MYSQL_RES* res = mysql_store_result(conn);      // Store the result
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);       // Fetch the first row
            if (row) {
                scoreID = atoi(row[0]);                // Convert the first column (scoreID) to an integer

            }
            else {
                cout << "No data found!" << endl;
            }
            mysql_free_result(res); // Free memory
        }
        else {
            cout << "Error retrieving result: " << mysql_error(conn) << endl;
        }
    }
    else {
        cout << "Query execution failed: " << mysql_error(conn) << endl;
    }

    // Step 6: Fetch Students Without Marks for Selected Course and Score Type
    qstate = mysql_query(conn, studentQuery.c_str());
    vector<pair<int, string>> students;
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mNo students found without marks for the selected course and score type.\033[0m" << endl;
            printLine();
          
        }

        cout << "\nStudents Without Marks:\n";
        printLine();
        cout << left << setw(15) << "Student ID" << setw(20) << "Matric Number" << setw(30) << "Full Name" << endl;
        printLine();
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[1] << setw(20) << row[2] << setw(30) << row[3] << endl;
            students.push_back({ stoi(row[1]), row[2] });
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching students: " << mysql_error(conn) << "\033[0m\n";
     
    }

    // Step 7: Update Marks for Each Student
    for (const auto& student : students) {
        bool validInput = false; // Track if a valid input was received
        while (!validInput) {    // Loop until a valid score is entered
            cout << "\nEnter Marks for Student (" << student.second << "): ";
            cin >> scoreValue;

            if (cin.fail() || scoreValue < 0 || scoreValue > 100) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "\033[33mInvalid input! Please enter a valid score between 0 and 100.\033[0m\n";
                continue;
            }

            // Update scoreID for the current student
            string updateQuery = "SELECT sc.score_id "
                "FROM scores sc "
                "WHERE sc.student_id = " + to_string(student.first) +
                " AND sc.course_id = " + to_string(courseId);

            qstate = mysql_query(conn, updateQuery.c_str());
            if (!qstate) {
                MYSQL_RES* scoreRes = mysql_store_result(conn);
                if (scoreRes) {
                    MYSQL_ROW scoreRow = mysql_fetch_row(scoreRes);
                    if (scoreRow) {
                        scoreID = stoi(scoreRow[0]); // Update scoreID for this student
                    }
                    mysql_free_result(scoreRes);
                }
            }
            else {
                cout << "\033[31mError fetching score ID for student: " << mysql_error(conn) << "\033[0m\n";
                continue;
            }

            // Insert marks for the current student
            string insertQuery =
                "INSERT INTO score_mark (score_id, mark, date_score, score_type) "
                "VALUES (" + to_string(scoreID) + ", " + to_string(scoreValue) + ", CURDATE(), " + to_string(scoreTypeId1) + ")";

            qstate = mysql_query(conn, insertQuery.c_str());
            if (qstate) {
                cout << "\033[31mFailed to add marks for student: " << student.second << "\033[0m\n";
            }
            else {
                cout << "\033[32mMarks added successfully for " << student.second << "!\033[0m\n";
                validInput = true; // Exit loop for this student
            }
        }

        // Ask whether to continue or stop after each student
        char continueChoice;
        cout << "\nDo you want to input marks for another student? (Y/N): ";
        cin >> continueChoice;
        if (toupper(continueChoice) == 'N') {
            cout << "\nExiting input process...\n";
            cout << endl;
            showLoadingScreen("Please Wait.....");
            lecturerPage(lecturerId, fullName); // Return to lecturer page
           
        }
    }


    cout << "\nAll marks have been added successfully.\nPress Enter to continue...";
    (void)_getch();
    cout << endl;
    showLoadingScreen("Please Wait.....");
    lecturerPage(lecturerId, fullName);

}


// Function to display updated marks
void displayUpdatedMarks(int courseId) {
    string query = "SELECT s.matrix_number, CONCAT(u.first_name, ' ', u.last_name) AS full_name, "
        "st.score_title, a.score "
        "FROM scores sc "
        "JOIN score_mark a ON sc.score_id = a.score_id "
        "JOIN students s ON sc.student_id = s.student_id "
        "JOIN users u ON u.user_id = s.student_id "
        "JOIN score_types st ON a.score_type = st.score_type_id "
        "WHERE sc.course_id = " + to_string(courseId);

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << left << setw(20) << "Matric Number" << setw(30) << "Full Name"
            << setw(20) << "Score Type" << setw(10) << "Score" << endl;
        printLine();

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(20) << row[0] << setw(30) << row[1]
                << setw(20) << row[2] << setw(10) << row[3] << endl;
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching updated marks: " << mysql_error(conn) << "\033[0m\n";
    }
}

// Function to update student marks
void updateStudentMarks(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait...");
    system("cls");

    int courseId, scoreTypeId;
    string selectedStudentId, keyAlphabet, matricNumber;
    float newScore;

    const int consoleWidth = 120;
    cout << string(consoleWidth, '=') << endl;
    printCentered("UPDATE STUDENT MARKS", consoleWidth);
    cout << string(consoleWidth, '=') << endl;

    // Display courses assigned to the lecturer
    cout << "Courses Assigned to You:\n";
    printLine();
    string query = "SELECT c.course_id, c.course_name "
        "FROM courses c JOIN course_lecturer cl ON c.course_id = cl.course_id "
        "WHERE cl.lecturer_id = " + to_string(lecturerId);

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mWarning: No courses have been assigned to you.\033[0m" << endl;
            return;
        }

        cout << left << setw(15) << "Course ID" << setw(40) << "Course Name" << endl;
        printLine();
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(40) << row[1] << endl;
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching courses: " << mysql_error(conn) << "\033[0m\n";
        return;
    }

    // Select course
    cout << "\nEnter Course ID to Update Marks: ";
    cin >> courseId;
    cin.ignore();

    // Search students by matric number or key alphabet
    int searchChoice;
    cout << "\nSearch Method:\n";
    cout << "1. Search by Matric Number\n";
    cout << "2. Search by Key Alphabet (Full Name)\n";
    cout << "3. View All Students\n";
    printLine();
    cout << "Enter Choice: ";
    cin >> searchChoice;
    cin.ignore();
    cout << endl;
    string studentQuery;
    if (searchChoice == 1) {
        cout << "Enter Matric Number: ";
        getline(cin, matricNumber);
        studentQuery = "SELECT sc.score_id, sm.mark_ID, s.matrix_number, "
            "CONCAT(u.first_name, ' ', u.last_name) AS full_name, ue.score_title, sm.mark "
            "FROM students s "
            "INNER JOIN scores sc ON s.student_id = sc.student_id "
            "INNER JOIN score_mark sm ON sc.score_id = sm.score_id "
            "INNER JOIN users u ON u.user_id = s.student_id "
            "INNER JOIN score_types ue ON sm.score_type = ue.score_type_id "
            "WHERE sc.course_id = " + to_string(courseId) + " "
            "AND s.matrix_number = '" + matricNumber + "' "
            "AND sm.mark IS NOT NULL "
            "AND ue.score_title LIKE 'PBL%' "
            "ORDER BY ue.score_title ASC";

    }
    else if (searchChoice == 2) {
        cout << "Enter Starting Alphabet for Full Names: ";
        getline(cin, keyAlphabet);
        studentQuery = "SELECT sc.score_id, sm.mark_ID, s.matrix_number, "
            "CONCAT(u.first_name, ' ', u.last_name) AS full_name, ue.score_title, sm.mark "
            "FROM students s "
            "INNER JOIN scores sc ON s.student_id = sc.student_id "
            "INNER JOIN score_mark sm ON sc.score_id = sm.score_id "
            "INNER JOIN users u ON u.user_id = s.student_id "
            "INNER JOIN score_types ue ON sm.score_type = ue.score_type_id "
            "WHERE sc.course_id = " + to_string(courseId) + " "
            "AND CONCAT(u.first_name, ' ', u.last_name) LIKE '" + keyAlphabet + "%' "
            "AND sm.mark IS NOT NULL "
            "AND ue.score_title LIKE 'PBL%' "
            "ORDER BY ue.score_title ASC";

    }
    else if (searchChoice == 3) {
        studentQuery = "SELECT sc.score_id, sm.mark_ID, s.matrix_number, "
            "CONCAT(u.first_name, ' ', u.last_name) AS full_name, ue.score_title, sm.mark "
            "FROM students s "
            "INNER JOIN scores sc ON s.student_id = sc.student_id "
            "INNER JOIN score_mark sm ON sc.score_id = sm.score_id "
            "INNER JOIN users u ON u.user_id = s.student_id "
            "INNER JOIN score_types ue ON sm.score_type = ue.score_type_id "
            "WHERE sc.course_id = " + to_string(courseId) + " "
            "AND sm.mark IS NOT NULL "
            "AND ue.score_title LIKE 'PBL%' "
            "ORDER BY ue.score_title ASC";

    }
    else {
        cout << "\033[31mInvalid choice!\033[0m" << endl;
        cout << "Please enter any key to continue..." << endl;
        (void)getch;
        // std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate delay
        showLoadingScreen("Processed to Back page....");
        lecturerPage(lecturerId, fullName);
    }

    // Fetch students
    qstate = mysql_query(conn, studentQuery.c_str());
    vector<pair<int, string>> students;

    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mNo students found based on your search.\033[0m" << endl;
            cout << "Please enter any key to continue..."<<endl;
            (void)getch;
           // std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate delay
            showLoadingScreen("Processed to Back page....");
            lecturerPage(lecturerId, fullName);
            
        }

        printLine();
        cout << left << setw(15) << "ID" << setw(20) << "Matric Number" << setw(30) << "Full Name" << setw(40) << "Score Title" << setw(20) << "Score" << endl;
        printLine();
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[1] << setw(20) << row[2] << setw(30) << row[3] << setw(40) << row[4] << setw(20) << row[5] << endl;
            students.push_back({ stoi(row[1]), row[3] });
        }
    }
    else {
        cout << "\033[31mError fetching students: " << mysql_error(conn) << "\033[0m\n";
        return;
    }
/*
    // Step 4: Display Score Types
    cout << "\nAvailable Score Types:\n";
    printLine();
    query = "SELECT score_type_id, score_title FROM score_types";
    qstate = mysql_query(conn, query.c_str());
    vector<pair<int, string>> scoreTypes;

    if (!qstate) {
        res = mysql_store_result(conn);
        cout << left << setw(15) << "Score Type ID" << setw(30) << "Title" << endl;
        printLine();

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(30) << row[1] << endl;
            scoreTypes.push_back({ stoi(row[0]), row[1] });
        }
    }
    */
    // Allow user to select a student by ID
    while (true) {
        printLine();
        cout << "\nEnter the Mark ID of the student to update (or type '0' to return): ";
        cin >> selectedStudentId;

        if (selectedStudentId == "0") {
            // std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate delay
            showLoadingScreen("Processed to Back page....");
            lecturerPage(lecturerId, fullName);
        }

        auto it = find_if(students.begin(), students.end(),
            [&](const pair<int, string>& student) { return to_string(student.first) == selectedStudentId; });

        if (it == students.end()) {
            cout << "\033[31mInvalid Student ID. Please try again.\033[0m" << endl;
            continue;
        }

        // Update marks for the selected student
        while (true) {
            cout << "\nUpdating Marks for Student (" << it->second << "):\n";
            cout << "Enter New Score: ";
            cin >> newScore;

            string updateQuery = "UPDATE score_mark "
                "SET mark = " + to_string(newScore) +
                " WHERE mark_ID = " + selectedStudentId + ";";


            qstate = mysql_query(conn, updateQuery.c_str());
            if (qstate) {
                cout << "\033[31mFailed to update marks for " << it->second << ": " << mysql_error(conn) << "\033[0m" << endl;
            }
            else {
                cout << "\033[32mMarks updated successfully for " << it->second << "!\033[0m" << endl;
            }

            char anotherScore;
            cout << "\nDo you want to update another score for this student? (y/n): ";
            cin >> anotherScore;

            if (anotherScore == 'n' || anotherScore == 'N') {
                break;
            }
        }
    }

    cout << "\nAll updates are completed. Press Enter to continue...";
    (void)_getch();
    cout << endl;
    showLoadingScreen("Please Wait.....");
    lecturerPage(lecturerId, fullName);
}

// Function to view student marks and grades 

void viewStudentMarksAndGrades(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait...");
    system("cls");

    int courseId;

    // Step 1: Display Courses Assigned to Lecturer
    const int consoleWidth = 120;
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("VIEW STUDENT MARKS AND GRADES ", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << "Courses Assigned to You:\n";

    printLine();
    string query = "SELECT c.course_id, c.course_name "
        "FROM courses c "
        "JOIN course_lecturer cl ON c.course_id = cl.course_id "
        "WHERE cl.lecturer_id = " + to_string(lecturerId);

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mWarning: No courses have been assigned to you.\033[0m" << endl;
            printLine();
            cout << "\nPress Enter to return to the menu...";
            (void)_getch();
            return;
        }

        cout << left << setw(15) << "Course ID" << setw(40) << "Course Name" << endl;
        printLine();

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(40) << row[1] << endl;
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching courses: " << mysql_error(conn) << "\033[0m\n";
        return;
    }

    // Select Course
    cout << "\nEnter Course ID to View Marks and Grades: ";
    cin >> courseId;
    printLine();
    // Step 2: Fetch Student Marks and Grades
    string marksQuery = "SELECT s.matrix_number, CONCAT(u.first_name, ' ', u.last_name) AS full_name, "
        "st.score_title, a.mark, gd.grade "
        "FROM scores sc "
        "INNER JOIN score_mark a ON sc.score_id = a.score_id "
        "INNER JOIN students s ON sc.student_id = s.student_id "
        "INNER JOIN users u ON u.user_id = s.student_id "
        "INNER JOIN score_types st ON a.score_type = st.score_type_id "
        "LEFT JOIN grade_definitions gd ON a.mark BETWEEN gd.min_score AND gd.max_score "
        "WHERE sc.course_id = " + to_string(courseId) + " "
        "ORDER BY st.score_title, s.matrix_number";

    qstate = mysql_query(conn, marksQuery.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mNo marks available for the selected course.\033[0m" << endl;
            printLine();
            cout << "\nPress Enter to return to the menu...";
            (void)_getch();
            cout << endl;
            showLoadingScreen("Please Wait...");
            lecturerPage(lecturerId, fullName);
        }

        // Display table header
        cout << left << setw(20) << "Matric Number"
            << setw(30) << "Full Name"
            << setw(20) << "Score Type"
            << setw(10) << "Marks"
            << setw(10) << "Grade" << endl;
        printLine();

        // Display student marks and grades
        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(20) << row[0]   // Matric Number
                << setw(30) << row[1]          // Full Name
                << setw(20) << row[2]          // Score Type
                << setw(10) << row[3]          // Marks
                << setw(10) << (row[4] ? row[4] : "N/A") << endl; // Grade or N/A if not found
        }
        printLine();

        // Call Grade Distribution Analysis
        analyzeGradeDistributionByScoreType(courseId);
        analyzeOverallGradeDistribution(courseId);
        //analyzePassFailDistribution(courseId);

    }
    else {
        cout << "\033[31mError fetching marks and grades: " << mysql_error(conn) << "\033[0m\n";
        return;
    }

    cout << "\nPress Enter to return to the menu...";
    (void)_getch();
    cout << endl;
    showLoadingScreen("Please Wait...");
    lecturerPage(lecturerId, fullName);
}


void displayGraph(map<string, int>& gradeData, const string& title) {
    const int graphWidth = 50;  // Maximum width of the graph
    const int scale = 2;        // Each '*' represents 2 people

    // Add a separator before the graph
    cout << "\n" << string(graphWidth, '-') << endl;

    // Add a distinct title for the graph
    string graphTitle = "Graph: " + title;
    printCentered(graphTitle, graphWidth); // Print the graph title
    cout << string(graphWidth, '-') << "\n";

    // Display each grade with a scaled bar
    for (const auto& grade : gradeData) {
        // Calculate the bar length based on the value, each '*' represents 2 people
        int barLength = grade.second / scale;

        // Print the grade label and the bar
        cout << left << setw(10) << grade.first << " | ";
        for (int i = 0; i < barLength; ++i) {
            if (barLength <= 2) {
                // All red if the bar length is 2 or less
                cout << "\033[31m*\033[0m";
            }
            else if (barLength > 2 && barLength <= 4) {
                // All orange if the bar length is more than 2 but 4 or less
                cout << "\033[33m*\033[0m"; // Orange
            }
            else {
                // All cyan if the bar length is more than 4
                cout << "\033[36m*\033[0m"; // Cyan
            }
        }

        // Display the actual value next to the bar
        cout << " (" << grade.second << " student)" << endl;
    }

    // Add a separator after the graph
    cout << string(graphWidth, '-') << "\n";

    // Add an explanation below the graph
    cout << "Note: Each '*' represents 2 students.\n";
    cout << string(graphWidth, '-') << "\n\n";
}

void analyzeGradeDistributionByScoreType(int courseId) {
    map<string, map<string, int>> scoreTypeGradeCount; // Nested map for score type and grade count
    map<string, int> scoreTypeStudentCount;           // Total student count per score type
    map<string, int> passFailByScoreType;             // Pass/Fail counts by score type (pass as positive, fail as negative)

    string query = "SELECT st.score_title, a.mark "
        "FROM scores sc "
        "JOIN score_mark a ON sc.score_id = a.score_id "
        "JOIN score_types st ON a.score_type = st.score_type_id "
        "WHERE sc.course_id = " + to_string(courseId);

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            string scoreType = row[0];
            float mark = stof(row[1]);
            string grade;

            // Determine grade based on marks
            if (mark >= 90) grade = "A+";
            else if (mark >= 80) grade = "A";
            else if (mark >= 75) grade = "A-";
            else if (mark >= 70) grade = "B+";
            else if (mark >= 65) grade = "B";
            else if (mark >= 60) grade = "B-";
            else if (mark >= 55) grade = "C+";
            else if (mark >= 50) grade = "C";
            else if (mark >= 45) grade = "C-";
            else if (mark >= 40) grade = "D+";
            else if (mark >= 35) grade = "D";
            else if (mark >= 30) grade = "D-";
            else grade = "F";

            // Update grade count for the specific score type
            scoreTypeGradeCount[scoreType][grade]++;
            scoreTypeStudentCount[scoreType]++;

            // Pass/Fail count for the specific score type
            if (mark >= 30) // Adjusted passing threshold to D-
                passFailByScoreType[scoreType]++; // Increment pass count
            else
                passFailByScoreType[scoreType]--; // Increment fail count (negative for tracking)
        }
    }
    else {
        cout << "\033[31mError fetching data: " << mysql_error(conn) << "\033[0m\n";
        return;
    }

    // Display Grade Distribution by Score Type
    const int consoleWidth = 120;
    for (const auto& scoreTypeEntry : scoreTypeGradeCount) {
        string scoreType = scoreTypeEntry.first;
        const auto& gradeCount = scoreTypeEntry.second;
        int totalStudents = scoreTypeStudentCount[scoreType];
        int passCount = max(0, passFailByScoreType[scoreType]);  // Positive for Pass
        int failCount = abs(min(0, passFailByScoreType[scoreType]));  // Negative for Fail

        cout << string(consoleWidth, '=') << endl;
        printCentered("GRADE DISTRIBUTION FOR " + scoreType, consoleWidth);
        cout << string(consoleWidth, '=') << endl;

        cout << string(consoleWidth, '-') << endl;
        // Print table header
        cout << left << setw(15) << "Grade" << setw(20) << "Number of Students" << setw(15) << "Percentage (%)" << endl;
        cout << string(consoleWidth, '-') << endl;

        // Print each grade with count and percentage
        for (const auto& gradeEntry : gradeCount) {
            float percentage = (gradeEntry.second / (float)totalStudents) * 100;
            cout << left << setw(15) << gradeEntry.first << setw(20) << gradeEntry.second << setw(15) << fixed << setprecision(2) << percentage << endl;
        }

        cout << string(consoleWidth, '-') << endl;
        cout << "Pass: " << passCount << " students (" << fixed << setprecision(2) << (passCount * 100.0 / totalStudents) << "%)" << endl;
        cout << "Fail: " << failCount << " students (" << fixed << setprecision(2) << (failCount * 100.0 / totalStudents) << "%)" << endl;
        cout << "Total Students: " << totalStudents << "\n\n";

        // Add Graph for Grade Distribution
        displayGraph(scoreTypeGradeCount[scoreType], "Grade Distribution for " + scoreType);
    }
}

void analyzeOverallGradeDistribution(int courseId) {
    map<string, map<string, float>> studentScoresByType; // Students' scores categorized by score types
    map<string, string> studentNames; // Students' names
    map<string, int> overallGradeCount; // Grade distribution based on total scores
    map<string, string> studentGrades; // Students' grades
    int totalStudents = 0; // Total number of students
    int passCount = 0, failCount = 0; // Count of passed and failed students

    const float MODULE_WEIGHT = 0.7; // Module weight 70%
    const float FINAL_EXAM_WEIGHT = 0.3; // Final exam weight 30%

    // Fetch all scores including types
    string scoresQuery = "SELECT s.matrix_number, CONCAT(u.first_name, ' ', u.last_name) AS full_name, "
        "st.score_title, a.mark "
        "FROM scores sc "
        "JOIN score_mark a ON sc.score_id = a.score_id "
        "JOIN score_types st ON a.score_type = st.score_type_id "
        "JOIN students s ON sc.student_id = s.student_id "
        "JOIN users u ON s.student_id = u.user_id "
        "WHERE sc.course_id = " + to_string(courseId);

    qstate = mysql_query(conn, scoresQuery.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            string matrixNumber = row[0];
            string fullName = row[1];
            string scoreType = row[2];
            float mark = stof(row[3]);

            studentScoresByType[matrixNumber][scoreType] = mark; // Save score by type
            studentNames[matrixNumber] = fullName; // Save student name
        }
    }
    else {
        cout << "\033[31mError fetching scores: " << mysql_error(conn) << "\033[0m\n";
        return;
    }

    // Step 2: Calculate Overall Scores and Grade Distribution
    map<string, float> studentOverallScores;
    map<string, string> studentPassFailStatus;

    for (const auto& entry : studentScoresByType) {
        string matrixNumber = entry.first;
        const auto& scores = entry.second;

        // Normalize and weight scores
        float moduleScore = 0.0;
        float finalExamScore = 0.0;

        for (const auto& scoreEntry : scores) {
            if (scoreEntry.first == "Final Exam") {
                finalExamScore = scoreEntry.second;
            }
            else {
                moduleScore += scoreEntry.second;
            }
        }

        // Normalize module score (assume each component is out of 100)
        moduleScore = (moduleScore / (scores.size() - 1)); // Exclude final exam from module count

        // Calculate weighted total score
        float overallScore = (moduleScore * MODULE_WEIGHT) + (finalExamScore * FINAL_EXAM_WEIGHT);
        studentOverallScores[matrixNumber] = overallScore;

        // Determine grade based on overall score
        string grade;
        if (overallScore >= 90) grade = "A+";
        else if (overallScore >= 80) grade = "A";
        else if (overallScore >= 75) grade = "A-";
        else if (overallScore >= 70) grade = "B+";
        else if (overallScore >= 65) grade = "B";
        else if (overallScore >= 60) grade = "B-";
        else if (overallScore >= 55) grade = "C+";
        else if (overallScore >= 50) grade = "C";
        else if (overallScore >= 45) grade = "C-";
        else if (overallScore >= 40) grade = "D+";
        else if (overallScore >= 35) grade = "D";
        else if (overallScore >= 30) grade = "D-";
        else grade = "F";

        studentGrades[matrixNumber] = grade; // Save student grade
        overallGradeCount[grade]++;
        totalStudents++;

        // Count Pass/Fail
        if (overallScore >= 30) { // Adjusted passing threshold to D-
            passCount++;
            studentPassFailStatus[matrixNumber] = "Pass";
        }
        else {
            failCount++;
            studentPassFailStatus[matrixNumber] = "Fail";
        }
    }

    // Step 3: Display Overall Grade Distribution
    const int consoleWidth = 120;
    cout << string(consoleWidth, '=') << endl;
    printCentered("OVERALL GRADE DISTRIBUTION", consoleWidth);
    cout << string(consoleWidth, '=') << endl;

    cout << string(consoleWidth, '-') << endl;
    // Print table header
    cout << left << setw(15) << "Grade" << setw(20) << "Number of Students" << setw(15) << "Percentage (%)" << endl;
    cout << string(consoleWidth, '-') << endl;

    for (const auto& gradeEntry : overallGradeCount) {
        float percentage = (gradeEntry.second / (float)totalStudents) * 100;
        cout << left << setw(15) << gradeEntry.first << setw(20) << gradeEntry.second << setw(15) << fixed << setprecision(2) << percentage << endl;
    }

    cout << string(consoleWidth, '-') << endl;
    cout << "Pass: " << passCount << " students (" << fixed << setprecision(2) << (passCount * 100.0 / totalStudents) << "%)" << endl;
    cout << "Fail: " << failCount << " students (" << fixed << setprecision(2) << (failCount * 100.0 / totalStudents) << "%)" << endl;
    cout << "Total Students: " << totalStudents << "\n\n";

    // Add Graph for Overall Grade Distribution
    displayGraph(overallGradeCount, "Overall Grade Distribution");

    // Step 4: Display Pass/Fail Details
    cout << string(consoleWidth, '=') << endl;
    printCentered("PASS/FAIL DETAILS", consoleWidth);
    cout << string(consoleWidth, '=') << endl;

    cout << left << setw(15) << "Matrix Number"
        << setw(30) << "Full Name"
        << setw(15) << "Status"
        << setw(10) << "Score"
        << setw(10) << "Grade" << endl;
    cout << string(consoleWidth, '-') << endl;

    for (const auto& entry : studentOverallScores) {
        string matrixNumber = entry.first;
        string fullName = studentNames[matrixNumber]; // Get student's name
        float overallScore = entry.second;
        string status = studentPassFailStatus[matrixNumber];
        string grade = studentGrades[matrixNumber]; // Get student's grade

        cout << left << setw(15) << matrixNumber
            << setw(30) << fullName
            << setw(15) << status
            << setw(10) << fixed << setprecision(2) << overallScore
            << setw(10) << grade << endl;
    }
    cout << string(consoleWidth, '-') << endl;
}


void downloadMarksRecords(int lecturerId, const string& fullName) {
    showLoadingScreen("\nPlease Wait...");
    system("cls");

    int courseId;
    string fileName = "marks_records.txt"; // Save as a text file for table design

    // Step 1: Display Courses Assigned to Lecturer
    const int consoleWidth = 120;
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("DOWNLOAD MARKS RECORDS ", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;
    // cout << "===== Download Marks Records =====\n";
    cout << "Courses Assigned to You:\n";

    printLine();
    string query = "SELECT c.course_id, c.course_name "
        "FROM courses c "
        "JOIN course_lecturer cl ON c.course_id = cl.course_id "
        "WHERE cl.lecturer_id = " + to_string(lecturerId);

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mWarning: No courses have been assigned to you.\033[0m" << endl;
              qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mWarning: No courses have been assigned to you.\033[0m" << endl;
            (void)getch;
           // std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate delay
            showLoadingScreen("Processed to Back page....");
            lecturerPage(lecturerId, fullName);
        }

        cout << left << setw(15) << "Course ID" << setw(40) << "Course Name" << endl;
        printLine();

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(40) << row[1] << endl;
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching courses: " << mysql_error(conn) << "\033[0m\n";
       (void)getch;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate delay
        //showLoadingScreen("Processed to Back page....");
        lecturerPage(lecturerId, fullName);
    }
        }

        cout << left << setw(15) << "Course ID" << setw(40) << "Course Name" << endl;
        printLine();

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(15) << row[0] << setw(40) << row[1] << endl;
        }
        printLine();
    }
    else {
        cout << "\033[31mError fetching courses: " << mysql_error(conn) << "\033[0m\n";
       (void)getch;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate delay
        //showLoadingScreen("Processed to Back page....");
        lecturerPage(lecturerId, fullName);
    }

    // Select Course
    cout << "\nEnter Course ID to Download Marks: ";
    cin >> courseId;

    // Step 2: Fetch Marks Records
    string marksQuery = "SELECT s.matrix_number, CONCAT(u.first_name, ' ', u.last_name) AS student_name, "
        "st.score_title, a.mark, CONCAT(ul.first_name, ' ', ul.last_name) AS lecturer_name, ak.department_short_name, ad.course_name,"
        "CONCAT(ul.first_name, ' ', ul.last_name) AS lecturer_name, "
        "ak.department_name, "
        "ad.course_name "
        "FROM scores sc "
        "JOIN score_mark a ON sc.score_id = a.score_id "
        "JOIN students s ON sc.student_id = s.student_id "
        "JOIN courses ad ON sc.course_id = ad.course_id "
        "JOIN course_lecturer an ON ad.course_id = an.course_id "
        "JOIN department ak ON ak.lecturer_id = an.lecturer_id "
        "JOIN users u ON u.user_id = s.student_id "
        "JOIN users ul ON ul.user_id = an.lecturer_id "
        "JOIN score_types st ON a.score_type = st.score_type_id "
        "WHERE sc.course_id = " + to_string(courseId) + " "
        "ORDER BY st.score_title ASC";


    qstate = mysql_query(conn, marksQuery.c_str());
    if (!qstate) {
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            cout << "\033[33mNo marks available for the selected course.\033[0m" << endl;
            return;
        }

        // Step 3: Write Data to File in Table Design
        ofstream outFile(fileName);
        if (!outFile.is_open()) {
            cout << "\033[31mError: Unable to create file.\033[0m\n";
            return;
        }

        // Write Table Header
        outFile << "View Record Mark" << endl;
        outFile << " " << endl;
        outFile << string(180, '-') << endl;
        outFile << left << setw(24) << "Matric Number"
            << setw(20) << "Full Name"
            << setw(28) << "Lecturer Name"
            << setw(18) << "Department"
            << setw(38) << "Course"
            << setw(18) << "Score Type"
            << "Marks" << endl;
        outFile << string(180, '-') << endl;

        // Write Data Rows
        while ((row = mysql_fetch_row(res))) {
            outFile << left << setw(24) << row[0]    // Matric Number
                << setw(20) << row[1]           // Full Name
                << setw(28) << row[4]
                << setw(18) << row[5]
                << setw(38) << row[6]
                << setw(18) << row[2]           // Score Type
                << row[3] << endl;              // Marks
        }

        // Close the file
        outFile.close();

        // Step 4: Confirmation
        cout << "\033[32mMarks records have been successfully saved to: " << fileName << "\033[0m\n";

    }
    else {
        cout << "\033[31mError fetching marks records: " << mysql_error(conn) << "\033[0m\n";
        (void)getch;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate delay
        //showLoadingScreen("Processed to Back page....");
        lecturerPage(lecturerId, fullName);
    }

    cout << "\nPress Enter to return to the menu...";
    (void)_getch();
    cout << endl;
    showLoadingScreen("Please Wait...");
    lecturerPage(lecturerId, fullName);
}

void studentPage(const string& fullName, int studentId, int lecturerId) {
    int choice;
    string email, matrixNumber = "", major = "";

    // Admin contact details
    const string adminPhoneNumber = "012-3456789"; // Replace with actual phone number

    // Query to fetch student details
    string query = "SELECT u.email, s.matrix_number, s.major "
        "FROM users u "
        "JOIN students s ON u.user_id = s.student_id "
        "WHERE u.user_id = " + to_string(studentId);

    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (row && row[0]) {
            email = row[0];
            matrixNumber = row[1] ? row[1] : ""; // Matrix number can be NULL
            major = row[2] ? row[2] : "";       // Major can be NULL
        }
        else {
            // Custom error with printError
            printWarning("\nNotice: Student details for \"" + fullName + "\" are not Assign yet.");
            printWarning("\nPlease contact the admin at: \"" + adminPhoneNumber + "\"");

            return;
        }
    }
    else {
        printError("Database error: " + string(mysql_error(conn)));
        return;
    }

    while (true) {
        system("cls");

        const int consoleWidth = 120; // Define the width of the console
        // Print top border
        cout << string(consoleWidth, '=') << endl;
        // Print centered title
        printCentered("STUDENT DASHBOARD", consoleWidth);
        // Print bottom border
        cout << string(consoleWidth, '=') << endl;

        cout << "\nWelcome, " << fullName << "!" << endl;

        // Display email
        cout << "Email: " << email << endl;

        // Display matrix number and major only if they exist
        if (!matrixNumber.empty()) {
            cout << "Matrix Number: " << matrixNumber << endl;
        }
        if (!major.empty()) {
            cout << "Major: " << major << endl;
        }

        cout << string(120, '-') << endl;
        cout << "1. Check Assigned Courses" << endl;
        cout << "2. View Grades" << endl;
        cout << "3. Provide Feedback" << endl;
        cout << "4. Logout" << endl;
        cout << string(120, '-') << endl;
        cout << "Please enter your choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            viewAssignedCourses(studentId, fullName, lecturerId);
            break;
        case 2:
            viewGrades(studentId, fullName, lecturerId);
            break;
        case 3:
            provideFeedback(studentId, fullName, lecturerId);
            break;
        case 4:
            showLoadingScreen("\033[32mLogging out... Please wait.\033[0m");
            main(lecturerId, fullName);
        default:
            cout << "Invalid choice. Please try again." << endl;
            (void)_getch();
        }
    }
}

void viewAssignedCourses(int studentId, const string& fullName, int lecturerId) {
    showLoadingScreen("\nPlease Wait..");
    system("cls"); // Clear the screen

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("ASSIGNED COURSES", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << endl;
    cout << string(120, '-') << endl;
    string query = "SELECT c.course_name, c.course_code, c.credits "
        "FROM COURSES c "
        "INNER JOIN SCORES s ON c.course_id = s.course_id "
        "WHERE s.student_id = " + to_string(studentId);

    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        res = mysql_store_result(conn);
        if (res && mysql_num_rows(res) > 0) {
            // Table Header
            cout << left << setw(30) << "Course Name"
                << setw(20) << "Course Code"
                << setw(10) << "Credits" << endl;
            printLine();

            // Display Data Rows
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(30) << (row[0] ? row[0] : "N/A")   // Course Name
                    << setw(20) << (row[1] ? row[1] : "N/A")          // Course Code
                    << setw(10) << (row[2] ? row[2] : "N/A") << endl; // Credits
            }
            printLine();
        }
        else {
            cout << "No courses assigned." << endl;
        }
    }
    else {
        cout << "Error fetching courses: " << mysql_error(conn) << endl;
    }

    cout << "\nPress any key to return to the dashboard...\n\n";
    (void)_getch();
    showLoadingScreen("Please Wait....");
    studentPage(fullName, studentId, lecturerId);
}



// View Grades with Table Style
void viewGrades(int studentId, const string& fullName, int lecturerId) {
    if (studentId <= 0) {
        cerr << "Error: Invalid Student ID provided." << endl;
        return;
    }

    showLoadingScreen("\nPlease Wait...");
    system("cls");

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    printCentered("VIEW GRADES", consoleWidth);
    cout << string(consoleWidth, '=') << endl;
    cout << endl;

    // SQL query to fetch all relevant scores
    string query = "SELECT c.course_name, st.score_title, ac.mark, gd.grade, ac.date_score "
        "FROM scores s "
        "INNER JOIN score_mark ac ON s.score_id = ac.score_id "
        "INNER JOIN courses c ON s.course_id = c.course_id "
        "INNER JOIN score_types st ON ac.score_type = st.score_type_id "
        "LEFT JOIN grade_definitions gd ON ac.mark BETWEEN gd.min_score AND gd.max_score "
        "WHERE s.student_id = " + to_string(studentId) + " "
        "ORDER BY c.course_name ASC, st.score_title ASC, ac.date_score DESC";

    // Execute query
    qstate = mysql_query(conn, query.c_str());
    if (qstate != 0) {
        cerr << "Error: Query failed - " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        cerr << "Error: Failed to store result - " << mysql_error(conn) << endl;
        return;
    }

    // Initialize variables
    string currentCourse = "";
    double pblTotal = 0.0, exercise = 0.0, finalExam = 0.0;

    // Map to store overall course totals
    map<string, double> courseTotals;

    // Open file for export
    ofstream outFile("student_grades.txt");

    // Loop through each row in the result set
    while ((row = mysql_fetch_row(res))) {
        string courseName = row[0] ? row[0] : "N/A";    // Course Name
        string scoreType = row[1] ? row[1] : "N/A";     // Score Type
        double score = row[2] ? stod(row[2]) : 0.0;     // Score
        string grade = row[3] ? row[3] : "N/A";         // Grade
        string dateScored = row[4] ? row[4] : "N/A";    // Date Scored

       
        // If course changes, print the previous course summary and reset values
        if (currentCourse != courseName && !currentCourse.empty()) {
            // Print summary for the previous course
            double normalizedTotal = printCourseSummary(currentCourse, pblTotal, exercise, finalExam);

            // Store the normalized total in the map
            courseTotals[currentCourse] = normalizedTotal;

            outFile << string(consoleWidth, '-') << "\n";
            outFile << endl;

            // Write course summary to file
            outFile << "Summary for Course: " << currentCourse << "\n";
            outFile << "PBL Total: " << fixed << setprecision(2) << pblTotal << " (50%)\n";
            outFile << "Exercise: " << fixed << setprecision(2) << exercise << " (20%)\n";
            outFile << "Final Exam: " << fixed << setprecision(2) << finalExam << " (30%)\n";
            outFile << "Normalized Total: " << fixed << setprecision(2) << normalizedTotal << " / 100\n\n";

            // Reset accumulators
            pblTotal = 0.0;
            exercise = 0.0;
            finalExam = 0.0;
        }

        // Print table header for the new course
        if (currentCourse != courseName) {
            currentCourse = courseName;

            cout << "\n" << string(consoleWidth, '-') << endl;
            cout << left << setw(40) << "Course Name"
                << setw(20) << "Score Type"
                << setw(10) << "Score"
                << setw(10) << "Grade"
                << setw(15) << "Date Scored" << endl;
            cout << string(consoleWidth, '-') << endl;

            // Write table header to file
            outFile << string(consoleWidth, '-') << "\n";
            outFile << left << setw(40) << "Course Name"
                << setw(20) << "Score Type"
                << setw(10) << "Score"
                << setw(10) << "Grade"
                << setw(15) << "Date Scored" << "\n";
            outFile << string(consoleWidth, '-') << "\n";
        }

        // Print row
        cout << left << setw(40) << courseName
            << setw(20) << scoreType
            << setw(10) << score
            << setw(10) << grade
            << setw(15) << dateScored << endl;

        // Write row to file
        outFile << left << setw(40) << courseName
            << setw(20) << scoreType
            << setw(10) << score
            << setw(10) << grade
            << setw(15) << dateScored << "\n";
       
        // Accumulate scores based on type
        if (scoreType.find("PBL") != string::npos) {
            pblTotal += score;
        }
        else if (scoreType == "Exercise") {
            exercise = score;
        }
        else if (scoreType == "Final") {
            finalExam = score;
        }
        
    }
    
    outFile << string(consoleWidth, '-') << endl;

    // Print summary for the last course
    if (!currentCourse.empty()) {
        double normalizedTotal = printCourseSummary(currentCourse, pblTotal, exercise, finalExam);
        courseTotals[currentCourse] = normalizedTotal;

        // Write summary for the last course to the file
        outFile << "Summary for Course: " << currentCourse << "\n";
        outFile << "PBL Total: " << fixed << setprecision(2) << pblTotal << " (50%)\n";
        outFile << "Exercise: " << fixed << setprecision(2) << exercise << " (20%)\n";
        outFile << "Final Exam: " << fixed << setprecision(2) << finalExam << " (30%)\n";
        outFile << "Normalized Total: " << fixed << setprecision(2) << normalizedTotal << " / 100\n\n";
    }

    mysql_free_result(res); // Free the result set
    cout << string(consoleWidth, '-') << endl;

    // Print overall summary
    printOverallSummary(courseTotals);

    // Write overall summary to the file
    outFile << "\nOverall Summary:\n";
    outFile << string(consoleWidth, '-') << "\n";
    outFile << left << setw(40) << "Course Name"
        << setw(30) << "Normalized Total (/100)"
        << setw(10) << "Grade" << endl;
    outFile << string(consoleWidth, '-') << "\n";

    for (const auto& entry : courseTotals) {
        string grade = getGradeForScore(entry.second);
        outFile << left << setw(40) << entry.first
            << setw(30) << fixed << setprecision(2) << entry.second
            << setw(10) << grade << "\n";
    }
    outFile << string(consoleWidth, '-') << "\n";

    outFile.close();

    // Ask user about download
    char downloadChoice;
    cout << "\nDo you want to download the grades as a file? (y/n): ";
    cin >> downloadChoice;

    if (downloadChoice == 'y' || downloadChoice == 'Y') {
        printSuccess( "\nGrades have been saved to 'student_grades.txt'. You can download the file.\n");
    }
    else if (downloadChoice == 'n' || downloadChoice == 'N') {
        printWarning ("\nYou chose not to download the grades. Returning to the dashboard...\n");
    }
    else {
        printWarning( "\nInvalid choice! No file downloaded. Returning to the dashboard...\n");
    }

    cout << "\nPress any key to return to the dashboard...\n\n";
    (void)_getch();
    showLoadingScreen("Please Wait....");
    studentPage(fullName, studentId, lecturerId);
}



// Helper function to print course summary
double printCourseSummary(const string& courseName, double pblTotal, double exercise, double finalExam) {
    double normalizedTotal = (pblTotal / 500.0 * 50) + (exercise / 100.0 * 20) + (finalExam / 100.0 * 30);
    printLine();
    cout << "\nSummary for Course: " << courseName << endl;
    cout << "PBL Total: " << fixed << setprecision(2) << pblTotal << " (50%)" << endl;
    cout << "Exercise: " << fixed << setprecision(2) << exercise << " (20%)" << endl;
    cout << "Final Exam: " << fixed << setprecision(2) << finalExam << " (30%)" << endl;
    cout << "Normalized Total: " << fixed << setprecision(2) << normalizedTotal << " / 100" << endl;
 
    return normalizedTotal;
}

// Helper function to print overall summary
void printOverallSummary(const map<string, double>& courseTotals) {
    cout << "\n" << string(120, '=') << endl;
    printCentered("OVERALL SUMMARY", 120);
    cout << string(120, '=') << endl;
    cout << endl;
    cout << endl;
    printLine();
    // Table header
    cout << left << setw(40) << "Course Name"
        << setw(30) << "Normalized Total (/100)"
        << setw(10) << "Grade" << endl;
    printLine();

    // Print each course total with grades
    for (const auto& entry : courseTotals) {
        string courseName = entry.first;
        double normalizedTotal = entry.second;
        string grade = getGradeForScore(normalizedTotal); // Get grade based on score

        cout << left << setw(40) << courseName
            << setw(30) << fixed << setprecision(2) << normalizedTotal
            << setw(10) << grade << endl;
    }

    cout << string(120, '-') << endl;
}

// Helper function to get grade for a given score
string getGradeForScore(double score) {
    string grade = "N/A";

    // Query the grade_definitions table to get the grade
    string query = "SELECT grade FROM grade_definitions WHERE " + to_string(score) +
        " BETWEEN min_score AND max_score";

    qstate = mysql_query(conn, query.c_str());
    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row && row[0]) {
                grade = row[0];
            }
            mysql_free_result(res);
        }
    }
    else {
        cerr << "Error: Failed to fetch grade - " << mysql_error(conn) << endl;
    }

    return grade;
}

void provideFeedback(int studentId, const string& fullName, int lecturerId) {
    system("cls");
    int feedbackChoice;

    const int consoleWidth = 120; // Define the width of the console
    // Print top border
    cout << string(consoleWidth, '=') << endl;
    // Print centered title
    printCentered("PROVIDE FEEDBACK", consoleWidth);
    // Print bottom border
    cout << string(consoleWidth, '=') << endl;

    cout << endl;
    cout << " 1. Feedback on a Course" << endl;
    cout << " 2. Feedback on the System" << endl;
    cout << " 3. Return to Dashboard" << endl;
    cout << string(120, '-') << endl;
    cout << endl;
    cout << "Please enter your choice: ";
    cin >> feedbackChoice;
    cin.ignore(); // Clear the input buffer

    if (feedbackChoice == 1) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen
        // Course Feedback
        int courseId;
        string feedback;

        // Query to fetch courses the student is enrolled in
        string query = "SELECT DISTINCT c.course_id, c.course_name "
            "FROM courses c "
            "JOIN scores s ON c.course_id = s.course_id "
            "WHERE s.student_id = " + to_string(studentId) +
            " ORDER BY c.course_id ASC";

        qstate = mysql_query(conn, query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);

            if (res->row_count > 0) {
                // Display available courses
                cout << "\n Courses you are enrolled in:\n";
                cout << string(120, '-') << endl;
                cout << " Course ID | Course Name" << endl;
                cout << string(120, '-') << endl;

                while ((row = mysql_fetch_row(res))) {
                    cout << " " << row[0] << "         | " << row[1] << endl;
                }
                printLine();

                // Prompt user to select a course
                cout << "\nEnter the Course ID to provide feedback: ";
                cin >> courseId;
                cin.ignore(); // Clear input buffer
                cout << endl;

                cout << " Enter your feedback: ";
                getline(cin, feedback);

                // Insert feedback into the database
                string insertQuery = "INSERT INTO feedback (user_id, feedback_type, course_id, feedback_text) "
                    "VALUES (" + to_string(studentId) +
                    ", 'Course feedback', " + to_string(courseId) + ", '" + feedback + "')";
                qstate = mysql_query(conn, insertQuery.c_str());

                if (!qstate) {
                    cout << "\nThank you for your feedback on the course!" << endl;
                    //cout << string(120, '-') << endl;
                }
                else {
                    cout << "\nError submitting feedback: " << mysql_error(conn) << endl;
                }
            }
            else {
                cout << "You are not enrolled in any courses.\n";
            }
        }
        else {
            cout << "\nError retrieving courses: " << mysql_error(conn) << endl;
        }
    }
    else if (feedbackChoice == 2) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen
        // System Feedback
        string feedback;

        cout << "\nEnter your feedback on the system: ";
        getline(cin, feedback);

        // Insert system feedback into the database
        string insertQuery = "INSERT INTO feedback (user_id, feedback_type, feedback_text) "
            "VALUES (" + to_string(studentId) + ", 'System feedback', '" + feedback + "')";
        qstate = mysql_query(conn, insertQuery.c_str());

        if (!qstate) {
            cout << "\nThank you for your feedback on the system!" << endl;
        }
        else {
            cout << "\nError submitting feedback: " << mysql_error(conn) << endl;
        }
    }
    else if (feedbackChoice == 3) {
        showLoadingScreen("\nPlease Wait..");
        system("cls"); // Clear the screen
        // Return to Dashboard
        return;
    }
    else {
        cout << "Invalid choice. Returning to Dashboard..." << endl;
    }

    cout << "\nPress any key to return to the dashboard...\n\n";
    (void)_getch();
    showLoadingScreen("Please Wait....");
    studentPage(fullName, studentId, lecturerId);
}
