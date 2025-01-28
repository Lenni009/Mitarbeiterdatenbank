#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>
#include "database.hpp"
#include "employee.hpp"

void Database::readFile(std::string path)
{
  std::ifstream file(path);

  // read file
  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }
    std::stringstream strStream(line);
    std::string value;
    char sep = ',';
    std::vector<std::string> args;
    while (std::getline(strStream, value, sep))
    {
      args.push_back(value);
    }

    float salary = std::stof(args.at(3));
    unsigned int yearsOfEmployment = std::stoi(args.at(4));
    addEmployee(args.at(0), args.at(1), args.at(2), salary, yearsOfEmployment);
  }
}

void Database::saveFile(std::string path)
{
  std::string outputText;

  for (Employee &employee : db)
  {
    outputText += employee.getEmployeeData();
    outputText += "\n\n"; // adding empty line between entries
  }

  // https://www.w3schools.com/cpp/cpp_files.asp
  // create and open a text file
  std::ofstream dbFile(path);

  // write to the file
  dbFile << outputText;

  // close the file
  dbFile.close();
}

unsigned int Database::addEmployee(std::string name, std::string firstName, std::string postalCode, float salary, unsigned int yearsOfEmployment)
{
  unsigned int employeeId = getNewEmployeeId();

  // using unique_ptr to automatically allocate/deallocate memory when object is created/goes out of scope
  std::unique_ptr<Employee> employee = std::make_unique<Employee>(employeeId, name, firstName, postalCode, salary);

  db.push_back(*employee);
  return employeeId;
}

void Database::removeEmployee(unsigned int employeeId)
{
  const int employeeIndex = getEmployeeIndexById(employeeId);

  if (employeeIndex != -1)
  {
    // https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
    db.erase(db.begin() + employeeIndex);
  }
}

// returning an int so we can check for invalid IDs
int Database::getEmployeeIndexById(unsigned int employeeId)
{
  // find element where Employee.employeeId == employeeId
  // returns an iterator
  const auto it = std::find_if(db.begin(), db.end(), [&employeeId](Employee &employee)
                               { return employee.getEmployeeId() == employeeId; });
  if (it != db.end())
  {
    return it - db.begin();
  }
  else
  {
    std::cout << "Ungültige Mitarbeiternummer!" << std::endl;
    return -1;
  }
}

Employee &Database::getEmployeeByIndex(unsigned int index)
{
  return db.at(index);
}

unsigned int Database::getNewEmployeeId()
{
  if (db.size())
  {
    return db.back().getEmployeeId() + 1;
  }
  else
  {
    return 0;
  }
}

std::vector<unsigned int> Database::findEmployee(std::string name, std::string firstName)
{
  std::vector<unsigned int> filterResults;
  for (Employee &employee : db)
  {
    if (employee.getEmployeeName() == name && employee.getEmployeeFirstName() == firstName)
    {
      filterResults.push_back(employee.getEmployeeId());
    }
  }
  return filterResults;
}

std::vector<unsigned int> Database::employmentAnniversary(unsigned int yearsOfEmployment)
{
  std::vector<unsigned int> filterResults;
  for (Employee &employee : db)
  {
    if (employee.getYearsOfEmployment() == yearsOfEmployment)
    {
      filterResults.push_back(employee.getEmployeeId());
    }
  }
  return filterResults;
}

void Database::viewDB()
{
  // access by reference to avoid copying
  for (Employee &employee : db)
  {
    employee.outputDataToConsole();
    std::cout << std::endl;
  }
}

// fancy wrapper around the employee's class own method, but it is required by the task that this method exists on the DB
void Database::increaseSalary(unsigned int employeeId, float factor)
{
  int employeeIndex = getEmployeeIndexById(employeeId);
  // -1 = invalid index, ID doesn't exist
  if (employeeIndex != -1)
  {
    Employee &employee = getEmployeeByIndex(employeeIndex);
    employee.increaseSalary(factor);
  }
}

// another method that the task requires to be on the DB object
void Database::increaseYearsOfEmployment(unsigned int employeeId)
{
  // the code here is pretty much similar to the above method, but I'm lacking the knowledge to make this generic.
  // since a function in C++ can only have one return type (as far as I know), I cannot declare a method that *might* return an employee, or might return void.
  // so the alternative is to return an int and then check whether that int has an expected value.
  int employeeIndex = getEmployeeIndexById(employeeId);
  // -1 = invalid index, ID doesn't exist
  if (employeeIndex != -1)
  {
    Employee &employee = getEmployeeByIndex(employeeIndex);
    employee.increaseYearsOfEmployment();
  }
}

bool Database::isEmployeeIdValid(unsigned int employeeId)
{
  return getEmployeeIndexById(employeeId) != -1;
}
