#ifndef MANAGMENT_H
#define MANAGMENT_H
#include "vector"
#include <string>

class Employee {
public:
    Employee(const std::string& name, const std::string& jobTitle);
    void setName(const std::string& newName);
    void setJobTitle(const std::string& newJobTitle);
    std::string getName();
    std::string getJobTitle();
private:
    std::string name;
    std::string jobTitle;
};

class Managment {
public:
    int addEmployee(const std::string& name, const std::string& jobTitle);
    void removeEmployee(int employeeId);
    void editEmployeeInfo(int employeeId, const std::string& newName, const std::string& newJobTitle);
    std::string getEmployyeInfo(int employeeId);
private:
    std::vector<Employee*> employees;
};

#endif // MANAGMENT_H

