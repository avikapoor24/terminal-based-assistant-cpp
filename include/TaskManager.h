#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct Task
{
    int id;
    std::string title;
    std::string description;
    std::string dueDate;
    int priority;
    bool completed;
};

class TaskManager
{
private:
    std::string username;
    std::vector<Task> tasks;
    std::string tasksFilePath;
    int nextTaskId;

    // Helper functions
    bool loadTasks();
    bool saveTasks();
    int getNextTaskId();

public:
    TaskManager(const std::string &username);

    // Task operations
    bool addTask(const std::string &title, const std::string &description,
                 const std::string &dueDate, int priority);
    bool removeTask(int taskId);
    bool markTaskComplete(int taskId);
    void viewTasks();
    std::vector<Task> getUpcomingTasks(int days);
};

#endif // TASK_MANAGER_H