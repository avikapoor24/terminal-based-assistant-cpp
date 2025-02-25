#ifndef MARKS_TRACKER_H
#define MARKS_TRACKER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct SubjectMarks
{
    std::string subject;
    double obtained;
    double total;
    int credits;
};

struct SemesterGPA
{
    std::string semester;
    double gpa;
    int credits;
};

class MarksTracker
{
private:
    std::string username;
    std::vector<SubjectMarks> marks;
    std::vector<SemesterGPA> semesterGPAs;
    std::string marksFilePath;
    std::string cgpaFilePath;

    // Helper functions
    bool loadMarks();
    bool saveMarks();
    bool loadCGPA();
    bool saveCGPA();

public:
    MarksTracker(const std::string &username);

    // Marks operations
    bool addMarks(const std::string &subject, double obtained, double total, int credits);
    void viewMarks();
    double calculateGPA();
    double calculatePercentage();

    // CGPA operations
    bool addSemesterGPA(const std::string &semester, double gpa, int credits);
    void viewCGPAHistory();
    double calculateCGPA();
};

#endif // MARKS_TRACKER_H