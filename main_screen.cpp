#include "main_screen.h"

#include "client_service.h"

#include "administrator.h"

#include <iostream>

void MainScreen::startMainLoop(const std::string & inputUsername) {
    int choice; // Объявляем переменную для выбора пользователя
    do { // Начинаем цикл обработки выбора пользователя
        system("cls");
        std::cout << "Welcome, " << inputUsername << "! Here is the main menu:\n"; // Выводим приветственное сообщение и главное меню
        std::cout << "1. Schedule an appointment\n";  // Выводим пункт меню "Запланировать прием"
        std::cout << "2. Cancel an appointment\n"; // Выводим пункт меню "Отменить прием"
        std::cout << "3. View schedule\n"; // Выводим пункт меню "Просмотреть расписание"
        std::cout << "4. Client and service settings\n"; // Выводим пункт меню "Настройки клиентов и услуг"
        std::cout << "5. Advanced access\n"; // Выводим пункт меню "Расширенный доступ"
        std::cout << "6. Exit\n"; // Выводим пункт меню "Выход"
        std::cout << "Enter your choice: "; // Приглашаем пользователя ввести выбор
        std::cin >> choice; // Получаем выбор пользователя

        if (choice == 1) { // Если выбор - 1
            system("cls");
            ClientService clientService; // Создаем экземпляр класса ClientService
            clientService.writeClientAppointment(); // Вызываем метод для записи приема клиента

        } else if (choice == 2) { // Если выбор - 2
            system("cls");
            ClientService clientService; // Создаем экземпляр класса ClientService
            std::string date, time; // Объявляем переменные для даты и времени
            std::cout << "Enter the date for the appointment to cancel: "; // Приглашаем пользователя ввести дату для отмены приема
            std::cin >> date;  // Получаем введенную дату
            std::cout << "Enter the time for the appointment to cancel: "; // Приглашаем пользователя ввести время для отмены приема
            std::cin >> time; // Получаем введенное время
            clientService.deleteClientAppointment(date, time);  // Вызываем метод для отмены приема клиента

        } else if (choice == 3) { // Если выбор - 3
            system("cls");
            ClientService clientService; // Создаем экземпляр класса ClientService
            clientService.viewSchedule(); // Вызываем метод для просмотра расписания
            system("pause"); // Приостанавливаем выполнение программы до нажатия клавиши

        } else if (choice == 4) { // Если выбор - 4
            system("cls");
            ClientService clientService;  // Создаем экземпляр класса ClientService
            clientService.displayClientServiceMenu(); // Вызываем метод для отображения меню клиентских услуг

        } else if (choice == 5 && inputUsername == "admin") {  // Если выбор - 5 и имя пользователя "admin"
            system("cls");
            Administrator admin;
            admin.enterAdministratorMenu(); // Вызываем метод для входа в меню администратора
        } else { // Если выбор не соответствует ни одному из предыдущих вариантов
            std::cout << "Invalid choice. Please try again.\n"; // Выводим сообщение об ошибке выбора
        }

    } while (choice != 6);
}
