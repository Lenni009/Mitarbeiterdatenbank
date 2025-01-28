#include <iostream>
#include <sstream>
#include "employee.hpp"

/// @brief Constructor for an employee object, holding the employee's data
/// @param employeeId Unique ID of the employee
/// @param name Surname of the employee
/// @param firstName First name of the employee
/// @param postalCode Postal code of where the employee lives
/// @param salary Salary of the employee
/// @param yearsOfEmployment How long the employee has been employed at the company
Employee::Employee(unsigned int employeeId, std::string name, std::string firstName, std::string postalCode, float salary, unsigned int yearsOfEmployment)
{
  this->employeeId = employeeId;
  this->name = name;
  this->firstName = firstName;
  this->postalCode = postalCode;
  this->salary = salary;
  this->yearsOfEmployment = yearsOfEmployment;
}

// getters. They need to be commented as per the task description.

/// @brief Get the years of employment for the employee
/// @return Years of employment of the employee
unsigned int Employee::getYearsOfEmployment()
{
  return yearsOfEmployment;
}

/// @brief Get the unique ID of the employee
/// @return Unique ID of the employee
unsigned int Employee::getEmployeeId()
{
  return employeeId;
}

/// @brief Get Surname of the employee
/// @return Surname of the employee
std::string Employee::getEmployeeName()
{
  return name;
}

/// @brief Get first name of the employee
/// @return First name of the employee
std::string Employee::getEmployeeFirstName()
{
  return firstName;
}

/// @brief Get the employee's data in one delimiter separated string for use in the csv DB file
/// @return The employee's data in one delimiter separated string
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

/// @brief Output the employee's data in a human readable format to the console
void Employee::outputDataToConsole()
{
  std::cout << "Mitarbeiternummer: " << employeeId << std::endl;
  std::cout << "Name: " << name << std::endl;
  std::cout << "Vorname: " << firstName << std::endl;
  std::cout << "PLZ: " << postalCode << std::endl;
  std::cout << "Gehalt: " << salary << std::endl;
  std::cout << "Jahre der Betriebszugehörigkeit: " << yearsOfEmployment << std::endl;
}

// setters. These also need to be commented as per the task description.

/// @brief Adjust the employee's salary
/// @param factor Factor by which the employee's salary should be adjusted. Must be >= 0.
void Employee::adjustSalary(float factor)
{
  salary *= factor;
}

/// @brief Increases the years of employment of the employee by 1
void Employee::increaseYearsOfEmployment()
{
  yearsOfEmployment++;
}
