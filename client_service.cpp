#include "client_service.h" // Включение заголовочного файла для класса ClientService

#include "service.h" // Включение заголовочного файла для класса Service

#include <iostream> // Включение стандартной библиотеки для ввода/вывода

#include <fstream> // Включение стандартной библиотеки для работы с файлами

#include <string> // Включение стандартной библиотеки для работы со строками

#include <sstream>  // Включение стандартной библиотеки для работы со вводом/выводом в строковом формате


Service::Service(const std::string & name, double cost,
    const std::string & description): name(name), cost(cost), description(description) {}  // Определение конструктора класса Service

std::string Service::getName() const { // Определение метода getName класса Service
    return name;  // Возврат имени услуги
}

double Service::getCost() const {  // Определение метода getCost класса Service
    return cost;  // Возврат стоимости услуги
}

std::string Service::getDescription() const { // Определение метода getDescription класса Service
    return description; // Возврат описания услуги
}

void Service::setCost(double newCost) { // Определение метода setCost класса Service
    cost = newCost;  // Установка новой стоимости для услуги
}
void Service::setDescription(const std::string & newDescription) { // Определение метода setDescription класса Service
    description = newDescription;  // Установка нового описания для услуги
}

void ClientService::removeClient(const std::string & clientName) { //Определение метода для удаления клиента
    for (std::vector < Client > ::iterator it = clients.begin(); it != clients.end(); ++it) { // Цикл по всем клиентам в векторе
        if (it -> getName() == clientName) { // Проверка имени клиента
            clients.erase(it); // Удалить клиента из вектора
            saveClientsToFile(); // Перезаписать данные в файл
            std::cout << "Client removed successfully." << std::endl; // Вывод сообщения об успешном удалении клиента
            return;
        }
    }
    std::cout << "Client not found." << std::endl; // Вывод сообщения, если клиент не найден
}

void Service::viewServicesFromFile() {  // Определение метода для просмотра услуг
    std::ifstream file("services.txt");  // Открытие файла services.txt для чтения
    if (file.is_open()) { // Проверка успешного открытия файла
        std::string line; // Объявление переменной для хранения строки из файла
        while (std::getline(file, line)) { // Цикл по строкам файла
            std::cout << line << std::endl; // Вывод каждой строки из файла
        }
        file.close(); // Закрыть файл
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl; // Вывод сообщения об ошибке, если файл не удалось открыть
    }
}

void ClientService::loadClientsFromFile() { // Метод для загрузки клиентов из файла
    std::ifstream file("clients.txt"); // Открытие файла clients.txt для чтения
    if (file.is_open()) { // Проверка успешного открытия файла
        std::string name, email, phoneNumber;  // Объявление переменных для хранения данных о клиенте
        while (file >> name >> email >> phoneNumber) { // Чтение данных о клиенте из файла
            clients.push_back(Client(name, email, phoneNumber)); // Добавить клиента в вектор
        }
        file.close(); // Закрыть файл
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl; // Вывод сообщения об ошибке, если файл не удалось открыть
    }
    if (file.bad()) { // Проверка наличия ошибок при чтении файла
        std::cerr << "Error: Failed to read data from file" << std::endl; // Вывод сообщения об ошибке при чтении данных из файла
    }
}

void ClientService::addClient(const Client & client) { // Метод для добавления клиента
    clients.push_back(client); // Добавить клиента в список
    saveClientsToFile(); // Сохранить клиентов в файл
}

void ClientService::saveClientsToFile() { // Метод записи данный о клиентах в файл
    std::ofstream file("clients.txt");// Открыть файл для записи
    if (file.is_open()) { // Проверка успешного открытия файла
        for (std::vector < Client > ::iterator it = clients.begin(); it != clients.end(); ++it) { // Цикл по клиентам в векторе
            const Client & client = * it; // Получение ссылки на текущего клиента
            file << client.getName() << " " << client.getEmail() << " " << client.getPhoneNumber() << std::endl; // Записать данные о каждом клиенте в файл
        }
        file.close(); // Закрыть файл
    } else {
        std::cerr << "Error: Unable to open file for writing" << std::endl; // Вывод сообщения об ошибке, если файл не удалось открыть для записи
    }
}

