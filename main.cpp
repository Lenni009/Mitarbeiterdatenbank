#include <iostream>
#include <algorithm>
#include "database.hpp"

// instantiate DB class
// creating this on the stack and in the global scope since the DB will be used during the entire runtime
Database db = Database();

void handleEmployeeEdit(unsigned int employeeId, unsigned int editAction)
{
  const int index = db.getEmployeeIndexById(employeeId);

  if (index == -1)
  {
    return;
  }

  Employee employee = db.getEmployeeByIndex(index);

  switch (editAction)
  {
  case 1:
    // increase salary
    std::cout << "Faktor für Gehaltserhöhung (z. B. 1.2 = +20%): ";
    float factor;
    std::cin >> factor;

    employee.increaseSalary(factor);
    break;

  case 2:
    // increase years of employment
    employee.increaseYearsOfEmployment();
    break;

  case 3:
    // remove employment
    db.removeEmployee(employeeId);
    break;
  }
}

void getUserAction()
{

  // get user action
  std::cout << "[1] Datenbank ansehen" << std::endl;
  std::cout << "[2] Mitarbeiter*in hinzufügen" << std::endl;
  std::cout << "[3] Mitarbeiter*in bearbeiten" << std::endl;
  std::cout << "[4] Mitarbeiter*in suchen" << std::endl;
  std::cout << "Gewählte Option: ";

  unsigned int action;
  std::cin >> action;
  std::cout << std::endl;

  switch (action)
  {
  case 1:
    db.viewDB();
    break;

  case 2:
  {
    std::cout << "Vorname: ";
    std::string firstName;
    std::cin >> firstName;

    std::cout << "Nachname: ";
    std::string name;
    std::cin >> name;

    std::cout << "PLZ: ";
    std::string postalCode;
    std::cin >> postalCode;

    std::cout << "Gehalt: ";
    float salary;
    std::cin >> salary;

    // should always be 0 for new employees, but it's good having the option to specify this datapoint for initial db population
    std::cout << "Jahre der Betriebszugehörigkeit: ";
    unsigned int yearsOfEmployment;
    std::cin >> yearsOfEmployment;

    unsigned int employeeId = db.getNewEmployeeId();

    Employee *employee = new Employee(employeeId, name, firstName, postalCode, salary, yearsOfEmployment);
    db.addEmployee(*employee);

    std::cout << "Nutzer " << firstName << " " << name << " mit der Mitarbeiternummer " << employeeId << " erfolgreich hinzugefügt" << std::endl;
    break;
  }

  case 3:
  {
    std::cout << "Zu bearbeitende Mitarbeiternummer: ";
    unsigned int employeeIdToEdit;
    std::cin >> employeeIdToEdit;
    std::cout << std::endl;

    std::cout << "[1] Gehalt erhöhen";
    std::cout << "[2] Jahre der Betriebszugehörigkeit erhöhen";
    std::cout << "[3] Mitarbeiter*in entfernen";
    std::cout << "Gewählte Option: ";

    unsigned int editAction;
    std::cin >> editAction;

    handleEmployeeEdit(employeeIdToEdit, editAction);
    break;
  }

  case 4:

    break;
  }
}

int main()
{
  // read file
  db.readFile("db.csv");

  // restart dialogue after an action has been completed to prevent program restart requirement for further actions
  while (true)
  {
    getUserAction();
    std::cout << std::endl;
  }
}
