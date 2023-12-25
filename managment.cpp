#include "managment.h"
#include <stdexcept>

Employee::Employee(const std::string& name, const std::string& jobTitle)
    : name(name), jobTitle(jobTitle) {}

void Employee::setName(const std::string& newName) {
    name = newName;
}

void Employee::setJobTitle(const std::string& newJobTitle) {
    jobTitle = newJobTitle;
}

std::string Employee::getName() {
    return name;
}

std::string Employee::getJobTitle() {
    return jobTitle;
}

int Managment::addEmployee(const std::string &name, const std::string &jobTitle) {
    Employee* employee = new Employee(name, jobTitle);
    employees.push_back(employee);
    return employees.size() - 1;
}

void Managment::editEmployeeInfo(int employeeId, const std::string &newName, const std::string &newJobTitle) {
    Employee* employee = employees[employeeId];
    if (!employee) {
        throw std::runtime_error("Not found employee with ID: " + std::to_string(employeeId));
    }
    employee->setName(newName);
    employee->setJobTitle(newJobTitle);
}

void Managment::removeEmployee(int employeeId) {
    Employee* employee = employees[employeeId];
    if (!employee) {
        throw std::runtime_error("Not found employee with ID: " + std::to_string(employeeId));
    }
    employees[employeeId] = nullptr;
}

std::string  Managment::getEmployyeInfo(int employeeId) {
    Employee* employee = employees[employeeId];
    if (!employee) {
        throw std::runtime_error("Not found employee with ID: " + std::to_string(employeeId));
    }

    return "ID: " + std::to_string(employeeId) + "\n"
            "Name: " + employee->getName() + "\n"
            "JobTitle: " + employee->getName();
}
