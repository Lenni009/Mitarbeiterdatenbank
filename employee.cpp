#include <iostream>
#include <sstream>
#include "employee.hpp"

Employee::Employee(int employeeId, std::string name, std::string firstName, std::string postalCode, float salary, int yearsOfEmployment)
{
  this->employeeId_ = employeeId;
  this->name_ = name;
  this->firstName_ = firstName;
  this->postalCode_ = postalCode;
  this->salary_ = salary;
  this->yearsOfEmployment_ = yearsOfEmployment;
}

// getters

int Employee::getYearsOfEmployment()
{
  return yearsOfEmployment_;
}

int Employee::getEmployeeId()
{
  return employeeId_;
}

std::string Employee::getEmployeeName()
{
  return name_;
}

std::string Employee::getEmployeeFirstName()
{
  return firstName_;
}

// all data in one comma-separated string

std::string Employee::getEmployeeData()
{
  char sep = ',';
  // std::to_string() has unexpected behaviour with floats, so we're using stringstreams instead.
  // solution from https://stackoverflow.com/questions/2125880/convert-float-to-stdstring-in-c
  std::ostringstream strstream;
  strstream << salary_;
  std::string salaryString(strstream.str());
  return std::string(name_ + sep + firstName_ + sep + postalCode_ + sep + salaryString + sep + std::to_string(yearsOfEmployment_));
}

// log data formatted as key/value pairs to the console

void Employee::outputDataToConsole()
{
  std::cout << "Mitarbeiternummer: " << employeeId_ << std::endl;
  std::cout << "Name: " << name_ << std::endl;
  std::cout << "Vorname: " << firstName_ << std::endl;
  std::cout << "PLZ: " << postalCode_ << std::endl;
  std::cout << "Gehalt: " << salary_ << std::endl;
  std::cout << "Jahre der Betriebszugehörigkeit: " << yearsOfEmployment_ << std::endl;
}

// setters

void Employee::adjustSalary(float factor)
{
  salary_ *= factor;
}

void Employee::increaseYearsOfEmployment()
{
  yearsOfEmployment_++;
}
