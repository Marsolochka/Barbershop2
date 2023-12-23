#include "administrator.h"
#include "client_service.h"
#include <regex>

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
      std::cout << "8. Finances\n";
      std::cout << "9. Menu\n";
      std::cout << "Enter your choice: ";
      std::cin >> adminSubMenuChoice;

      switch (adminSubMenuChoice) {
      case 8: // Пункт меню для финансов
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
    } while (adminSubMenuChoice != 9);
  } else {
    std::cout << "Incorrect administrator password. Access denied.\n";
  }
}
