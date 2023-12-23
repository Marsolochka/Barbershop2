// client_service.cpp
#include "client_service.h"
#include "service.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Service::Service(const std::string& name, double cost, const std::string& description)
    : name(name), cost(cost), description(description) {}

std::string Service::getName() const {
    return name;
}

double Service::getCost() const {
    return cost;
}

std::string Service::getDescription() const {
    return description;
}

void Service::setCost(double newCost) {
    cost = newCost;
}
void Service::setDescription(const std::string& newDescription) {
    description = newDescription;
}


void ClientService::removeClient(const std::string& clientName) {
    for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->getName() == clientName) {
            clients.erase(it); // Удалить клиента из вектора
            saveClientsToFile(); // Перезаписать данные в файл
            std::cout << "Client removed successfully." << std::endl;
            return;
        }
    }
    std::cout << "Client not found." << std::endl;
}

void ClientService::viewServicesFromFile() {
    std::ifstream file("services.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl; // Вывод каждой строки из файла
        }
        file.close(); // Закрыть файл
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl;
    }
}

void ClientService::loadClientsFromFile() {
    std::ifstream file("clients.txt");
    if (file.is_open()) {
        std::string name, email, phoneNumber;
        while (file >> name >> email >> phoneNumber) {
            clients.push_back(Client(name, email, phoneNumber)); // Добавить клиента в вектор
        }
        file.close(); // Закрыть файл
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl;
    }
    if (file.bad()) {
        std::cerr << "Error: Failed to read data from file" << std::endl;
    }
}



void ClientService::addClient(const Client& client) {
    clients.push_back(client); // Add client to the list
    saveClientsToFile(); // Save clients to file
}

void ClientService::saveClientsToFile() {
    std::ofstream file("clients.txt"); // Открыть файл для записи (существующий файл будет перезаписан)
    if (file.is_open()) {
        for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
            const Client& client = *it;
            file << client.getName() << " " << client.getEmail() << " " << client.getPhoneNumber() << std::endl; // Записать данные о каждом клиенте в файл
        }
        file.close(); // Закрыть файл
    } else {
        std::cerr << "Error: Unable to open file for writing" << std::endl;
    }
}

void ClientService::generateReport(const std::string& startDateTime, const std::string& endDateTime) {
        // Открываем файл с записями клиентов
        std::ifstream appointmentsFile("client_appointments.txt");
        if (!appointmentsFile.is_open()) {
            std::cerr << "Error: Unable to open client appointments file" << std::endl;
            return;
        }

        // Открываем файл для записи отчёта
        std::ofstream reportFile("report.txt");
        if (!reportFile.is_open()) {
            std::cerr << "Error: Unable to open report file" << std::endl;
            return;
        }

        std::string appointment;
        while (std::getline(appointmentsFile, appointment)) {
            // Разбиваем запись о клиенте на части
            std::string client, service, date, time;
            size_t clientPos = appointment.find("Client: ") + 8;
            size_t servicePos = appointment.find("Service: ") + 9;
            size_t datePos = appointment.find("Date: ") + 6;
            size_t timePos = appointment.find("Time: ") + 6;
            client = appointment.substr(clientPos, servicePos - clientPos - 9);
            service = appointment.substr(servicePos, datePos - servicePos - 10);
            date = appointment.substr(datePos, timePos - datePos - 7);
            time = appointment.substr(timePos);

            // Проверяем, попадает ли запись в указанный период
            if (date + " " + time >= startDateTime && date + " " + time <= endDateTime) {
                reportFile << "Client: " << client << " | Service: " << service << " | Date: " << date << " | Time: " << time << std::endl;
            }
        }

        appointmentsFile.close();
        reportFile.close();
        std::cout << "Report has been successfully generated for the period from " << startDateTime << " to " << endDateTime << std::endl;
    }

