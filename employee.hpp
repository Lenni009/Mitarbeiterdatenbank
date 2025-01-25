#pragma once
#include <string>
#include <vector>

class Employee
{
private:
  unsigned int employeeId;
  std::string name;
  std::string firstName;
  unsigned int postalCode; // 12345
  float salary;            // no huge decimal needed, saving memory by using float instead of double
  unsigned int yearsOfEmployment;

public:
  Employee(unsigned int employeeId, std::string name, std::string firstName, unsigned int postalCode, float salary, unsigned int yearsOfEmployment);
  ~Employee();
  // getters
  unsigned int getYearsOfEmployment();
  unsigned int getEmployeeId();

  // mutate data
  void increaseSalary(unsigned int factor); // "increase" as per task description -> can only go up -> int cannot be signed -> using unsigned int
  void increaseYearsOfEmployment();
};
