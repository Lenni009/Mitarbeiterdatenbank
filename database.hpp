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
  // file operations
  void readFile(std::string path);
  void saveFile(std::string path);

  // employee add/remove
  // the task dictates the following: `int mitarbeiternummer = datenbank.neuerMitarbeiter ( name , vorname , plz , gehalt );`
  // this seems to be an error, since by that definition, the yearsOfEmployment are not stored in the DB, and would always be set to 0 for everyone on program start.
  // this goes against the following statements in the task:
  // "Jeder Mitarbeiter wird durch folgende Einträge beschrieben: Name, Vorname, Postleitzahl, Gehalt, Jahre der Betriebszugehörigkeit."
  // "Die Werte stehen in einer Datei, sodass jede Zeile genau einen der Einträge in der genannten Reihenfolge enthält."
  // therefore this method takes the yearsOfEmployment, despite what the task requires.
  unsigned int addEmployee(std::string name, std::string firstName, std::string postalCode, float salary, unsigned int yearsOfEmployment); // I wouldn't return anything from this function, but the task requires this to return the employee id
  void removeEmployee(unsigned int employeeId);

  // employee item getters
  int getEmployeeIndexById(unsigned int employeeId);
  Employee &getEmployeeByIndex(unsigned int index);

  // get ID for new employee
  unsigned int getNewEmployeeId();

  // employee finders
  std::vector<unsigned int> findEmployeesByName(std::string name, std::string firstName);
  std::vector<unsigned int> findEmployeesByYearsOfEmployment(unsigned int yearsOfEmployment);

  // get output of DB data
  void viewDB();

  // employee data mutations
  // I would just use these methods on the employee objects directly, but the task requires this to be on the db object
  void adjustSalary(unsigned int employeeId, float factor);
  void increaseYearsOfEmployment(unsigned int employeeId);

  // input validation
  bool isEmployeeIdValid(unsigned int employeeId);
};