void ClientService::writeClientAppointment() {
    // Открываем файл с клиентами
    std::ifstream clientsFile("clients.txt");
    if (!clientsFile.is_open()) {
        std::cerr << "Error: Unable to open clients file" << std::endl;
        return;
    }

    // Выводим список клиентов с их индексами
    std::vector<std::string> clients;
    std::string client;
    int clientIndex = 0;
    while (std::getline(clientsFile, client)) {
        clients.push_back(client);
        std::cout << clientIndex << ". " << client << std::endl;
        clientIndex++;
    }
    clientsFile.close();

    // Предоставляем возможность выбрать клиента по индексу
    int chosenClientIndex;
    std::cout << "Choose the client by entering the index: ";
    std::cin >> chosenClientIndex;
    if (chosenClientIndex < 0 || chosenClientIndex >= clients.size()) {
        std::cout << "Invalid client index" << std::endl;
        return;
    }
    std::string chosenClient = clients[chosenClientIndex];

    // Открываем файл с услугами
    std::ifstream servicesFile("services.txt");
    if (!servicesFile.is_open()) {
        std::cerr << "Error: Unable to open services file" << std::endl;
        return;
    }

    // Выводим список услуг с их индексами
    std::vector<std::string> services;
    std::string service;
    int serviceIndex = 0;
    while (std::getline(servicesFile, service)) {
        services.push_back(service);
        std::cout << serviceIndex << ". " << service << std::endl;
        serviceIndex++;
    }
    servicesFile.close();

    // Предоставляем возможность выбрать услугу по индексу
    int chosenServiceIndex;
    std::cout << "Choose the service by entering the index: ";
    std::cin >> chosenServiceIndex;
    if (chosenServiceIndex < 0 || chosenServiceIndex >= services.size()) {
        std::cout << "Invalid service index" << std::endl;
        return;
    }
    std::string chosenService = services[chosenServiceIndex];

    // Ввод даты и времени
    std::string date, time;
    std::cout << "Enter the date for the appointment (e.g. 2023-09-15): ";
    std::cin >> date;
    std::cout << "Enter the time for the appointment (e.g. 14:30): ";
    std::cin >> time;

    // Запись информации о записи клиента
    std::ofstream outputFile("client_appointments.txt", std::ios::app); // Открываем файл для добавления информации
    if (outputFile.is_open()) {
        outputFile << "Client: " << chosenClient << " | Service: " << chosenService << " | Date: " << date << " | Time: " << time << std::endl; // Записываем информацию о клиенте, выбранной услуге и времени записи
        outputFile.close();
        std::cout << "Client " << chosenClient << " has been successfully added for the service " << chosenService << " at " << time << " on " << date << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing" << std::endl;

    }
}

void ClientService::deleteClientAppointment(const std::string& date, const std::string& time) {
    std::ifstream inputFile("client_appointments.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open client appointments file" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::string appointment = "Date: " + date + " | Time: " + time;
        if (line.find(appointment) == std::string::npos) {
            lines.push_back(line);
        }
    }
    inputFile.close();

    std::ofstream outputFile("client_appointments.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open client appointments file for writing" << std::endl;
        return;
    }

    for (const auto& l : lines) {
        outputFile << l << std::endl;
    }
    outputFile.close();

    std::cout << "Client appointments for the date " << date << " and time " << time << " have been successfully deleted" << std::endl;
}