void ClientService::generateReport(const std::string & startDateTime,
    const std::string & endDateTime) {
    std::ifstream appointmentsFile("client_appointments.txt"); // Открываем файл с записями клиентов
    if (!appointmentsFile.is_open()) { // Проверка успешного открытия файла с записями клиентов
        std::cerr << "Error: Unable to open client appointments file" << std::endl; // Вывод сообщения об ошибке, если файл не удалось открыть
        return;// Возврат из метода
    }

    std::ofstream reportFile("report.txt"); // Открываем файл для записи отчёта
    if (!reportFile.is_open()) { // Проверка успешного открытия файла для записи отчёта
        std::cerr << "Error: Unable to open report file" << std::endl;  // Вывод сообщения об ошибке, если файл не удалось открыть
        return; // Возврат из метода
    }

    std::string appointment;  //Объявление переменной для хранения информации о записи клиента
    while (std::getline(appointmentsFile, appointment)) {  // Цикл по записям о клиентах в файле

        // Разбиваем запись о клиенте на части
        std::string client, service, date, time; // Объявление переменных для хранения разделенных частей записи о клиенте
        size_t clientPos = appointment.find("Client: ") + 8; // Поиск позиции начала имени клиента
        size_t servicePos = appointment.find("Service: ") + 9; // Поиск позиции начала названия услуги
        size_t datePos = appointment.find("Date: ") + 6;// Поиск позиции начала даты
        size_t timePos = appointment.find("Time: ") + 6; // Поиск позиции начала времени
        client = appointment.substr(clientPos, servicePos - clientPos - 9); // Получение имени клиента
        service = appointment.substr(servicePos, datePos - servicePos - 10);  // Получение названия услуги
        date = appointment.substr(datePos, timePos - datePos - 7); // Получение даты
        time = appointment.substr(timePos); // Получение времени

        // Проверяем, попадает ли запись в указанный период
        if (date + " " + time >= startDateTime && date + " " + time <= endDateTime) { // Проверка попадания записи в указанный период
            reportFile << "Client: " << client << " | Service: " << service << " | Date: " << date << " | Time: " << time << std::endl; // Запись информации в файл отчёта
        }
    }

    appointmentsFile.close(); // Закрытие файла с записями клиентов
    reportFile.close();  // Закрытие файла отчёта
    std::cout << "Report has been successfully generated for the period from " << startDateTime << " to " << endDateTime << std::endl; // Вывод сообщения об успешном создании отчёта
}

