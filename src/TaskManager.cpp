#include "../include/TaskManager.h"
#include <algorithm>
#include <iomanip>

TaskManager::TaskManager(const std::string &username) : username(username)
{
    tasksFilePath = "data/tasks_" + username + ".txt";
    loadTasks();
    nextTaskId = getNextTaskId();
}

bool TaskManager::loadTasks()
{
    std::ifstream inFile(tasksFilePath);
    if (!inFile.is_open())
    {
        return false;
    }

    tasks.clear();

    std::string line;
    while (std::getline(inFile, line))
    {
        Task task;
        size_t pos = 0;

        // Parse task ID
        pos = line.find(',');
        task.id = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Parse title
        pos = line.find(',');
        task.title = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse description
        pos = line.find(',');
        task.description = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse due date
        pos = line.find(',');
        task.dueDate = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Parse priority
        pos = line.find(',');
        task.priority = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Parse completed status
        task.completed = (line == "1");

        tasks.push_back(task);
    }

    inFile.close();
    return true;
}

bool TaskManager::saveTasks()
{
    std::ofstream outFile(tasksFilePath);
    if (!outFile.is_open())
    {
        return false;
    }

    for (const auto &task : tasks)
    {
        outFile << task.id << ","
                << task.title << ","
                << task.description << ","
                << task.dueDate << ","
                << task.priority << ","
                << (task.completed ? "1" : "0") << std::endl;
    }

    outFile.close();
    return true;
}

int TaskManager::getNextTaskId()
{
    if (tasks.empty())
    {
        return 1;
    }

    int maxId = 0;
    for (const auto &task : tasks)
    {
        if (task.id > maxId)
        {
            maxId = task.id;
        }
    }

    return maxId + 1;
}

bool TaskManager::addTask(const std::string &title, const std::string &description,
                          const std::string &dueDate, int priority)
{
    Task newTask;
    newTask.id = nextTaskId++;
    newTask.title = title;
    newTask.description = description;
    newTask.dueDate = dueDate;
    newTask.priority = priority;
    newTask.completed = false;

    tasks.push_back(newTask);
    return saveTasks();
}

bool TaskManager::removeTask(int taskId)
{
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [taskId](const Task &task)
                           { return task.id == taskId; });

    if (it != tasks.end())
    {
        tasks.erase(it);
        return saveTasks();
    }

    std::cout << "Task with ID " << taskId << " not found." << std::endl;
    return false;
}

bool TaskManager::markTaskComplete(int taskId)
{
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [taskId](const Task &task)
                           { return task.id == taskId; });

    if (it != tasks.end())
    {
        it->completed = true;
        return saveTasks();
    }

    std::cout << "Task with ID " << taskId << " not found." << std::endl;
    return false;
}

void TaskManager::viewTasks()
{
    if (tasks.empty())
    {
        std::cout << "No tasks found." << std::endl;
        return;
    }

    std::cout << "\n===================================================================\n";
    std::cout << std::left << std::setw(4) << "ID" << " | "
              << std::setw(20) << "Title" << " | "
              << std::setw(10) << "Due Date" << " | "
              << std::setw(8) << "Priority" << " | "
              << "Status" << std::endl;
    std::cout << "===================================================================\n";

    for (const auto &task : tasks)
    {
        std::cout << std::left << std::setw(4) << task.id << " | "
                  << std::setw(20) << task.title << " | "
                  << std::setw(10) << task.dueDate << " | "
                  << std::setw(8) << task.priority << " | "
                  << (task.completed ? "Completed" : "Pending") << std::endl;
    }

    std::cout << "===================================================================\n";
}

std::vector<Task> TaskManager::getUpcomingTasks(int days)
{
    // This would require date manipulation, which is a bit complex
    // For simplicity, we'll just return all pending tasks
    std::vector<Task> upcomingTasks;

    for (const auto &task : tasks)
    {
        if (!task.completed)
        {
            upcomingTasks.push_back(task);
        }
    }

    return upcomingTasks;
}