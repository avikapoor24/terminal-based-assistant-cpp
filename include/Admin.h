#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

class Admin
{
private:
    std::string username;
    std::string passwordHash;
    std::string lastLogin;
    const std::string adminFilePath = "data/admin.txt";

    // Helper functions
    std::string generateSHA256(const std::string &input);
    std::string getCurrentTimestamp();
    bool saveAdminData();
    bool loadAdminData();

public:
    Admin();

    // Core authentication functions
    bool adminExists();
    bool createAdmin(const std::string &username, const std::string &password);
    bool login(const std::string &username, const std::string &password);
    bool logout();

    // Account management
    bool changeUsername(const std::string &newUsername);
    bool changePassword(const std::string &oldPassword, const std::string &newPassword);
    void viewAccountInfo();

    // Getters
    std::string getUsername() const { return username; }
};

#endif // ADMIN_H