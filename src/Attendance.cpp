#include "../include/Attendance.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>

// Constructor
Attendance::Attendance(const std::string &username) : username(username)
{
    attendanceFilePath = "data/" + username + "_attendance.txt";
    loadAttendance();
}

// Destructor
Attendance::~Attendance()
{
    saveAttendance();
}

// Load attendance data from file
bool Attendance::loadAttendance()
{
    std::ifstream file(attendanceFilePath);
    if (!file)
    {
        std::cerr << "No existing attendance file found, starting fresh." << std::endl;
        return false;
    }

    records.clear();
    std::string subject, date, status;
    while (file >> subject >> date >> status)
    {
        records.push_back({subject, date, status});
    }
    file.close();
    return true;
}

// Save attendance data to file
bool Attendance::saveAttendance()
{
    std::ofstream file(attendanceFilePath);
    if (!file)
    {
        std::cerr << "Error: Could not save attendance file!" << std::endl;
        return false;
    }

    for (const auto &record : records)
    {
        file << record.subject << " " << record.date << " " << record.status << "\n";
    }
    file.close();
    return true;
}

// Fix: Mark attendance with subject, date, and status
bool Attendance::markAttendance(const std::string &subject, const std::string &date, const std::string &status)
{
    records.push_back({subject, date, status});
    return saveAttendance();
}

// View all attendance records
void Attendance::viewAttendance()
{
    if (records.empty())
    {
        std::cout << "No attendance records available.\n";
        return;
    }

    std::cout << "\nAttendance Records:\n";
    for (const auto &record : records)
    {
        std::cout << record.subject << " | " << record.date << " | " << record.status << "\n";
    }
}

// Calculate attendance percentage for a subject
double Attendance::calculateAttendancePercentage(const std::string &subject)
{
    int total = 0, attended = 0;
    for (const auto &record : records)
    {
        if (subject.empty() || record.subject == subject)
        {
            total++;
            if (record.status == "present")
                attended++;
        }
    }
    return total > 0 ? (attended / static_cast<double>(total)) * 100.0 : 0.0;
}

// Check subjects with low attendance
void Attendance::checkLowAttendance(double threshold)
{
    std::map<std::string, int> totalClasses, attendedClasses;
    for (const auto &record : records)
    {
        totalClasses[record.subject]++;
        if (record.status == "present")
            attendedClasses[record.subject]++;
    }

    std::cout << "\nSubjects with Low Attendance (< " << threshold << "%):\n";
    for (const auto &[subject, total] : totalClasses)
    {
        double percentage = total > 0 ? (attendedClasses[subject] / static_cast<double>(total)) * 100.0 : 0.0;
        if (percentage < threshold)
        {
            std::cout << subject << " - " << percentage << "%\n";
        }
    }
}
