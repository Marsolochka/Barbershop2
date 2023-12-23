// main_screen.cpp

#include "main_screen.h"
#include "client_service.h"
#include "administrator.h"
#include <iostream>

void MainScreen::startMainLoop(const std::string & inputUsername) {
  int choice;

  do {
    system("cls");
    std::cout << "Welcome, " << inputUsername << "! Here is the main menu:\n";
    std::cout << "1. Schedule an appointment\n";
    std::cout << "2. Cancel an appointment\n";
    std::cout << "3. View schedule\n";
    std::cout << "4. Client and service settings\n";
    std::cout << "5. Advanced access\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
      system("cls");
      ClientService clientService;
      clientService.writeClientAppointment();

    } else if (choice == 2) {
      system("cls");
      ClientService clientService;
      std::string date, time;
      std::cout << "Enter the date and time of the appointment to cancel:" << std::endl;
      std::cout << "Date (e.g. 2023-09-15): ";
      std::cin >> date;
      std::cout << "Time (e.g. 14:30): ";
      std::cin >> time;
      clientService.cancelClientAppointment(date, time);

    } else if (choice == 3) {
      system("cls");
      ClientService clientService;
      clientService.viewSchedule();
      system("pause"); // Приостанавливаем выполнение программы до нажатия клавиши

    } else if (choice == 4) {
      system("cls");
      ClientService clientService;
      clientService.displayClientServiceMenu();

    } else if (choice == 5 && inputUsername == "admin") {
      system("cls");
      Administrator admin;
      admin.enterAdministratorMenu();
    } else {
      std::cout << "Invalid choice. Please try again.\n";
    }

  } while (choice != 6);
}



