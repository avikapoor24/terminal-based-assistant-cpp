#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

struct AttendanceRecord
{
    std::string subject;
    std::string date;
    std::string status; // "present" or "absent"
};

class Attendance
{
private:
    std::string username;
    std::vector<AttendanceRecord> records;
    std::string attendanceFilePath;

    // Helper functions
    bool loadAttendance();
    bool saveAttendance();

public:
    Attendance(const std::string &username);
    ~Attendance();

    // Fix: Updated function to match main.cpp
    bool markAttendance(const std::string &subject, const std::string &date, const std::string &status);

    void viewAttendance();
    double calculateAttendancePercentage(const std::string &subject = "");
    void checkLowAttendance(double threshold = 75.0);
};

#endif // ATTENDANCE_H
