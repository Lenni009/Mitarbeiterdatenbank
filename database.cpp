#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "database.hpp"
#include "employee.hpp"

Database::Database()
{
}

Database::~Database()
{
}

void Database::readFile(std::string path)
{
  std::ifstream file(path);

  // read file
  std::string line;
  while (std::getline(file, line))
  {
    char sep = ',';
    std::stringstream strStream(line);
    std::string value;
    std::vector<std::string> args;
    while (std::getline(strStream, value, sep))
    {
      args.push_back(value);
    }

    unsigned int employeeId = stoi(args.at(0));
    unsigned int postalCode = stoi(args.at(3));
    unsigned int salary = stoi(args.at(4));
    unsigned int yearsOfEmployment = stoi(args.at(5));
    Employee *employee = new Employee(employeeId, args.at(1), args.at(2), postalCode, salary, yearsOfEmployment);
    db.push_back(*employee);
  }
}

void Database::saveFile(std::string path)
{
}

void Database::removeEmployee(unsigned int employeeId)
{
}

std::vector<Employee> Database::findEmployee(std::string name, std::string firstName)
{
  return std::vector<Employee>();
}

std::vector<Employee> Database::employmentAnniversary(unsigned int yearsOfEmployment)
{
  return std::vector<Employee>();
}
