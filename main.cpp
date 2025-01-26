#include <iostream>
#include <algorithm>
#include "database.hpp"

// instantiate DB class
// creating this on the stack and in the global scope since the DB will be used during the entire runtime
Database db = Database();

void handleEmployeeEdit(unsigned int employeeId, unsigned int editAction)
{
  switch (editAction)
  {
  case 1:
  {
    // increase salary
    std::cout << "Faktor für Gehaltserhöhung (z. B. 1.2 = +20%): ";
    float factor;
    std::cin >> factor;

    if (db.isEmployeeIdValid(employeeId))
    {
      db.increaseSalary(employeeId, factor);
      std::cout << "Gehalt erfolgreich erhöht" << std::endl;
    }
    break;
  }

  case 2:
  {
    // increase years of employment
    db.increaseYearsOfEmployment(employeeId);
    int employeeIndex = db.getEmployeeIndexById(employeeId);
    if (employeeIndex == -1)
    {
      break;
    }
    Employee employee = db.getEmployeeByIndex(employeeIndex);
    unsigned int yearsOfEmployment = employee.getYearsOfEmployment();
    std::cout << "Jahre der Betriebszugehörigkeit erfolgreich auf " << yearsOfEmployment << " erhöht" << std::endl;
    break;
  }

  case 3:
  {
    // remove employment
    if (db.isEmployeeIdValid(employeeId))
    {
      db.removeEmployee(employeeId);
      std::cout << "Mitarbeiter*in erfolgreich entfernt" << std::endl;
    }
    break;
  }
  }
}

void handleEmployeeSearch(unsigned int findAction)
{
  switch (findAction)
  {
  case 1:
  {
    // by name
    std::cout << "Vorname: ";
    std::string firstName;
    std::cin >> firstName;

    std::cout << "Nachname: ";
    std::string name;
    std::cin >> name;

    std::vector<unsigned int> employeeIds = db.findEmployee(name, firstName);

    std::cout << "Folgende Mitarbeiternummern sind mit dem Namen " << firstName << " " << name << " assoziiert:" << std::endl;
    for (unsigned int &employeeId : employeeIds)
    {
      std::cout << employeeId << std::endl;
    }
    break;
  }

  case 2:
  {
    // by years of employment
    std::cout << "Jahre der Betriebszugehörigkeit: ";
    unsigned int yearsOfEmployment;
    std::cin >> yearsOfEmployment;

    std::vector<unsigned int> employeeIds = db.employmentAnniversary(yearsOfEmployment);

    std::cout << "Folgende Mitarbeiternummern haben " << yearsOfEmployment << "-jähriges Jubiläum:" << std::endl;
    for (unsigned int &employeeId : employeeIds)
    {
      std::cout << employeeId << std::endl;
    }

    break;
  }
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
    // view db formatted as key/value pairs in the console
    db.viewDB();
    break;

  case 2:
  {
    // add employee
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

    unsigned int employeeId = db.addEmployee(name, firstName, postalCode, salary);

    std::cout << "Nutzer " << firstName << " " << name << " mit der Mitarbeiternummer " << employeeId << " erfolgreich hinzugefügt" << std::endl;
    break;
  }

  case 3:
  {
    // edit employee
    std::cout << "Zu bearbeitende Mitarbeiternummer: ";
    unsigned int employeeIdToEdit;
    std::cin >> employeeIdToEdit;
    std::cout << std::endl;

    std::cout << "[1] Gehalt erhöhen" << std::endl;
    std::cout << "[2] Jahre der Betriebszugehörigkeit erhöhen" << std::endl;
    std::cout << "[3] Mitarbeiter*in entfernen" << std::endl;
    std::cout << "Gewählte Option: ";

    unsigned int editAction;
    std::cin >> editAction;

    handleEmployeeEdit(employeeIdToEdit, editAction);
    break;
  }

  case 4:
    // find employee
    std::cout << "Mitarbeiter*in finden" << std::endl;
    std::cout << "[1] mit Name" << std::endl;
    std::cout << "[2] mit Jahren der Betriebszugehörigkeit" << std::endl;
    std::cout << "Gewählte Option: ";

    unsigned int findAction;
    std::cin >> findAction;

    handleEmployeeSearch(findAction);
    break;
  }
}

int main()
{
  const std::string filePath = "db.csv";

  // read file
  db.readFile(filePath);

  // restart dialogue after an action has been completed to prevent program restart requirement for further actions
  while (true)
  {
    getUserAction();
    db.saveFile(filePath);
    std::cout << std::endl;
    // TODO: add a way to exit program
    // return a number from getUserAction(), decide on that number whether to exit or continue loop
  }
}
