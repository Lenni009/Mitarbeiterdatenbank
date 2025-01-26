#include <iostream>
#include "employee.hpp"

Employee::Employee(unsigned int employeeId, std::string name, std::string firstName, std::string postalCode, float salary, unsigned int yearsOfEmployment)
{
  this->employeeId = employeeId;
  this->name = name;
  this->firstName = firstName;
  this->postalCode = postalCode;
  this->salary = salary;
  this->yearsOfEmployment = yearsOfEmployment;
}

Employee::~Employee()
{
}

void Employee::increaseSalary(float factor)
{
  salary *= factor;
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

std::string Employee::getEmployeeName()
{
  return name;
}

std::string Employee::getEmployeeFirstName()
{
  return firstName;
}

std::string Employee::getEmployeeData()
{
  char sep = ',';
  return std::string(std::to_string(employeeId) + sep + name + sep + firstName + sep + postalCode + sep + std::to_string(salary) + std::to_string(yearsOfEmployment));
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
