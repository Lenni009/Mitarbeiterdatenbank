#include <iostream>
#include <sstream>
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

// getters
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
  // std::to_string() has unexpected behaviour with floats, so we're using stringstreams instead.
  // solution from https://stackoverflow.com/questions/2125880/convert-float-to-stdstring-in-c
  std::ostringstream strstream;
  strstream << salary;
  std::string salaryString(strstream.str());
  return std::string(name + sep + firstName + sep + postalCode + sep + salaryString + sep + std::to_string(yearsOfEmployment));
}

void Employee::outputDataToConsole()
{
  std::cout << "Mitarbeiternummer: " << employeeId << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Vorname: " << firstName << std::endl;
  std::cout << "PLZ: " << postalCode << std::endl;
  std::cout << "Gehalt: " << salary << std::endl;
  std::cout << "Jahre der Betriebszugehörigkeit: " << yearsOfEmployment << std::endl;
}

// setters
void Employee::increaseSalary(float factor)
{
  salary *= factor;
}

void Employee::increaseYearsOfEmployment()
{
  yearsOfEmployment++;
}
