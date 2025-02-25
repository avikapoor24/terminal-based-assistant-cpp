#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct Event
{
    int id;
    std::string day;
    std::string title;
    std::string startTime;
    std::string endTime;
    std::string location;
};

class Timetable
{
private:
    std::string username;
    std::vector<Event> events;
    std::string timetableFilePath;
    int nextEventId;

    // Helper functions
    bool loadTimetable();
    bool saveTimetable();
    int getNextEventId();
    bool isTimeConflict(const Event &event1, const Event &event2);
    int convertTimeToMinutes(const std::string &timeStr);

public:
    Timetable(const std::string &username);

    // Event operations
    bool addEvent(const std::string &day, const std::string &title,
                  const std::string &startTime, const std::string &endTime,
                  const std::string &location);
    bool removeEvent(int eventId);
    void viewTimetable();
    void checkConflicts();
    std::vector<Event> getEventsForDay(const std::string &day);
};

#endif // TIMETABLE_H