#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
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
    if (line.empty())
    {
      continue;
    }
    char sep = ',';
    std::stringstream strStream(line);
    std::string value;
    std::vector<std::string> args;
    while (std::getline(strStream, value, sep))
    {
      args.push_back(value);
    }

    unsigned int employeeId = std::stoi(args.at(0));
    float salary = std::stof(args.at(4));
    unsigned int yearsOfEmployment = std::stoi(args.at(5));
    Employee *employee = new Employee(employeeId, args.at(1), args.at(2), args.at(3), salary, yearsOfEmployment);
    db.push_back(*employee);
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

void Database::removeEmployee(unsigned int employeeId)
{
  // find where employee.employeeId == employeeId and remove that specific entry from the vector
  db.erase(std::find_if(db.begin(), db.end(), [&employeeId](Employee &employee)
                        { return employee.getEmployeeId() == employeeId; }));
}

std::vector<Employee> Database::findEmployee(std::string name, std::string firstName)
{
  return std::vector<Employee>();
}

std::vector<Employee> Database::employmentAnniversary(unsigned int yearsOfEmployment)
{
  return std::vector<Employee>();
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
