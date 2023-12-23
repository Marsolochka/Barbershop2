#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

#include "client.h"
#include "service.h"
#include <vector>
#include <fstream>

class ClientService {
public:
    void addClient(const Client& client);
       void scheduleService(); // Объявление метода scheduleService
       // Остальные методы и члены класса
    // Изменим параметры на объект типа Service
    void displayClientServiceMenu();
    void viewClientsFromFile();
    void editClientData();
    void addService(const Service& service);
    void loadClientsFromFile();
    void viewServicesFromFile();
    void editServiceData(const std::string& serviceName, double newCost, const std::string& newDescription); // Добавим объявление метода для редактирования данных об услуге
    void loadServicesFromFile(); // Метод для загрузки данных об услугах из файла
    void editService(const std::string& serviceName, double newPrice, const std::string& newDescription);
    void saveClientsToFile();
    void saveServicesToFile();
    void writeClientAppointment();
    void setDescription(const std::string& description);
    void viewSchedule();
    void cancelClientAppointment(const std::string& date, const std::string& time);
    void writeClientAppointments(const std::string& startDate, const std::string& endDate);
private:
    std::vector<Client> clients;
    std::vector<Service> services; // Изменим тип вектора для хранения объектов типа Service
    std::string description;
    void removeClient(const std::string& clientName);
    void removeService(const std::string& serviceName); // Добавим объявление метода для удаления услуги

};

#endif // CLIENT_SERVICE_H
