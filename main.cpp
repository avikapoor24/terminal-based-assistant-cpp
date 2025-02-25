#include <iostream>
#include <string>
#include <limits>
#include "../include/Admin.h"
#include "../include/TaskManager.h"
#include "../include/MarksTracker.h"
#include "../include/Timetable.h"
#include "../include/Attendance.h"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMainMenu()
{
    std::cout << "\n=================================\n";
    std::cout << "   TERMINAL PERSONAL ASSISTANT   \n";
    std::cout << "=================================\n";
    std::cout << "1. Task Management\n";
    std::cout << "2. Academic Marks Tracker\n";
    std::cout << "3. Timetable Manager\n";
    std::cout << "4. Attendance Tracker\n";
    std::cout << "5. CGPA Calculator\n";
    std::cout << "6. Account Settings\n";
    std::cout << "0. Logout\n";
    std::cout << "=================================\n";
    std::cout << "Enter your choice: ";
}

void taskManagementMenu(TaskManager &taskManager)
{
    int choice;
    while (true)
    {
        clearScreen();
        std::cout << "\n=================================\n";
        std::cout << "      TASK MANAGEMENT MENU      \n";
        std::cout << "=================================\n";
        std::cout << "1. View All Tasks\n";
        std::cout << "2. Add New Task\n";
        std::cout << "3. Mark Task as Complete\n";
        std::cout << "4. Remove Task\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            taskManager.viewTasks();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 2:
        {
            std::string title, description, dueDate;
            int priority;

            std::cout << "Enter task title: ";
            std::getline(std::cin, title);

            std::cout << "Enter task description: ";
            std::getline(std::cin, description);

            std::cout << "Enter due date (YYYY-MM-DD): ";
            std::getline(std::cin, dueDate);

            std::cout << "Enter priority (1-5, 5 being highest): ";
            std::cin >> priority;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            taskManager.addTask(title, description, dueDate, priority);
            std::cout << "Task added successfully!\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 3:
        {
            int taskId;
            taskManager.viewTasks();
            std::cout << "Enter task ID to mark as complete: ";
            std::cin >> taskId;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            taskManager.markTaskComplete(taskId);
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 4:
        {
            int taskId;
            taskManager.viewTasks();
            std::cout << "Enter task ID to remove: ";
            std::cin >> taskId;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            taskManager.removeTask(taskId);
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 0:
            return;
        default:
            std::cout << "Invalid choice! Press Enter to continue...";
            std::cin.get();
            break;
        }
    }
}

void marksTrackerMenu(MarksTracker &marksTracker)
{
    int choice;
    while (true)
    {
        clearScreen();
        std::cout << "\n=================================\n";
        std::cout << "      MARKS TRACKER MENU        \n";
        std::cout << "=================================\n";
        std::cout << "1. View All Marks\n";
        std::cout << "2. Add Subject Marks\n";
        std::cout << "3. Calculate GPA\n";
        std::cout << "4. Calculate Percentage\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            marksTracker.viewMarks();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 2:
        {
            std::string subject;
            double obtained, total;
            int credits;

            std::cout << "Enter subject name: ";
            std::getline(std::cin, subject);

            std::cout << "Enter obtained marks: ";
            std::cin >> obtained;

            std::cout << "Enter total marks: ";
            std::cin >> total;

            std::cout << "Enter subject credits: ";
            std::cin >> credits;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            marksTracker.addMarks(subject, obtained, total, credits);
            std::cout << "Marks added successfully!\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 3:
            std::cout << "Current GPA: " << marksTracker.calculateGPA() << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        case 4:
            std::cout << "Overall Percentage: " << marksTracker.calculatePercentage() << "%" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice! Press Enter to continue...";
            std::cin.get();
            break;
        }
    }
}

void timetableMenu(Timetable &timetable)
{
    int choice;
    while (true)
    {
        clearScreen();
        std::cout << "\n=================================\n";
        std::cout << "       TIMETABLE MENU           \n";
        std::cout << "=================================\n";
        std::cout << "1. View Timetable\n";
        std::cout << "2. Add Event\n";
        std::cout << "3. Remove Event\n";
        std::cout << "4. Check for Schedule Conflicts\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            timetable.viewTimetable();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 2:
        {
            std::string day, title, startTime, endTime, location;

            std::cout << "Enter day (e.g., Monday): ";
            std::getline(std::cin, day);

            std::cout << "Enter event title: ";
            std::getline(std::cin, title);

            std::cout << "Enter start time (HH:MM): ";
            std::getline(std::cin, startTime);

            std::cout << "Enter end time (HH:MM): ";
            std::getline(std::cin, endTime);

            std::cout << "Enter location: ";
            std::getline(std::cin, location);

            timetable.addEvent(day, title, startTime, endTime, location);
            std::cout << "Event added successfully!\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 3:
        {
            int eventId;
            timetable.viewTimetable();
            std::cout << "Enter event ID to remove: ";
            std::cin >> eventId;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            timetable.removeEvent(eventId);
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 4:
            timetable.checkConflicts();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice! Press Enter to continue...";
            std::cin.get();
            break;
        }
    }
}

void attendanceMenu(Attendance &attendance)
{
    int choice;
    while (true)
    {
        clearScreen();
        std::cout << "\n=================================\n";
        std::cout << "      ATTENDANCE MENU           \n";
        std::cout << "=================================\n";
        std::cout << "1. View Attendance Record\n";
        std::cout << "2. Mark Attendance\n";
        std::cout << "3. Check Attendance Percentage\n";
        std::cout << "4. Check Low Attendance Alert\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            attendance.viewAttendance();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 2:
        {
            std::string subject, date, status;

            std::cout << "Enter subject name: ";
            std::getline(std::cin, subject);

            std::cout << "Enter date (YYYY-MM-DD): ";
            std::getline(std::cin, date);

            std::cout << "Enter attendance status (present/absent): ";
            std::getline(std::cin, status);

            attendance.markAttendance(subject, date, status);
            std::cout << "Attendance marked successfully!\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 3:
        {
            std::string subject;
            std::cout << "Enter subject name (or leave blank for overall): ";
            std::getline(std::cin, subject);

            double percentage = attendance.calculateAttendancePercentage(subject);
            if (subject.empty())
            {
                std::cout << "Overall attendance percentage: " << percentage << "%" << std::endl;
            }
            else
            {
                std::cout << "Attendance percentage for " << subject << ": " << percentage << "%" << std::endl;
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 4:
            attendance.checkLowAttendance();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice! Press Enter to continue...";
            std::cin.get();
            break;
        }
    }
}

void cgpaCalculatorMenu(MarksTracker &marksTracker)
{
    int choice;
    while (true)
    {
        clearScreen();
        std::cout << "\n=================================\n";
        std::cout << "       CGPA CALCULATOR           \n";
        std::cout << "=================================\n";
        std::cout << "1. View CGPA History\n";
        std::cout << "2. Add Semester GPA\n";
        std::cout << "3. Calculate CGPA\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            marksTracker.viewCGPAHistory();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 2:
        {
            std::string semester;
            double gpa;
            int credits;

            std::cout << "Enter semester (e.g., Fall 2023): ";
            std::getline(std::cin, semester);

            std::cout << "Enter GPA for this semester: ";
            std::cin >> gpa;

            std::cout << "Enter credits for this semester: ";
            std::cin >> credits;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            marksTracker.addSemesterGPA(semester, gpa, credits);
            std::cout << "Semester GPA added successfully!\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 3:
            std::cout << "Current CGPA: " << marksTracker.calculateCGPA() << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice! Press Enter to continue...";
            std::cin.get();
            break;
        }
    }
}

void accountSettingsMenu(Admin &admin)
{
    int choice;
    while (true)
    {
        clearScreen();
        std::cout << "\n=================================\n";
        std::cout << "      ACCOUNT SETTINGS MENU     \n";
        std::cout << "=================================\n";
        std::cout << "1. Change Username\n";
        std::cout << "2. Change Password\n";
        std::cout << "3. View Account Information\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "=================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            std::string newUsername;
            std::cout << "Enter new username: ";
            std::getline(std::cin, newUsername);

            admin.changeUsername(newUsername);
            std::cout << "Username changed successfully!\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 2:
        {
            std::string oldPassword, newPassword;
            std::cout << "Enter current password: ";
            std::getline(std::cin, oldPassword);

            std::cout << "Enter new password: ";
            std::getline(std::cin, newPassword);

            if (admin.changePassword(oldPassword, newPassword))
            {
                std::cout << "Password changed successfully!\n";
            }
            else
            {
                std::cout << "Failed to change password. Incorrect current password.\n";
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 3:
            admin.viewAccountInfo();
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice! Press Enter to continue...";
            std::cin.get();
            break;
        }
    }
}

int main()
{
    Admin admin;
    std::string username, password;
    bool isLoggedIn = false;

// Create data directory if it doesn't exist
#ifdef _WIN32
    system("mkdir data 2> nul");
#else
    system("mkdir -p data");
#endif

    clearScreen();
    std::cout << "=================================\n";
    std::cout << "   TERMINAL PERSONAL ASSISTANT   \n";
    std::cout << "=================================\n";

    // Check if admin exists, if not, create one
    if (!admin.adminExists())
    {
        std::cout << "No admin account found. Let's create one.\n";

        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        admin.createAdmin(username, password);
        std::cout << "Admin account created successfully!\n";
    }

    // Login loop
    while (!isLoggedIn)
    {
        clearScreen();
        std::cout << "=================================\n";
        std::cout << "            LOGIN               \n";
        std::cout << "=================================\n";

        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        isLoggedIn = admin.login(username, password);

        if (!isLoggedIn)
        {
            std::cout << "Invalid username or password. Press Enter to try again...";
            std::cin.get();
        }
    }

    // Initialize modules
    TaskManager taskManager(username);
    MarksTracker marksTracker(username);
    Timetable timetable(username);
    Attendance attendance(username);

    // Main menu loop
    int choice;
    while (true)
    {
        clearScreen();
        displayMainMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            taskManagementMenu(taskManager);
            break;
        case 2:
            marksTrackerMenu(marksTracker);
            break;
        case 3:
            timetableMenu(timetable);
            break;
        case 4:
            attendanceMenu(attendance);
            break;
        case 5:
            cgpaCalculatorMenu(marksTracker);
            break;
        case 6:
            accountSettingsMenu(admin);
            break;
        case 0:
            std::cout << "Logging out. Thank you for using Terminal Personal Assistant!\n";
            return 0;
        default:
            std::cout << "Invalid choice! Press Enter to continue...";
            std::cin.get();
            break;
        }
    }

    return 0;
}