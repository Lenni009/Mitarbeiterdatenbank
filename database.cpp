#include <string>
#include <iostream>
#include <fstream>
#include "database.hpp"

Database::Database()
{
}

Database::~Database()
{
}

void Database::readFile(std::string path)
{
  std::ifstream file(path);

  // read fist line of file
  std::string line;
  std::getline(file, line);

  // log to console
  std::cout << " Inhalt der Zeile ist \"" << line << "\"" << std ::endl;
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
