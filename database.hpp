#pragma once
// while technically non-standard, `#pragma once` is widely supported and unlikely to break in the scope of this project
// https://en.wikipedia.org/wiki/Pragma_once
// https://stackoverflow.com/questions/787533/is-pragma-once-a-safe-include-guard
#include <vector>
#include <string>
#include "employee.hpp"

// this class should only be instantiated once.
// since this project's scope is quite limited, the singleton pattern is not used here, as it would be unnecessary overhead and complexity.
// should it ever become necessary to implement, look here: https://refactoring.guru/design-patterns/singleton/cpp/example
class Database
{
private:
  std::vector<Employee> db;

public:
  Database();
  ~Database();

  // file operations
  void readFile(std::string path);
  void saveFile(std::string path);

  // employee add/remove
  unsigned int addEmployee(std::string name, std::string firstName, std::string postalCode, float salary); // I wouldn't return anything from this function, but the task requires this to return the employee id
  void removeEmployee(unsigned int employeeId);

  // employee item getters
  int getEmployeeIndexById(unsigned int employeeId);
  Employee getEmployeeByIndex(unsigned int index);

  // get ID for new employee
  unsigned int getNewEmployeeId();

  // employee finders
  std::vector<unsigned int> findEmployee(std::string name, std::string firstName);
  std::vector<unsigned int> employmentAnniversary(unsigned int yearsOfEmployment);

  // get output of DB data
  void viewDB();

  // employee data mutations
  // I would just use these methods on the employee objects directly, but the task requires this to be on the db object
  void increaseSalary(unsigned int employeeId, float factor);
  void increaseYearsOfEmployment(unsigned int employeeId);

  // input validation
  bool isEmployeeIdValid(unsigned int employeeId);
};
