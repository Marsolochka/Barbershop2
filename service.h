#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>

class Service {
public:
    Service(const std::string& name, double cost, const std::string& description);
    std::string getName() const;
    double getCost() const;
    std::string getDescription() const;
    void setCost(double cost);
    void setDescription(const std::string& description); // Setter function for description
    std::string getDate() const {
        return date;
    }
    std::string getTime() const {
        return time;
    }


private:
    std::string name;
    double cost;
    std::string description;
    std::string date;
    std::string time;
};

#endif // SERVICE_H