void ClientService::writeClientAppointment() { // Метод для записи клиента на услугу

    std::ifstream clientsFile("clients.txt"); // Открываем файл с клиентами
    if (!clientsFile.is_open()) { // Проверяем, успешно ли открыт файл с клиентами
        std::cerr << "Error: Unable to open clients file" << std::endl; // Выводим сообщение об ошибке, если файл с клиентами не удалось открыть
        return; // Возвращаемся из метода
    }

    // Выводим список клиентов с их индексами
    std::vector < std::string > clients; // Создаем вектор для хранения информации о клиентах
    std::string client; // Объявляем переменную для хранения информации о каждом клиенте
    int clientIndex = 0; // Инициализируем индекс клиента
    while (std::getline(clientsFile, client)) { // Читаем информацию о клиентах из файла
        clients.push_back(client);  // Добавляем информацию о клиенте в вектор
        std::cout << clientIndex << ". " << client << std::endl; // Выводим индекс и информацию о клиенте
        clientIndex++; // Увеличиваем индекс для следующего клиента
    }
    clientsFile.close();  // Закрываем файл с клиентами

    // Предоставляем возможность выбрать клиента по индексу
    int chosenClientIndex;  // Объявляем переменную для выбранного индекса клиента
    std::cout << "Choose the client by entering the index: ";  // Предлагаем ввести индекс выбранного клиента
    std::cin >> chosenClientIndex;  // Считываем выбранный индекс клиента
    if (chosenClientIndex < 0 || static_cast<size_t>(chosenClientIndex) >= clients.size()) {
        std::cout << "Invalid client index" << std::endl;
        return;
    }

    std::string chosenClient = clients[chosenClientIndex]; // Получаем информацию о выбранном клиенте


    std::ifstream servicesFile("services.txt"); // Открываем файл "services.txt" для чтения информации о услугах
    if (!servicesFile.is_open()) { // Проверяем, успешно ли открыт файл с услугами
        std::cerr << "Error: Unable to open services file" << std::endl; // Выводим сообщение об ошибке, если файл с услугами не удалось открыть
        return; // Возвращаемся из метода
    }

    // Выводим список услуг с их индексами
    std::vector < std::string > services;  // Создаем вектор для хранения информации о услугах
    std::string service;  // Объявляем переменную для хранения информации о каждой услуге
    int serviceIndex = 0; // Инициализируем индекс услуги
    while (std::getline(servicesFile, service)) { // Читаем информацию об услугах из файла
        services.push_back(service); // Добавляем информацию об услуге в вектор
        std::cout << serviceIndex << ". " << service << std::endl;  // Выводим индекс и информацию об услуге
        serviceIndex++;  // Увеличиваем индекс для следующей услуги
    }
    servicesFile.close(); // Закрываем файл с услугами

    // Предоставляем возможность выбрать услугу по индексу
    int chosenServiceIndex; // Объявляем переменную для выбранного индекса услуги
    std::cout << "Choose the service by entering the index: "; // Предлагаем ввести индекс выбранной услуги
    std::cin >> chosenServiceIndex; // Считываем выбранный индекс услуги
    if (chosenServiceIndex < 0 || static_cast<size_t>(chosenServiceIndex) >= services.size()) {
        std::cout << "Invalid service index" << std::endl;
        return;
    }

    std::string chosenService = services[chosenServiceIndex]; // Получаем информацию о выбранной услуге

    // Ввод даты и времени
    std::string date, time; // Объявляем переменные для даты и времени записи
    std::cout << "Enter the date for the appointment (e.g. 2023-09-15): "; // Предлагаем ввести дату записи
    std::cin >> date; // Считываем введенную дату
    std::cout << "Enter the time for the appointment (e.g. 14:30): ";  // Предлагаем ввести время записи
    std::cin >> time;  // Считываем введенное время

    // Запись информации о записи клиента
    std::ofstream outputFile("client_appointments.txt", std::ios::app); // Открываем файл для добавления информации
    if (outputFile.is_open()) {  // Проверяем успешное открытие файла для записи
        outputFile << "Client: " << chosenClient << " | Service: " << chosenService << " | Date: " << date << " | Time: " << time << std::endl; // Записываем информацию о клиенте, выбранной услуге и времени записи
        outputFile.close(); // Закрываем файл
        std::cout << "Client " << chosenClient << " has been successfully added for the service " << chosenService << " at " << time << " on " << date << std::endl; // Выводим сообщение об успешном добавлении записи клиента
    } else {
        std::cerr << "Error: Unable to open file for writing" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть для записи

    }
}

void ClientService::deleteClientAppointment(const std::string & date,
    const std::string & time) {
    std::ifstream inputFile("client_appointments.txt"); // Открываем файл для чтения записей о клиентских записях
    if (!inputFile.is_open()) { // Проверяем, успешно ли открыт файл
        std::cerr << "Error: Unable to open client appointments file" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть
        return;// Возвращаемся из метода
    }

    std::vector < std::string > lines;  // Создаем вектор для хранения строк из файла
    std::string line; // Объявляем переменную для хранения строки
    while (std::getline(inputFile, line)) {  // Читаем строки из файла
        std::string appointment = "Date: " + date + " | Time: " + time; // Формируем информацию о записи для удаления
        if (line.find(appointment) == std::string::npos) { // Проверяем, содержит ли строка информацию о записи для удаления
            lines.push_back(line);  // Добавляем строку в вектор, если она не соответствует записи для удаления
        }
    }
    inputFile.close(); // Закрываем файл

    std::ofstream outputFile("client_appointments.txt"); // Открываем файл для записи
    if (!outputFile.is_open()) {  // Проверяем, успешно ли открыт файл для записи
        std::cerr << "Error: Unable to open client appointments file for writing" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть для записи
        return;  // Возвращаемся из метода
    }

    for (const auto & l: lines) {  // Записываем строки из вектора в файл
        outputFile << l << std::endl;
    }
    outputFile.close();

    std::cout << "Client appointments for the date " << date << " and time " << time << " have been successfully deleted" << std::endl; // Выводим сообщение об успешном удалении записи
}

