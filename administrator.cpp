#include "administrator.h"

#include "client_service.h"

#include <regex>

#include <stdexcept>

void Administrator::enterAdministratorMenu() {
    std::string adminPassword;
    std::cout << "Enter administrator password: ";
    std::cin >> adminPassword;

    if (adminPassword == "admin123") {
        int adminSubMenuChoice;
        do {
            system("cls");
            std::cout << "1. Add item\n"; // Пункты меню администратора
            std::cout << "2. Remove item\n";
            std::cout << "3. Edit item\n";
            std::cout << "4. View all items\n";
            std::cout << "5. Add employee\n";
            std::cout << "6. Remove employee\n";
            std::cout << "7. View all employees\n";
            std::cout << "8. Edit employee\n";
            std::cout << "9. Finances\n";
            std::cout << "10. Menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> adminSubMenuChoice;


            switch (adminSubMenuChoice) {
            case 1: // Add item
                {
                    std::string name, description;
                    std::cout << "Enter the name of the item: ";
                    std::cin >> name;
                    std::cout << "Enter the description of the item: ";
                    std::cin >> description;
                    addItem(name, description);
                    std::cout << "Item added successfully.\n";
                    system("pause");
                    break;
                }
                case 2: // Remove item
                {
                    int itemId;
                    std::cout << "Enter the ID of the item to remove: ";
                    std::cin >> itemId;
                    try {
                        removeItem(itemId);
                        std::cout << "Item removed successfully.\n";
                    } catch (const std::runtime_error& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    system("pause");
                    break;
                }
                case 3: // Edit item
                {
                    int itemId;
                    std::string newName, newDescription;
                    std::cout << "Enter the ID of the item to edit: ";
                    std::cin >> itemId;
                    std::cout << "Enter the new name of the item: ";
                    std::cin >> newName;
                    std::cout << "Enter the new description of the item: ";
                    std::cin >> newDescription;
                    try {
                        editItemInfo(itemId, newName, newDescription);
                        std::cout << "Item edited successfully.\n";
                    } catch (const std::runtime_error& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    system("pause");
                    break;
                }
                case 4: // View all items
                {
                    for (size_t i = 0; i < items.size(); ++i) {
                        std::pair<std::string, std::string> item = items[i];
                        std::cout << "Item ID: " << i << ", Name: " << item.first << ", Description: " << item.second << "\n";
                        system("pause");
                    }
                    break;
                }
            case 5: // Пункт меню для добавления сотрудника
            {
                std::string name, JobTitle;
                std::cout << "Enter employee name: ";
                std::cin >> name;
                std::cout << "Enter employee job title: ";
                std::cin >> JobTitle;
                addEmployee(name, JobTitle);
                system("pause");
                break;
            }
            case 6: // Menu item for removing an employee
            {
                int employeeId;
                std::cout << "Enter the ID of the employee to remove: ";
                std::cin >> employeeId;
                try {
                    removeEmployee(employeeId);
                    std::cout << "Employee removed successfully.\n";
                } catch (const std::runtime_error & e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }

            case 7: // Menu item for viewing all employees
            {
                viewAllEmployees();
                system("pause");
                break;
            }
            case 8: {
                int employeeId;
                std::string newName, newJobTitle;

                // Чтение данных о сотруднике, которого необходимо изменить
                std::cout << "Enter employee ID to edit: ";
                std::cin >> employeeId;

                std::cout << "Enter new name: ";
                std::cin >> newName;

                std::cout << "Enter new job title: ";
                std::cin >> newJobTitle;

                try {
                    editEmployeeInfo(employeeId, newName, newJobTitle);
                    std::cout << "Employee information updated successfully." << std::endl;
                } catch (const std::runtime_error & e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 9: // Пункт меню для финансов
            {
                std::string startDateTime, endDateTime;

                std::regex dateTimePattern("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}");

                do {
                    std::cout << "Enter the start date and time for the financial report (e.g. 2023-01-01 00:00): ";
                    std::cin.ignore(); // очистить символ новой строки из входного буфера
                    std::getline(std::cin, startDateTime);
                } while (!std::regex_match(startDateTime, dateTimePattern));

                do {
                    std::cout << "Enter the end date and time for the financial report (e.g. 2023-12-31 23:59): ";
                    std::getline(std::cin, endDateTime);
                } while (!std::regex_match(endDateTime, dateTimePattern));

                ClientService clientService;
                // Вызываем метод для генерации финансового отчёта
                clientService.generateReport(startDateTime, endDateTime);
                system("pause"); // Приостанавливаем выполнение программы до нажатия клавиши
                break;
            }
            }
        } while (adminSubMenuChoice != 10);
    } else {
        std::cout << "Incorrect administrator password. Access denied.\n";
    }
}

void Administrator::addEmployee(const std::string & name,
    const std::string & jobTitle) {
    employees.push_back(name + " - " + jobTitle);  // Добавляем нового сотрудника в список
    saveEmployeesToFile(); // Сохранить данные при добавлении нового сотрудника
}

void Administrator::editEmployeeInfo(int employeeId,
    const std::string & newName,
        const std::string & newJobTitle) {
    if (employeeId >= static_cast < int > (employees.size())) {
        throw std::runtime_error("Employee ID out of range");  // Бросаем исключение, если ID сотрудника выходит за пределы списка
    }
    employees[employeeId] = newName + " - " + newJobTitle; // Простой пример изменения информации о сотруднике
    saveEmployeesToFile(); // Сохранить данные при изменении информации о сотруднике
}

void Administrator::removeEmployee(int employeeId) {
    if (employeeId >= static_cast < int > (employees.size())) {
        throw std::runtime_error("Employee ID out of range"); // Бросаем исключение, если ID сотрудника выходит за пределы списка
    }
    employees.erase(employees.begin() + employeeId); // Удаляем информацию о сотруднике
    saveEmployeesToFile(); // Сохраняем данные при удалении сотрудника
}

void Administrator::loadEmployeesFromFile() {
    std::ifstream file("employees.txt"); // Открываем файл для чтения списка сотрудников
    if (file.is_open()) {
        std::string employeeInfo;
        employees.clear(); // Очистить существующие данные перед загрузкой из файла
        while (std::getline(file, employeeInfo)) {
            employees.push_back(employeeInfo); // Добавляем информацию о сотруднике
        }
        file.close();
    } else {
        std::cout << "Unable to open file for loading employees." << std::endl;  // Выводим сообщение об ошибке открытия файла
    }
}

void Administrator::saveEmployeesToFile() {
    std::ofstream file("employees.txt"); // Открываем файл для записи списка сотрудников
    if (file.is_open()) {
        for (const auto & employee: employees) {
            file << employee << std::endl; // Записываем информацию о сотруднике в файл
        }
        file.close();
    } else {
        std::cout << "Unable to open file for saving employees." << std::endl; // Выводим сообщение об ошибке открытия файла
    }
}

void Administrator::viewAllEmployees() {
    loadEmployeesFromFile(); // Загружаем данные перед выводом списка сотрудников
    std::cout << "Employee List:\n";
    for (int i = 0; i < static_cast < int > (employees.size()); ++i) {
        std::cout << "ID: " << i << ", Employee Info: " << employees[i] << std::endl;
    }
}

void Administrator::saveItemsToFile(const std::string& filename) {
       std::ofstream file(filename);
       if (file.is_open()) {
           for (const auto& item : items) {
               file << item.first << "," << item.second << "\n";
           }
           file.close();
       } else {
           throw std::runtime_error("Unable to open file for writing: " + filename);
       }
   }
void Administrator::loadItemsFromFile(const std::string& filename) {
       std::ifstream file(filename);
       if (file.is_open()) {
           items.clear(); // Очищаем текущие элементы
           std::string line;
           while (std::getline(file, line)) {
               size_t pos = line.find(",");
               if (pos != std::string::npos) {
                   std::string name = line.substr(0, pos);
                   std::string description = line.substr(pos + 1);
                   items.emplace_back(name, description);
               }
           }
           file.close();
       } else {
           throw std::runtime_error("Unable to open file for reading: " + filename);
       }
   }
