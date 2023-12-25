#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
    public:
    Client(std::string name, std::string email, std::string phoneNumber): name(name),email(email), phoneNumber(phoneNumber) {} // Определяем конструктор класса Client с параметрами name, email, phoneNumber
    std::string getName() const { // Определяем метод для получения имени
        return name; // Возвращаем имя
    }
    std::string getEmail() const {  // Определяем метод для получения электронной
        return email; // Возвращаем электронную почту
    }
    std::string getPhoneNumber() const { // Определяем метод для получения номера телефона
        return phoneNumber; // Возвращаем номер телефона
    }

    private:
    std::string name; // Поле для хранения имени клиента
    std::string email; // Поле для хранения электронной почты клиента
    std::string phoneNumber; // Поле для хранения номера телефона клиента
};

#endif // CLIENT_H
