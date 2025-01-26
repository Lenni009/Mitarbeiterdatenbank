#pragma once
#include <string>
#include <vector>

class Employee
{
private:
  unsigned int employeeId;
  std::string name;
  std::string firstName;
  std::string postalCode; // 01234 -> using string to preserve leading 0 (would be stripped when using int)
  float salary;           // no huge decimal needed, saving memory by using float instead of double
  unsigned int yearsOfEmployment;

public:
  Employee(unsigned int employeeId, std::string name, std::string firstName, std::string postalCode, float salary, unsigned int yearsOfEmployment);
  ~Employee();
  // getters
  unsigned int getEmployeeId();
  std::string getEmployeeName();
  std::string getEmployeeFirstName();
  unsigned int getYearsOfEmployment();
  std::string getEmployeeData();
  void outputDataToConsole();

  // mutate data
  void increaseSalary(float factor);  // no huge precision needed -> using float instead of double
  void increaseYearsOfEmployment();
};