void ClientService::saveServicesToFile() { // Метод для сохранения услуг в файл
    std::ifstream readFile("services.txt"); // Открываем файл для чтения информации о услугах
    std::vector < std::string > existingServices;  // Создаем вектор для хранения существующих услуг

    if (readFile.is_open()) { // Проверяем, успешно ли открыт файл
        std::string line;
        while (std::getline(readFile, line)) { // Читаем строки из файла и добавляем их в вектор
            existingServices.push_back(line);  // Добавляем строку (информацию об услуге) в вектор существующих услуг
        }
        readFile.close();  // Закрываем файл
    }

    std::ofstream file("services.txt", std::ios::app); // Открываем файл для добавления информации в конец
    if (file.is_open()) {  // Проверяем, успешно ли открыт файл для записи
        for (size_t i = 0; i < services.size(); ++i) { // Перебираем все услуги
            std::stringstream ss; // Создаем поток для конвертации стоимости услуги в строку
            ss << services[i].getCost();  // Получаем стоимость услуги в виде строки
            std::string costStr = ss.str();  // Получаем строковое представление стоимости услуги из потока
            std::string serviceInfo = services[i].getName() + " | Cost: " + costStr + " | " + services[i].getDescription(); // Формируем информацию об услуге
            bool alreadyExists = false; // Инициализируем флаг наличия услуги в файле
            for (size_t j = 0; j < existingServices.size(); ++j) { // Перебираем все существующие услуги в файле
                if (existingServices[j] == serviceInfo) {  // Проверяем, не существует ли уже данная услуга в файле
                    alreadyExists = true;   // Устанавливаем флаг наличия услуги в файле в случае совпадения
                    break; // Прерываем цикл, так как услуга уже существует
                }
            }
            if (!alreadyExists) { // Если услуги нет в файле, добавляем её
                file << serviceInfo << std::endl; // Записываем информацию об услуге в файл
            }
        }
        file.close(); // Закрываем файл
    } else {
        std::cerr << "Error: Unable to open file for writing" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть для записи
    }
}

void ClientService::viewClientsFromFile() {
    std::ifstream file("clients.txt"); // Открываем файл для чтения информации о клиентах
    if (file.is_open()) { // Проверяем, успешно ли открыт файл
        std::string line;
        while (std::getline(file, line)) {   // Читаем строки из файла и выводим их на экран
            std::cout << line << std::endl; // Выводим каждую строку из файла
        }
        file.close(); // Закрываем файл
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть
    }
}
void ClientService::addService(const Service & service) {
    // Проверяем, что такой услуги еще нет в списке
    bool serviceExists = false; // Инициализируем флаг наличия услуги в списке
    for (size_t i = 0; i < services.size(); ++i) { // Проверяем, не существует ли уже данная услуга в списке
        if (services[i].getName() == service.getName()) { // Проверяем, существует ли уже данная услуга в списке
            serviceExists = true;  // Устанавливаем флаг наличия услуги в списке в случае совпадения
            break; // Прерываем цикл, так как услуга уже существует
        }
    }

    if (!serviceExists) { // Если услуги нет в списке, добавляем её
        services.push_back(service); // Добавляем услугу в список

        // Добавляем информацию о новой услуге в файл
        std::ofstream outputFile("services.txt", std::ios::app); // Открываем файл для добавления информации
        if (outputFile.is_open()) { // Проверяем, успешно ли открыт файл для записи
            outputFile << service.getName() << " | Cost: " << service.getCost() << " | " << service.getDescription() << std::endl; // Записываем информацию о новой услуге в файл
            outputFile.close(); // Закрываем фай
        } else {
            std::cerr << "Error: Unable to open file for writing" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть для записи
        }
        saveServicesToFile(); // Сохраняем все услуги в файл
    } else {
        std::cout << "Service already exists." << std::endl; // Выводим сообщение о том, что услуга уже существует
    }
}

