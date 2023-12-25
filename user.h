#ifndef USER_H
#define USER_H

#include <string>

class User {

    public:
    std::string username; // Публичное поле для имени пользователя
    std::string password; // Публичное поле для пароля пользователя
    bool isLoggedIn; // Публичное поле для отслеживания статуса входа в систему
    bool login(const std::string & inputUsername,
        const std::string & inputPassword); // Метод для входа в систему
    void logout(); // Метод для выхода из системы
};

#endif // USER_H