void ClientService::saveServicesToFile() {
    std::ifstream readFile("services.txt"); // Открываем файл для чтения
    std::vector<std::string> existingServices;

    if (readFile.is_open()) {
        std::string line;
        while (std::getline(readFile, line)) {
            existingServices.push_back(line);
        }
        readFile.close();
    }

    std::ofstream file("services.txt", std::ios::app); // Открываем файл для добавления информации в конец
    if (file.is_open()) {
        for (size_t i = 0; i < services.size(); ++i) {
            std::stringstream ss;
            ss << services[i].getCost();
            std::string costStr = ss.str();
            std::string serviceInfo = services[i].getName() + " | Cost: " + costStr + " | " + services[i].getDescription();
            bool alreadyExists = false;
            for (size_t j = 0; j < existingServices.size(); ++j) {
                if (existingServices[j] == serviceInfo) {
                    alreadyExists = true;
                    break;
                }
            }
            if (!alreadyExists) {
                file << serviceInfo << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file for writing" << std::endl;
    }
}



void ClientService::viewClientsFromFile() {
    std::ifstream file("clients.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl; // Output each line from the file
        }
        file.close(); // Close the file
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl;
    }
}
void ClientService::addService(const Service& service) {
    // Проверяем, что такой услуги еще нет в списке
    bool serviceExists = false;
    for (size_t i = 0; i < services.size(); ++i) {
        if (services[i].getName() == service.getName()) {
            serviceExists = true;
            break;
        }
    }

    if (!serviceExists) {
        services.push_back(service); // Добавить услугу в список

        // Добавляем информацию о новой услуге в файл
        std::ofstream outputFile("services.txt", std::ios::app); // Открываем файл для добавления информации
        if (outputFile.is_open()) {
            outputFile << service.getName() << " | Cost: " << service.getCost() << " | " << service.getDescription() << std::endl; // Сохраняем название, стоимость и описание услуги
            outputFile.close();
        } else {
            std::cerr << "Error: Unable to open file for writing" << std::endl;
        }
        saveServicesToFile(); // Сохраняем все услуги в файл
    } else {
        std::cout << "Service already exists." << std::endl;
    }
}



void ClientService::loadServicesFromFile() {
    std::ifstream file("services.txt");
    if (file.is_open()) {
        std::string name;
        double price;
        std::string description;
        while (file >> name >> price) {
            file.ignore(); // Ignoring the newline character after price
            std::getline(file, description);
            services.push_back(Service(name, price, description));
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file for reading" << std::endl;
    }
    if (file.bad()) {
        std::cerr << "Error: Failed to read data from file" << std::endl;
    }
}


void ClientService::removeService(const std::string& serviceName) {
    for (size_t i = 0; i < services.size(); ++i) {
        if (services[i].getName() == serviceName) {
            services.erase(services.begin() + i); // Удаляем услугу из списка
            saveServicesToFile(); // Сохраняем изменения в файл
            return;
        }
    }
    std::cout << "Service not found." << std::endl;
}

void ClientService::editClientData() {
    system("cls"); // Очистить экран
    std::cout << "Enter the name of the client you want to edit: ";
    std::string clientName;
    std::cin >> clientName;

    bool found = false;
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].getName() == clientName) {
            found = true;
            std::string newName, newEmail, newPhoneNumber;
            std::cout << "Enter new name for the client: ";
            std::cin >> newName;
            std::cout << "Enter new email for the client: ";
            std::cin >> newEmail;
            std::cout << "Enter new phone number for the client: ";
            std::cin >> newPhoneNumber;

            clients[i] = Client(newName, newEmail, newPhoneNumber);
            saveClientsToFile(); // Сохранить измененные данные в файл
            std::cout << "Client data updated. Press Enter to continue..."; // Подсказка для продолжения
            std::cin.get(); // Ждать нажатия клавиши Enter
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }
    }
    if (!found) {
        std::cout << "Client not found." << std::endl;
        std::cout << "Press Enter to continue..."; // Подсказка для продолжения
        std::cin.get(); // Ждать нажатия клавиши Enter
        std::cin.get(); // Ждать нажатия клавиши Enter
    }
}




void ClientService::viewSchedule() {
    std::ifstream scheduleFile("client_appointments.txt");
    if (!scheduleFile.is_open()) {
        std::cerr << "Error: Unable to open schedule file" << std::endl;
        return;
    }

    std::string appointment;
    std::cout << "Scheduled appointments:" << std::endl;
    while (std::getline(scheduleFile, appointment)) {
        std::cout << appointment << std::endl;
    }

    scheduleFile.close();
}

void ClientService::displayClientServiceMenu() {
    int choice;
    do {
        system("cls"); // Очистить экран
        std::cout << "Client and Service Settings Menu:\n"; // Отобразить название меню
        // Отобразить варианты меню
        std::cout << "1. Add client\n";
        std::cout << "2. Edit client data\n";
        std::cout << "3. Remove client\n";
        std::cout << "4. View all clients\n";
        std::cout << "5. Add service\n";
        std::cout << "6. Edit service\n";
        std::cout << "7. Remove service\n";
        std::cout << "8. View all services\n";
        std::cout << "9. Exit\n";
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

                    Client newClient(newName, newEmail, newPhoneNumber);
                    addClient(newClient); // Добавить нового клиента
                    std::cout << "Data saved. Press Enter to continue..."; // Подсказка для продолжения
                    std::cin.get(); // Ждать нажатия клавиши Enter
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

        case 7: { // Удалить услугу
            std::string serviceName;
            std::cout << "Enter service name to remove: ";
            std::cin >> serviceName;
            removeService(serviceName); // Вызов метода для удаления услуги
            std::cout << "Press Enter to continue..."; // Подсказка для продолжения
            std::cin.get(); // Ждать нажатия клавиши Enter
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }
        case 8: { // Просмотреть все услуги
            viewServicesFromFile(); // Вызов метода для просмотра услуг
            std::cout << "Press Enter to continue..."; // Подсказка для продолжения
            std::cin.get(); // Ждать нажатия клавиши Enter
            std::cin.get(); // Ждать нажатия клавиши Enter
            break;
        }
        default: // По умолчанию для недопустимого выбора
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 9); // Повторять, пока пользователь не выберет выход
}
