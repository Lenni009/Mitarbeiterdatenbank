#pragma once
// while technically non-standard, `#pragma once` is widely supported and unlikely to break in the scope of this project
// https://en.wikipedia.org/wiki/Pragma_once
// https://stackoverflow.com/questions/787533/is-pragma-once-a-safe-include-guard
#include <vector>
#include <string>
#include <employee.hpp>

// this class should only be instantiated once.
// since this project's scope is quite limited, the singleton pattern is not used here, as it would be unnecessary overhead.
class Database
{
private:
  std::vector<Employee> db;

public:
  Database();
  ~Database();
  void readFile(std::string path);
  void saveFile(std::string path);
  void removeEmployee(unsigned int employeeId);
  std::vector<Employee> findEmployee(std::string name, std::string firstName);
  std::vector<Employee> employmentAnniversary(unsigned int yearsOfEmployment);
};
