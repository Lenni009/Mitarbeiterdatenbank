#pragma once
#include <string>
#include <vector>

/// @brief Class for the employee objects inside the DB. Contains all employee data and methods to read and manipulate that data.
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
  /// @brief Constructor for an employee object, holding the employee's data
  /// @param employeeId Unique ID of the employee
  /// @param name Surname of the employee
  /// @param firstName First name of the employee
  /// @param postalCode Postal code of where the employee lives
  /// @param salary Salary of the employee
  /// @param yearsOfEmployment How long the employee has been employed at the company
  Employee(unsigned int employeeId, std::string name, std::string firstName, std::string postalCode, float salary, unsigned int yearsOfEmployment);

  // getters
  // individual attributes

  /// @brief Get the unique ID of the employee
  /// @return Unique ID of the employee
  unsigned int getEmployeeId();

  /// @brief Get Surname of the employee
  /// @return Surname of the employee
  std::string getEmployeeName();

  /// @brief Get first name of the employee
  /// @return First name of the employee
  std::string getEmployeeFirstName();

  /// @brief Get the years of employment for the employee
  /// @return Years of employment of the employee
  unsigned int getYearsOfEmployment();

  /// @brief Get the employee's data in one delimiter separated string for use in the csv DB file
  /// @return The employee's data in one delimiter separated string
  std::string getEmployeeData();

  /// @brief Output the employee's data in a human readable format to the console
  void outputDataToConsole();

  // mutate data

  /// @brief Adjust the employee's salary
  /// @param factor Factor by which the employee's salary should be adjusted. Must be > 0.
  void adjustSalary(float factor); // no huge precision needed -> using float instead of double

  /// @brief Increases the years of employment of the employee by 1
  void increaseYearsOfEmployment();
};