void ClientService::loadServicesFromFile() {
    std::ifstream file("services.txt"); // Открываем файл для чтения списка услуг
    if (file.is_open()) {  // Проверяем, успешно ли открыт файл
        std::string name;
        double price;
        std::string description;
        while (file >> name >> price) { // Читаем информацию о каждой услуге из файла
            file.ignore();// Пропускаем символ новой строки после цены
            std::getline(file, description);  // Получаем описание услуги
            services.push_back(Service(name, price, description)); // Добавляем услугу в список
        }
        file.close(); // Закрываем файл
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть для чтения
    }
    if (file.bad()) {  // Проверяем, произошла ли ошибка при чтении данных из файла
        std::cerr << "Error: Failed to read data from file" << std::endl; // Выводим сообщение об ошибке
    }
}

void ClientService::removeService(const std::string & serviceName) {
    for (size_t i = 0; i < services.size(); ++i) {  // Перебираем все услуги в списке
        if (services[i].getName() == serviceName) { // Проверяем, существует ли услуга с заданным именем
            services.erase(services.begin() + i); // Удаляем услугу из списка
            saveServicesToFile(); // Сохраняем изменения в файл
            return; // Завершаем функцию после удаления услуги
        }
    }
    std::cout << "Service not found." << std::endl; // Выводим сообщение, если услуга не найдена
}

void ClientService::editClientData() {
    system("cls"); // Очистить экран
    std::cout << "Enter the name of the client you want to edit: "; // Подсказка для ввода имени клиента
    std::string clientName;
    std::cin >> clientName; // Получаем имя клиента от пользователя

    bool found = false; // Инициализируем флаг нахождения клиента
    for (size_t i = 0; i < clients.size(); ++i) {  // Перебираем всех клиентов
        if (clients[i].getName() == clientName) {  // Проверяем, существует ли клиент с данным именем
            found = true;   // Устанавливаем флаг нахождения клиента
            std::string consent;
            std::cout << "Do you consent to update the client data? (yes/no): ";
            std::cin >> consent;

            if (consent == "yes") {
                std::string newName, newEmail, newPhoneNumber;
                std::cout << "Enter new name for the client: "; // Подсказка для ввода нового имени
                std::cin >> newName; // Получаем новое имя для клиента
                std::cout << "Enter new email for the client: "; // Подсказка для ввода новой почты
                std::cin >> newEmail;  // Получаем новую почту для клиента
                std::cout << "Enter new phone number for the client: "; // Подсказка для ввода нового номера телефона
                std::cin >> newPhoneNumber; // Получаем новый номер телефона для клиента

                clients[i] = Client(newName, newEmail, newPhoneNumber);  // Изменяем данные клиента
                saveClientsToFile(); // Сохраняем измененные данные в файл
                std::cout << "Client data updated successfully." << std::endl; // Подсказка для продолжения
            } else {
                std::cout << "Client data was not updated." << std::endl;
            }
            std::cout << "Press Enter to continue..."; // Подсказка для продолжения
            std::cin.ignore(); // Игнорируем символ новой строки во входном потоке
            std::cin.get(); // Ждать нажатия клавиши Enter
            break; // Завершаем цикл после изменения данных клиента
        }
    }
    if (!found) { // Если клиент не найден
        std::cout << "Client not found." << std::endl; // Выводим сообщение о том, что клиент не найден
        std::cout << "Press Enter to continue..."; // Подсказка для продолжения
        std::cin.ignore(); // Игнорируем символ новой строки во входном потоке
        std::cin.get(); // Ждать нажатия клавиши Enter
    }
}

void ClientService::viewSchedule() {
    std::ifstream scheduleFile("client_appointments.txt"); // Открываем файл с расписанием
    if (!scheduleFile.is_open()) {  // Проверяем, успешно ли открыт файл
        std::cerr << "Error: Unable to open schedule file" << std::endl; // Выводим сообщение об ошибке, если файл не удалось открыть
        return; // Завершаем функцию
    }

    std::string appointment;
    std::cout << "Scheduled appointments:" << std::endl; // Выводим заголовок списка назначенных приемов
    while (std::getline(scheduleFile, appointment)) {  // Читаем строки из файла и выводим их
        std::cout << appointment << std::endl; // Выводим каждый назначенный прием
    }

    scheduleFile.close(); // Закрываем файл
}

