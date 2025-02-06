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

/// @brief Wrapper class for the employee database object. Holds methods to read/write to and from the DB.
class Database
{
private:
  std::vector<Employee> db;

public:
  // file operations

  /// @brief Reads the specified file and fills the DB vector. Expects a csv file.
  /// @param path Path to the file to read
  void readFile(std::string path);

  /// @brief Saves the DB vector's data to the given csv file
  /// @param path Path to the csv file the data should be saved to
  void saveFile(std::string path);

  /// @brief Add an employee object to the DB vector
  /// @param name Surname of the employee
  /// @param firstName First name of the employee
  /// @param postalCode Postal code of where the employee lives
  /// @param salary The employee's salary
  /// @param yearsOfEmployment How long the employee has been employed at the company
  /// @return The employee's unique ID to identify them in the DB during runtime
  unsigned int addEmployee(std::string name, std::string firstName, std::string postalCode, float salary, unsigned int yearsOfEmployment);

  /// @brief Removes an employee with a given ID from the DB
  /// @param employeeId ID of the employee to be removed
  void removeEmployee(unsigned int employeeId);

  // employee item getters

  /// @brief Gets the index of an employee object with a specific ID
  /// @param employeeId The ID to be searched for in the DB
  /// @return The index where the wanted employee object is in the vector. Returns -1 if not found.
  int getEmployeeIndexById(unsigned int employeeId);

  /// @brief Get a reference to the employee object at a specific index in the DB vector
  /// @param index index in the DB to get a reference to
  /// @return Reference to the employee object at the given index
  Employee &getEmployeeByIndex(unsigned int index);

  /// @brief Get unique ID for new employee
  /// @return Unique ID for new employee
  unsigned int getNewEmployeeId();

  // employee finders

  /// @brief Get a list of employee IDs filtered by the employees' names
  /// @param name Surname of the employee (case sensitive)
  /// @param firstName First name of the employee (case sensitive)
  /// @return Vector of employee IDs that match the given name combination
  std::vector<unsigned int> findEmployeesByName(std::string name, std::string firstName);

  /// @brief Get a list of employee IDs filtered by the employees' years of employment
  /// @param yearsOfEmployment Specific number of years that should be filtered by
  /// @return Vector of employee IDs that match the given years of employment
  std::vector<unsigned int> findEmployeesByYearsOfEmployment(unsigned int yearsOfEmployment);

  /// @brief Outputs all DB entries in a human readable format to the console
  void viewDB();

  // employee data mutations

  /// @brief Adjust (increase/decrease) the salary of an employee with a given employee ID by a given factor.
  /// @param employeeId ID of the employee whose salary should be increased
  /// @param factor Factor by which the salary should be increased. Must be > 0.
  void adjustSalary(unsigned int employeeId, float factor);

  /// @brief Increase the years of employment for an employee with a given employee ID
  /// @param employeeId ID of the employee whose years of employment should be increased
  void increaseYearsOfEmployment(unsigned int employeeId);

  /// @brief Checks whether a given ID exists in the DB
  /// @param employeeId Employee ID to check
  /// @return Whether the given employee ID exists in the DB
  bool isEmployeeIdValid(unsigned int employeeId);
};
