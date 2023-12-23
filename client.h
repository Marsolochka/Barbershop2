// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client(std::string name, std::string email, std::string phoneNumber)
        : name(name), email(email), phoneNumber(phoneNumber) {}
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phoneNumber; }

private:
    std::string name;
    std::string email;
    std::string phoneNumber;
};

#endif // CLIENT_H
