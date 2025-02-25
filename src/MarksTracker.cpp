#include "../include/MarksTracker.h"
#include <algorithm>
#include <iomanip>

MarksTracker::MarksTracker(const std::string &username) : username(username)
{
    marksFilePath = "data/marks_" + username + ".txt";
    cgpaFilePath = "data/cgpa_" + username + ".txt";
    loadMarks();
    loadCGPA();
}

bool MarksTracker::loadMarks()
{
    std::ifstream inFile(marksFilePath);
    if (!inFile.is_open())
    {
        return false;
    }

    marks.clear();

    std::string line;
    while (std::getline(inFile, line))
    {
        SubjectMarks mark;
        size_t pos = 0;

        // Parse subject
        pos = line.find(',');
        mark.subject = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse obtained marks
        pos = line.find(',');
        mark.obtained = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Parse total marks
        pos = line.find(',');
        mark.total = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Parse credits
        mark.credits = std::stoi(line);

        marks.push_back(mark);
    }

    inFile.close();
    return true;
}

bool MarksTracker::saveMarks()
{
    std::ofstream outFile(marksFilePath);
    if (!outFile.is_open())
    {
        return false;
    }

    for (const auto &mark : marks)
    {
        outFile << mark.subject << ","
                << mark.obtained << ","
                << mark.total << ","
                << mark.credits << std::endl;
    }

    outFile.close();
    return true;
}

bool MarksTracker::loadCGPA()
{
    std::ifstream inFile(cgpaFilePath);
    if (!inFile.is_open())
    {
        return false;
    }

    semesterGPAs.clear();

    std::string line;
    while (std::getline(inFile, line))
    {
        SemesterGPA semGPA;
        size_t pos = 0;

        // Parse semester
        pos = line.find(',');
        semGPA.semester = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse GPA
        pos = line.find(',');
        semGPA.gpa = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Parse credits
        semGPA.credits = std::stoi(line);

        semesterGPAs.push_back(semGPA);
    }

    inFile.close();
    return true;
}

bool MarksTracker::saveCGPA()
{
    std::ofstream outFile(cgpaFilePath);
    if (!outFile.is_open())
    {
        return false;
    }

    for (const auto &semGPA : semesterGPAs)
    {
        outFile << semGPA.semester << ","
                << semGPA.gpa << ","
                << semGPA.credits << std::endl;
    }

    outFile.close();
    return true;
}

bool MarksTracker::addMarks(const std::string &subject, double obtained, double total, int credits)
{
    SubjectMarks newMark;
    newMark.subject = subject;
    newMark.obtained = obtained;
    newMark.total = total;
    newMark.credits = credits;

    // Check if subject already exists and update it
    auto it = std::find_if(marks.begin(), marks.end(),
                           [&subject](const SubjectMarks &mark)
                           { return mark.subject == subject; });

    if (it != marks.end())
    {
        *it = newMark;
    }
    else
    {
        marks.push_back(newMark);
    }

    return saveMarks();
}

void MarksTracker::viewMarks()
{
    if (marks.empty())
    {
        std::cout << "No marks found." << std::endl;
        return;
    }

    std::cout << "\n===================================================================\n";
    std::cout << std::left << std::setw(15) << "Subject" << " | "
              << std::setw(10) << "Obtained" << " | "
              << std::setw(10) << "Total" << " | "
              << std::setw(10) << "Percentage" << " | "
              << "Credits" << std::endl;
    std::cout << "===================================================================\n";

    for (const auto &mark : marks)
    {
        double percentage = (mark.obtained / mark.total) * 100;
        std::cout << std::left << std::setw(15) << mark.subject << " | "
                  << std::setw(10) << mark.obtained << " | "
                  << std::setw(10) << mark.total << " | "
                  << std::setw(10) << std::fixed << std::setprecision(2) << percentage << "% | "
                  << mark.credits << std::endl;
    }

    std::cout << "===================================================================\n";
    std::cout << "Overall Percentage: " << calculatePercentage() << "%" << std::endl;
    std::cout << "GPA: " << calculateGPA() << std::endl;
}

double MarksTracker::calculateGPA()
{
    if (marks.empty())
    {
        return 0.0;
    }

    double totalPoints = 0.0;
    int totalCredits = 0;

    for (const auto &mark : marks)
    {
        double percentage = (mark.obtained / mark.total) * 100;
        double gradePoint = 0.0;

        // Standard US GPA scale (adjust as needed)
        if (percentage >= 90)
            gradePoint = 4.0;
        else if (percentage >= 80)
            gradePoint = 3.0;
        else if (percentage >= 70)
            gradePoint = 2.0;
        else if (percentage >= 60)
            gradePoint = 1.0;

        totalPoints += gradePoint * mark.credits;
        totalCredits += mark.credits;
    }

    return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
}

double MarksTracker::calculatePercentage()
{
    if (marks.empty())
    {
        return 0.0;
    }

    double totalObtained = 0.0;
    double totalMarks = 0.0;

    for (const auto &mark : marks)
    {
        totalObtained += mark.obtained;
        totalMarks += mark.total;
    }

    return totalMarks > 0 ? (totalObtained / totalMarks) * 100 : 0.0;
}

bool MarksTracker::addSemesterGPA(const std::string &semester, double gpa, int credits)
{
    SemesterGPA newSemGPA;
    newSemGPA.semester = semester;
    newSemGPA.gpa = gpa;
    newSemGPA.credits = credits;

    // Check if semester already exists and update it
    auto it = std::find_if(semesterGPAs.begin(), semesterGPAs.end(),
                           [&semester](const SemesterGPA &semGPA)
                           { return semGPA.semester == semester; });

    if (it != semesterGPAs.end())
    {
        *it = newSemGPA;
    }
    else
    {
        semesterGPAs.push_back(newSemGPA);
    }

    return saveCGPA();
}

void MarksTracker::viewCGPAHistory()
{
    if (semesterGPAs.empty())
    {
        std::cout << "No CGPA history found." << std::endl;
        return;
    }

    std::cout << "\n===================================================================\n";
    std::cout << std::left << std::setw(15) << "Semester" << " | "
              << std::setw(10) << "GPA" << " | "
              << "Credits" << std::endl;
    std::cout << "===================================================================\n";

    for (const auto &semGPA : semesterGPAs)
    {
        std::cout << std::left << std::setw(15) << semGPA.semester << " | "
                  << std::setw(10) << std::fixed << std::setprecision(2) << semGPA.gpa << " | "
                  << semGPA.credits << std::endl;
    }

    std::cout << "===================================================================\n";
    std::cout << "Cumulative GPA: " << calculateCGPA() << std::endl;
}

double MarksTracker::calculateCGPA()
{
    if (semesterGPAs.empty())
    {
        return 0.0;
    }

    double totalPoints = 0.0;
    int totalCredits = 0;

    for (const auto &semGPA : semesterGPAs)
    {
        totalPoints += semGPA.gpa * semGPA.credits;
        totalCredits += semGPA.credits;
    }

    return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
}