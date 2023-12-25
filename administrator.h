#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <iostream>

#include <string>

#include <vector>

#include "service.h"

class Administrator {
    public: void enterAdministratorMenu(); // Объявление метода для входа в меню администратора
    Administrator(const std::string & name,
        const std::string & jobTitle); // Объявление конструктора класса Administrator
    void setName(const std::string & newName); // Объявление метода для установки имени
    void setJobTitle(const std::string & newJobTitle); // Объявление метода для установки должности
    std::string getName(); // Объявление метода для получения имени
    std::string getJobTitle(); // Объявление метода для получения должности
    void viewAllEmployees(); // Объявление метода для просмотра всех сотрудников
    void addEmployee(const std::string & name,
        const std::string & jobTitle); // Метод для добавления сотрудника
    void removeEmployee(int employeeId); // Метод для удаления сотрудника
    void editEmployeeInfo(int employeeId,
        const std::string & newName,
            const std::string & newJobTitle); // Метод для редактирования информации о сотруднике
    void loadEmployeesFromFile(); // Метод для загрузки данных о сотрудниках из файла
    std::vector < std::string > employeeNames; // Вектор для хранения имен сотрудников
    void saveEmployeesToFile(); // Метод для сохранения данных о сотрудниках в файл
    std::string getEmployeeInfo(int employeeId); // Метод для получения информации о сотруднике

    private:
    std::string name;
    std::string jobTitle;
    std::vector < std::string > employees; // Вектор для хранения информации о сотрудниках
};

#endif // ADMINISTRATOR_H
