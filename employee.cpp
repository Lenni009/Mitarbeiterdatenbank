#include <iostream>
#include "employee.hpp"

Employee::Employee(unsigned int employeeId, std::string name, std::string firstName, unsigned int postalCode, float salary, unsigned int yearsOfEmployment)
{
}

Employee::~Employee()
{
}

void Employee::increaseSalary(unsigned int factor)
{
  salary += salary * factor;
}

void Employee::increaseYearsOfEmployment()
{
  yearsOfEmployment++;
}

unsigned int Employee::getYearsOfEmployment()
{
  return yearsOfEmployment;
}

unsigned int Employee::getEmployeeId()
{
  return employeeId;
}

void Employee::outputDataToConsole()
{
  std::cout << "ID: " << employeeId << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Vorname: " << firstName << std::endl;
  std::cout << "PLZ: " << postalCode << std::endl;
  std::cout << "Gehalt: " << salary << std::endl;
  std::cout << "Jahre der Betriebszugehörigkeit: " << yearsOfEmployment << std::endl;
}
