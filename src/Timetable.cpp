#include "../include/Timetable.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

Timetable::Timetable(const std::string &username) : username(username)
{
    timetableFilePath = "data/timetable_" + username + ".txt";
    loadTimetable();
    nextEventId = getNextEventId();
}

bool Timetable::loadTimetable()
{
    std::ifstream inFile(timetableFilePath);
    if (!inFile.is_open())
    {
        return false;
    }

    events.clear();

    std::string line;
    while (std::getline(inFile, line))
    {
        Event event;
        size_t pos = 0;

        // Parse event ID
        pos = line.find(',');
        event.id = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Parse day
        pos = line.find(',');
        event.day = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse title
        pos = line.find(',');
        event.title = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse start time
        pos = line.find(',');
        event.startTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse end time
        pos = line.find(',');
        event.endTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse location
        event.location = line;

        events.push_back(event);
    }

    inFile.close();
    return true;
}

bool Timetable::saveTimetable()
{
    std::ofstream outFile(timetableFilePath);
    if (!outFile.is_open())
    {
        return false;
    }

    for (const auto &event : events)
    {
        outFile << event.id << ","
                << event.day << ","
                << event.title << ","
                << event.startTime << ","
                << event.endTime << ","
                << event.location << std::endl;
    }

    outFile.close();
    return true;
}

int Timetable::getNextEventId()
{
    if (events.empty())
    {
        return 1;
    }

    int maxId = 0;
    for (const auto &event : events)
    {
        if (event.id > maxId)
        {
            maxId = event.id;
        }
    }

    return maxId + 1;
}

int Timetable::convertTimeToMinutes(const std::string &timeStr)
{
    int hours, minutes;
    char colon;
    std::istringstream ss(timeStr);
    ss >> hours >> colon >> minutes;

    return hours * 60 + minutes;
}

bool Timetable::isTimeConflict(const Event &event1, const Event &event2)
{
    // First check if they're on the same day
    if (event1.day != event2.day)
    {
        return false;
    }

    int start1 = convertTimeToMinutes(event1.startTime);
    int end1 = convertTimeToMinutes(event1.endTime);
    int start2 = convertTimeToMinutes(event2.startTime);
    int end2 = convertTimeToMinutes(event2.endTime);

    // Check for overlap
    return (start1 < end2 && start2 < end1);
}

bool Timetable::addEvent(const std::string &day, const std::string &title,
                         const std::string &startTime, const std::string &endTime,
                         const std::string &location)
{
    Event newEvent;
    newEvent.id = nextEventId++;
    newEvent.day = day;
    newEvent.title = title;
    newEvent.startTime = startTime;
    newEvent.endTime = endTime;
    newEvent.location = location;

    // Check for conflicts with existing events
    for (const auto &event : events)
    {
        if (isTimeConflict(newEvent, event))
        {
            std::cout << "Warning: This event conflicts with '" << event.title
                      << "' on " << event.day << " (" << event.startTime
                      << "-" << event.endTime << ")." << std::endl;

            std::cout << "Do you still want to add this event? (y/n): ";
            char response;
            std::cin >> response;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (response != 'y' && response != 'Y')
            {
                return false;
            }

            break;
        }
    }

    events.push_back(newEvent);
    return saveTimetable();
}

bool Timetable::removeEvent(int eventId)
{
    auto it = std::find_if(events.begin(), events.end(),
                           [eventId](const Event &event)
                           { return event.id == eventId; });

    if (it != events.end())
    {
        events.erase(it);
        return saveTimetable();
    }

    std::cout << "Event with ID " << eventId << " not found." << std::endl;
    return false;
}

void Timetable::viewTimetable()
{
    if (events.empty())
    {
        std::cout << "No events found." << std::endl;
        return;
    }

    // Sort events by day and then by start time
    std::sort(events.begin(), events.end(), [this](const Event &a, const Event &b)
              {
        // First sort by day of week (assuming standard format)
        std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        
        auto dayAIndex = std::find(days.begin(), days.end(), a.day);
        auto dayBIndex = std::find(days.begin(), days.end(), b.day);
        
        if (dayAIndex != days.end() && dayBIndex != days.end()) {
            if (dayAIndex != dayBIndex) {
                return dayAIndex < dayBIndex;
            }
        } else if (a.day != b.day) {
            return a.day < b.day;
        }
        
        // Then sort by start time
        return convertTimeToMinutes(a.startTime) < convertTimeToMinutes(b.startTime); });

    std::string currentDay = "";
    for (const auto &event : events)
    {
        if (event.day != currentDay)
        {
            currentDay = event.day;
            std::cout << "\n===================================================================\n";
            std::cout << "                              " << currentDay << std::endl;
            std::cout << "===================================================================\n";
            std::cout << std::left << std::setw(4) << "ID" << " | "
                      << std::setw(20) << "Title" << " | "
                      << std::setw(12) << "Time" << " | "
                      << "Location" << std::endl;
            std::cout << "-------------------------------------------------------------------\n";
        }

        std::cout << std::left << std::setw(4) << event.id << " | "
                  << std::setw(20) << event.title << " | "
                  << std::setw(12) << (event.startTime + "-" + event.endTime) << " | "
                  << event.location << std::endl;
    }

    std::cout << "===================================================================\n";
}

void Timetable::checkConflicts()
{
    if (events.size() < 2)
    {
        std::cout << "No conflicts found (not enough events to have conflicts)." << std::endl;
        return;
    }

    bool conflictsFound = false;

    for (size_t i = 0; i < events.size(); ++i)
    {
        for (size_t j = i + 1; j < events.size(); ++j)
        {
            if (isTimeConflict(events[i], events[j]))
            {
                if (!conflictsFound)
                {
                    std::cout << "\n===================================================================\n";
                    std::cout << "                        SCHEDULE CONFLICTS                          \n";
                    std::cout << "===================================================================\n";
                    conflictsFound = true;
                }

                std::cout << "Conflict found: " << std::endl;
                std::cout << "  - " << events[i].title << " on " << events[i].day
                          << " (" << events[i].startTime << "-" << events[i].endTime
                          << ") at " << events[i].location << std::endl;
                std::cout << "  - " << events[j].title << " on " << events[j].day
                          << " (" << events[j].startTime << "-" << events[j].endTime
                          << ") at " << events[j].location << std::endl;
                std::cout << "-------------------------------------------------------------------\n";
            }
        }
    }

    if (!conflictsFound)
    {
        std::cout << "No conflicts found in your schedule." << std::endl;
    }
}

std::vector<Event> Timetable::getEventsForDay(const std::string &day)
{
    std::vector<Event> dayEvents;

    for (const auto &event : events)
    {
        if (event.day == day)
        {
            dayEvents.push_back(event);
        }
    }

    // Sort by start time
    std::sort(dayEvents.begin(), dayEvents.end(), [this](const Event &a, const Event &b)
              { return convertTimeToMinutes(a.startTime) < convertTimeToMinutes(b.startTime); });

    return dayEvents;
}