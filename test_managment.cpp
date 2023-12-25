#include <iostream>

#include "test_mangment.h"
#include "managment.h"

void writeLn(std::string& msg) {
    std::cout << msg << std::endl;
}

void testManagment() {
    std::string msg = "Test init Managment\n";
    writeLn(msg);
    Managment* managment = new Managment();

    std::string name = "Olga Fesina";
    std::string jobTitle = "Student";
    msg = "Create employee\n"
                      "name: " + name + "\n"
                      "jobTitle: " + jobTitle + "\n";
    writeLn(msg);

    int employeeID = managment->addEmployee(name,jobTitle);
    msg = "Employee added with ID: " + std::to_string(employeeID);
    writeLn(msg);

    name = "Olga Smirnova";
    jobTitle = "Developer";
    msg = "Test edit employee with ID: " + std::to_string(employeeID) + "\n"
            "change name to: " + name + "\n"
            "change jobTitle to: " + jobTitle + "\n";
    writeLn(msg);
    managment->editEmployeeInfo(employeeID, name, jobTitle);
    msg = "Info changed\n";
    writeLn(msg);

    msg = "Test get employee by ID: " + std::to_string(employeeID);
    writeLn(msg);
    msg = managment->getEmployyeInfo(employeeID);
    writeLn(msg);

    msg = "Test remove employee by ID: " + std::to_string(employeeID);
    writeLn(msg);
    managment->removeEmployee(employeeID);
    msg = "Employee with ID: " +  std::to_string(employeeID) + " removed\n";
    writeLn(msg);
}
