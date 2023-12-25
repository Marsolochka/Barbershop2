#ifndef SERVICE_H
#define SERVICE_H

#include <string>

#include <vector>

class Service {

    public: Service(const std::string & name, double cost,
        const std::string & description); // Конструктор класса Service с параметрами name, cost, description
     Service() = default;
    std::string getName() const; // Метод для получения имени услуги
    double getCost() const; // Метод для получения стоимости услуги
    std::string getDescription() const; // Метод для получения описания услуги
    void setCost(double cost); // Метод для установки стоимости услуги
    void setDescription(const std::string & description); // Метод-установщик для описания
    std::string getDate() const { // Метод для получения даты
        return date; // Возвращаем дату
    }
    std::string getTime() const { // Метод для получения времени
        return time; // Возвращаем время
    }
    void viewServicesFromFile(); // Объявление метода для загрузки услуг из файла

    private:
    std::string name; // Поле для хранения имени услуги
    double cost; // Поле для хранения стоимости услуги
    std::string description; // Поле для хранения описания услуги
    std::string date; // Поле для хранения даты
    std::string time; // Поле для хранения времени
};

#endif // SERVICE_H
