#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;
    bool isLoggedIn;
    bool login(const std::string& inputUsername, const std::string& inputPassword);
    void logout();
};

#endif // USER_H

