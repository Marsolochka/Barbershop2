#include <iostream> //Библиотека ввода-вывода

#include <limits>

#include "user.h" //Заголовочный файл

#include "main_screen.h"  //Заголовочный файл

#include "client_service.h"  //Заголовочный файл

#include "administrator.h"

int main() {
  User user1; // Создание объекта класса User с именем user1
  user1.username = "admin"; // Присвоение имени пользователя
  user1.password = "123456"; // Присвоение пароля
  user1.isLoggedIn = false; // Установка статуса входа в "невошел"

  User user2; // Создание объекта класса User с именем user2
  user2.username = "worker"; // Присвоение имени пользователя
  user2.password = "654321"; // Присвоение пароля
  user2.isLoggedIn = false; // Установка статуса входа в "невошел"

  bool loginSuccess = false; // Установка начального значения для переменной успеха входа
  std::string inputUsername; // Объявление переменной для ввода имени пользователя
  do {
    system("cls"); // Очистка экрана
    std::cout << "You are currently at the login panel.\n"; // Вывод сообщения о входе
    std::string inputPassword; // Объявление переменной для ввода пароля
    std::cout << "Enter your username: "; // Запрос ввода имени пользователя
    std::cin >> inputUsername; // Получение ввода имени пользователя
    std::cout << "Enter your password: "; // Запрос ввода пароля
    std::cin >> inputPassword; // Получение ввода пароля

    // Попытка входа с использованием метода login объектов user1 и user2
    if (user1.login(inputUsername, inputPassword) || user2.login(inputUsername, inputPassword)) {
      loginSuccess = true; // Если вход успешен, устанавливаем статус успеха входа в "вошел"
    } else {
      std::cout << "Invalid input. Please try logging in again.\n"; // Если вход неуспешен, выводим сообщение об ошибке
      std::cin.clear(); // Очистка флагов ошибок ввода
      std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n'); // Очистка буфера ввода
    }
  } while (!loginSuccess); // Повторяем вход, пока успешно не войдем

  MainScreen mainScreen; // Создание объекта класса MainScreen
  mainScreen.startMainLoop(inputUsername); // Отображение главного меню с использованием имени вошедшего пользователя
  return 0; // Завершение функции main и возврат значения 0
}