void ClientService::displayClientServiceMenu() {
    int choice; // Объявляем переменную для хранения выбора пользователя
    do {
        system("cls"); // Очистить экран

        std::cout << "Client and Service Settings Menu:\n"; // Отобразить название меню

        // Отобразить варианты меню
        std::cout << "1. Add client\n";
        std::cout << "2. Edit client data\n";
        std::cout << "3. Remove client\n";
        std::cout << "4. View all clients\n";
        std::cout << "5. Add service\n";
        std::cout << "6. Remove service\n";
        std::cout << "7. View all services\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice; // Получить выбор пользователя

        switch (choice) { // Обработать выбор пользователя
        case 1: { // Добавить клиента
            std::string newName, newEmail, newPhoneNumber;
            std::cout << "Enter client name: ";
            std::cin >> newName;
            std::cout << "Enter client email: ";
            std::cin >> newEmail;
            std::cout << "Enter client phone number: ";
            std::cin >> newPhoneNumber;
            std::string consent;

            std::cout << "Do you consent to add the client data? (yes/no): ";
            std::cin >> consent;

            if (consent == "yes") {
                Client newClient(newName, newEmail, newPhoneNumber);
                addClient(newClient); // Добавить нового клиента
                std::cout << "Data saved successfully." << std::endl;
            } else {
                std::cout << "Client data was not added." << std::endl;
            }

            std::cout << "Press Enter to continue..."; // Подсказка для продолжения
            std::cin.ignore(); // Игнорируем символ новой строки во входном потоке
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }

        case 2: { // Редактировать данные клиента
            editClientData();
            break;
        }
        case 3: { // Удалить клиента
            std::string clientName;
            std::cout << "Enter client name to remove: ";
            std::cin >> clientName;
            removeClient(clientName); // Вызов метода для удаления клиента
            std::cout << "Press Enter to continue...";
            std::cin.get();
            std::cin.get();
            break;
        }
        case 4: { // Просмотр клиентов
            viewClientsFromFile(); // Вызов метода для просмотра клиентов
            std::cout << "Press Enter to continue..."; // Подсказка для продолжения
            std::cin.get(); // Ждать нажатия клавиши Enter
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }
        case 5: { // Добавить услугу
            std::string serviceName;
            double servicePrice;
            std::string serviceDescription; // Добавлено для ввода описания услуги
            std::cout << "Enter service name: ";
            std::cin >> serviceName;
            std::cout << "Enter service price: ";
            std::cin >> servicePrice;
            std::cout << "Enter service description: "; // Запрос на ввод описания услуги
            std::cin >> std::ws; // Очистка буфера перед вводом строки
            std::getline(std::cin, serviceDescription); // Ввод описания услуги

            Service newService(serviceName, servicePrice, serviceDescription); // Использование конструктора с описанием
            addService(newService); // Добавить новую услугу
            std::cout << "Data saved. Press Enter to continue..."; // Подсказка для продолжения
            std::cin.get(); // Ждать нажатия клавиши Enter
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }

        case 6: { // Удалить услугу
            std::string serviceName;
            std::cout << "Enter service name to remove: ";
            std::cin >> serviceName;
            removeService(serviceName); // Вызов метода для удаления услуги
            std::cout << "Press Enter to continue..."; // Подсказка для продолжения
            std::cin.get(); // Ждать нажатия клавиши Enter
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }
        case 7: { // Просмотреть все услуги
            Service service;
            service.viewServicesFromFile(); // Вызов метода для просмотра услуг
            std::cout << "Press Enter to continue..."; // Подсказка для продолжения
            std::cin.get(); // Ждать нажатия клавиши Enter
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }
        default: // По умолчанию для недопустимого выбора
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 8); // Повторять, пока пользователь не выберет выход
}
