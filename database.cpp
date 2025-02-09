#include <string>
#include <iostream>
#include <fstream>   // for ifstream
#include <sstream>   // for stringstream
#include <algorithm> // for find_if
#include <vector>
#include <memory> // for unique_ptr
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
    int yearsOfEmployment = std::stoi(args.at(4));
    addEmployee(args.at(0), args.at(1), args.at(2), salary, yearsOfEmployment);
  }
}

void Database::saveFile(std::string path)
{
  std::string outputText;

  for (Employee &employee : db)
  {
    outputText += employee.getEmployeeData();
    outputText += "\n\n"; // adding empty line between entries (task requirement)
  }

  // https://www.w3schools.com/cpp/cpp_files.asp
  // open text file (create it if it doesn't exist yet)
  std::ofstream dbFile(path);

  // write to the file
  dbFile << outputText;

  dbFile.close();
}

// employee add/remove
// the task dictates the following: `int mitarbeiternummer = datenbank.neuerMitarbeiter ( name , vorname , plz , gehalt );`
// due to the architecture of the program, this method is also used during initial DB creation from file.
// therefore this method also takes the yearsOfEmployment, despite what the task requires.
// I wouldn't return anything from this function, but the task requires this to return the employee id.

int Database::addEmployee(std::string name, std::string firstName, std::string postalCode, float salary, int yearsOfEmployment)
{
  int employeeId = getNewEmployeeId();

  // using unique_ptr to automatically allocate/free memory when object is created/goes out of scope
  std::unique_ptr<Employee> employee = std::make_unique<Employee>(employeeId, name, firstName, postalCode, salary, yearsOfEmployment);

  db.push_back(*employee);
  return employeeId;
}

void Database::removeEmployee(int employeeId)
{
  const int employeeIndex = getEmployeeIndexById(employeeId);

  if (employeeIndex != -1)
  {
    // https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
    db.erase(db.begin() + employeeIndex);
  }
}

// Since a function in C++ can only have one return type (as far as I know), I cannot declare a method that *might* return an employee, or might return void.
// I am aware of function overloading, but in this case we do not know the return type based on the function args.
// So the alternative is to return an int and then check whether that int has an expected value.

int Database::getEmployeeIndexById(int employeeId)
{
  // find element where Employee.employeeId == employeeId
  // returns an iterator
  const auto it = std::find_if(db.begin(), db.end(), [&employeeId](Employee &employee)
                               { return employee.getEmployeeId() == employeeId; });
  if (it != db.end())
  {
    long index = it - db.begin();
    return static_cast<int>(index);
  }
  else
  {
    std::cerr << "Ungültige Mitarbeiternummer!" << std::endl;
    return -1;
  }
}

Employee &Database::getEmployeeByIndex(int index)
{
  size_t indexAsSizeT = static_cast<size_t>(index); // this is here because otherwise the compiler gives a warning
  return db.at(indexAsSizeT);
}

int Database::getNewEmployeeId()
{
  if (db.size())
  {
    // there is no scenario that I can think of where the last item in the DB doesn't have the highest ID
    return db.back().getEmployeeId() + 1;
  }
  else
  {
    return 0;
  }
}

std::vector<int> Database::findEmployeesByName(std::string name, std::string firstName)
{
  std::vector<int> filterResults;
  for (Employee &employee : db)
  {
    if (employee.getEmployeeName() == name && employee.getEmployeeFirstName() == firstName)
    {
      filterResults.push_back(employee.getEmployeeId());
    }
  }
  return filterResults;
}

std::vector<int> Database::findEmployeesByYearsOfEmployment(int yearsOfEmployment)
{
  std::vector<int> filterResults;
  for (Employee &employee : db)
  {
    if (employee.getYearsOfEmployment() == yearsOfEmployment)
    {
      filterResults.push_back(employee.getEmployeeId());
    }
  }
  return filterResults;
}

// get output of DB data

void Database::viewDB()
{
  // access by reference to avoid copying
  for (Employee &employee : db)
  {
    employee.outputDataToConsole();
    std::cout << std::endl;
  }
}

// This is just a fancy wrapper around the employee class' own method, but it is required by the task that this method exists on the DB.
// I would just use these methods on the employee objects directly, but the task requires this to be on the db object

void Database::adjustSalary(int employeeId, float factor)
{
  int employeeIndex = getEmployeeIndexById(employeeId);
  // -1 = invalid index -> ID doesn't exist
  if (employeeIndex != -1)
  {
    int employeeIndexInteger = static_cast<int>(employeeIndex);
    Employee &employee = getEmployeeByIndex(employeeIndexInteger);
    employee.adjustSalary(factor);
  }
}

// The task requires this method to be on the DB object as well

void Database::increaseYearsOfEmployment(int employeeId)
{
  // The code here is pretty much similar to the above method, but I'm lacking the knowledge to make this generic.
  // I would need to add a callback function as a method parameter which would then be executed in the `if` statement
  int employeeIndex = getEmployeeIndexById(employeeId);
  // -1 = invalid index -> ID doesn't exist
  if (employeeIndex != -1)
  {
    int employeeIndexInteger = static_cast<int>(employeeIndex);
    Employee &employee = getEmployeeByIndex(employeeIndexInteger);
    employee.increaseYearsOfEmployment();
  }
}

// input validation

bool Database::isEmployeeIdValid(int employeeId)
{
  return getEmployeeIndexById(employeeId) != -1;
}
