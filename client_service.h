#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

#include "client.h"

#include "service.h"

#include <vector>

#include <fstream>

class ClientService {
    public:

    void generateReport(const std::string & startDateTime,
        const std::string & endDateTime); // Объявление метода для генерации отчета
    void addClient(const Client & client);  // Объявление метода для добавления клиента
    void scheduleService(); // Объявление метода для планирования услуги
    void displayClientServiceMenu(); // Объявление метода для отображения меню клиентских услуг
    void viewClientsFromFile();// Объявление метода для загрузки клиентов из файла
    void editClientData();  // Объявление метода для редактирования данных клиента
    void addService(const Service & service); // Объявление метода для добавления услуги
    void loadClientsFromFile(); // Объявление метода для загрузки клиентов из файла
    void editServiceData(const std::string & serviceName, double newCost,
        const std::string & newDescription); // Объявление метода для редактирования данных об услуге
    void loadServicesFromFile(); // Метод для загрузки данных об услугах из файла
    void editService(const std::string & serviceName, double newPrice,
        const std::string & newDescription);   // Объявление метода для редактирования услуги
    void saveClientsToFile();  // Объявление метода для сохранения клиентов в файл
    void saveServicesToFile(); // Объявление метода для сохранения услуг в файл
    void writeClientAppointment(); // Объявление метода для записи приема клиента
    void setDescription(const std::string & description); // Объявление метода для установки описания
    void viewSchedule(); // Объявление метода для просмотра расписания
    void writeClientAppointments(const std::string & startDate,
        const std::string & endDate); // Объявление метода для записи приемов клиента в указанный период
    void deleteClientAppointment(const std::string & date,
        const std::string & time); // Объявление метода для удаления приема клиента
    void removeClient(const std::string & clientName); // Объявление метода для удаления клиента
    void removeService(const std::string & serviceName); // Объявление метода для удаления услуги

    private:
    std::vector < Client > clients; // Вектор для хранения объектов типа Client
    std::vector < Service > services;// Вектор для хранения объектов типа Service
    std::string description;  // Переменная для хранения описания


};

#endif // CLIENT_SERVICE_H
