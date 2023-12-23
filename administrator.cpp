#include "administrator.h"

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
      case 8:
          {
              std::string startDate, endDate;
              std::cout << "Enter start date (YYYY-MM-DD): ";
              std::cin >> startDate;
              std::cout << "Enter end date (YYYY-MM-DD): ";
              std::cin >> endDate;

              // Добавьте вызов метода для записи клиентских записей в файл с учетом указанного периода времени
              // Например:
              clientService.writeClientAppointments(startDate, endDate);

              // Дополнительная логика для обработки финансовых данных и отчетности
              // Например, подсчет общей суммы услуг за указанный период времени и запись в файл

              std::cout << "Financial report for the period from " << startDate << " to " << endDate << " has been generated." << std::endl;
          }
          break;
      }
    } while (adminSubMenuChoice != 9);
  } else {
    std::cout << "Incorrect administrator password. Access denied.\n";
  }
}
