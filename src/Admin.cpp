#include "../include/Admin.h"
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <ctime>

Admin::Admin()
{
    loadAdminData();
}

std::string Admin::generateSHA256(const std::string &input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

std::string Admin::getCurrentTimestamp()
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return std::string(buffer);
}

bool Admin::saveAdminData()
{
    std::ofstream outFile(adminFilePath);
    if (!outFile.is_open())
    {
        return false;
    }

    outFile << username << std::endl;
    outFile << passwordHash << std::endl;
    outFile << lastLogin << std::endl;

    outFile.close();
    return true;
}

bool Admin::loadAdminData()
{
    std::ifstream inFile(adminFilePath);
    if (!inFile.is_open())
    {
        return false;
    }

    std::getline(inFile, username);
    std::getline(inFile, passwordHash);
    std::getline(inFile, lastLogin);

    inFile.close();
    return true;
}

bool Admin::adminExists()
{
    std::ifstream inFile(adminFilePath);
    return inFile.good();
}

bool Admin::createAdmin(const std::string &username, const std::string &password)
{
    this->username = username;
    this->passwordHash = generateSHA256(password);
    this->lastLogin = getCurrentTimestamp();

    return saveAdminData();
}

bool Admin::login(const std::string &username, const std::string &password)
{
    if (!loadAdminData())
    {
        return false;
    }

    if (this->username == username && this->passwordHash == generateSHA256(password))
    {
        this->lastLogin = getCurrentTimestamp();
        saveAdminData();
        return true;
    }

    return false;
}

bool Admin::logout()
{
    // You might want to add additional logout functionality here
    return true;
}

bool Admin::changeUsername(const std::string &newUsername)
{
    this->username = newUsername;
    return saveAdminData();
}

bool Admin::changePassword(const std::string &oldPassword, const std::string &newPassword)
{
    if (this->passwordHash == generateSHA256(oldPassword))
    {
        this->passwordHash = generateSHA256(newPassword);
        return saveAdminData();
    }

    return false;
}

void Admin::viewAccountInfo()
{
    std::cout << "Account Information:" << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Last Login: " << lastLogin << std::endl;
}