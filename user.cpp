#include "user.h"

#include <iostream>

bool User::login(const std::string & inputUsername,
    const std::string & inputPassword) {
    if (inputUsername == username && inputPassword == password) { // Проверяем соответствие введенного имени пользователя и пароля
        isLoggedIn = true; // Устанавливаем флаг аутентификации в true
        std::cout << "Login successful. Welcome, " << username << "!\n"; // Выводим сообщение об успешной аутентификации
        return true; // Возвращаем true, если аутентификация успешна
    } else {  // Если введенные данные не соответствуют сохраненным
        return false; // Возвращаем false
    }
}

void User::logout() {
    isLoggedIn = false; // Устанавливаем флаг аутентификации в false
    std::cout << "Logout successful. Goodbye, " << username << "!\n"; // Выводим сообщение об успешном выходе из системы
}
