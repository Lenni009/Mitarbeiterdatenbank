#include <iostream>
#include <algorithm>
#include <limits>
#include <memory>
// include cpp files so they are automatically included in the final bundle
#include "employee.cpp"
#include "database.cpp"

// instantiate DB class
std::unique_ptr<Database> db = std::make_unique<Database>();

/// @brief Shows an error about the given option being invalid and handles the console's error state to prevent infinite loops
void showInvalidOptionError()
{
  std::cerr << "Ungültige Option" << std::endl;

  // the following is to prevent an infinite loop on invalid input
  // clear error flags
  std::cin.clear();

  // ignore the rest of the line (discard the bad input)
  // use std::numeric_limits<std::streamsize>::max() to ensure everything until a newline is ignored
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/// @brief Handles the UI for editing an employee
/// @param employeeId ID of the employee to edit
/// @param editAction Number of the action to perform on the employee object. Expected to be one of 1,2,3
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

    if (factor <= 0)
    {
      std::cerr << "Faktor darf nicht 0 oder negativ sein!" << std::endl;
      break;
    }

    if (db->isEmployeeIdValid(employeeId))
    {
      db->adjustSalary(employeeId, factor);
      std::cout << "Gehalt erfolgreich erhöht" << std::endl;
    }
    break;
  }

  case 2:
  {
    // increase years of employment
    db->increaseYearsOfEmployment(employeeId);
    int employeeIndex = db->getEmployeeIndexById(employeeId);
    if (employeeIndex == -1)
    {
      break;
    }
    Employee &employee = db->getEmployeeByIndex(employeeIndex);
    unsigned int yearsOfEmployment = employee.getYearsOfEmployment();
    std::cout << "Jahre der Betriebszugehörigkeit erfolgreich auf " << yearsOfEmployment << " erhöht" << std::endl;
    break;
  }

  case 3:
  {
    // remove employment
    if (db->isEmployeeIdValid(employeeId))
    {
      db->removeEmployee(employeeId);
      std::cout << "Mitarbeiter*in erfolgreich entfernt" << std::endl;
    }
    break;
  }

  default:
    showInvalidOptionError();
  }
}

/// @brief Handles the search options UI
/// @param findAction number of the action to be executed. Expected to be 1 or 2.
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

    std::vector<unsigned int> employeeIds = db->findEmployeesByName(name, firstName);

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
    int yearsOfEmployment;
    std::cin >> yearsOfEmployment;
    unsigned int absYearsOfEmployment = std::abs(yearsOfEmployment);

    std::vector<unsigned int> employeeIds = db->findEmployeesByYearsOfEmployment(absYearsOfEmployment);

    std::cout << "Folgende Mitarbeiternummern haben " << absYearsOfEmployment << "-jähriges Jubiläum:" << std::endl;
    for (unsigned int &employeeId : employeeIds)
    {
      std::cout << employeeId << std::endl;
    }

    break;
  }

  default:
    showInvalidOptionError();
  }
}

/// @brief
/// Handles main user interaction for the program.
/// I am aware that the return type and function parameter do not fit the function name at all.
/// However, I need a way of communicating data between main() and this function.
/// @param filePath path to the file that the DB file should be saved to
/// @return whether the program should exit
bool getUserAction(std::string filePath)
{
  // get user action
  std::cout << "[1] Datenbank ansehen" << std::endl;
  std::cout << "[2] Mitarbeiter*in hinzufügen" << std::endl;
  std::cout << "[3] Mitarbeiter*in bearbeiten" << std::endl;
  std::cout << "[4] Mitarbeiter*in suchen" << std::endl;
  std::cout << "[5] Programm beenden" << std::endl;
  std::cout << "Gewählte Option: ";

  unsigned int action;
  std::cin >> action;

  std::cout << std::endl;

  switch (action)
  {
  case 1:
    // view db formatted as key/value pairs in the console
    db->viewDB();
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
    // limiting to 5 digits since German postal codes only have 5 digits (and this is a German program): https://de.wikipedia.org/wiki/Postleitzahl_(Deutschland)
    std::string limitedPostalCode = postalCode.substr(0, 5);

    std::cout << "Gehalt: ";
    float salary;
    std::cin >> salary;
    float validatedSalary = std::max(std::abs(salary), float(1));

    unsigned int employeeId = db->addEmployee(name, firstName, limitedPostalCode, validatedSalary, 0);

    std::cout << "Mitarbeiter*in " << firstName << " " << name << " mit der Mitarbeiternummer " << employeeId << " erfolgreich hinzugefügt" << std::endl;
    db->saveFile(filePath);
    break;
  }

  case 3:
  {
    // edit employee
    std::cout << "Zu bearbeitende Mitarbeiternummer: ";
    unsigned int employeeIdToEdit;
    std::cin >> employeeIdToEdit;
    std::cout << std::endl;

    // input validation
    bool isValid = db->isEmployeeIdValid(employeeIdToEdit);
    if (!isValid)
    {
      break;
    }

    std::cout << "[1] Gehalt erhöhen" << std::endl;
    std::cout << "[2] Jahre der Betriebszugehörigkeit erhöhen" << std::endl;
    std::cout << "[3] Mitarbeiter*in entfernen" << std::endl;
    std::cout << "Gewählte Option: ";

    unsigned int editAction;
    std::cin >> editAction;

    std::cout << std::endl;

    handleEmployeeEdit(employeeIdToEdit, editAction);
    db->saveFile(filePath);
    break;
  }

  case 4:
  {
    // find employee
    std::cout << "Mitarbeiter*in suchen" << std::endl;
    std::cout << "[1] mit Name" << std::endl;
    std::cout << "[2] mit Jahren der Betriebszugehörigkeit" << std::endl;
    std::cout << "Gewählte Option: ";

    unsigned int findAction;
    std::cin >> findAction;

    std::cout << std::endl;

    handleEmployeeSearch(findAction);
    db->saveFile(filePath);
    break;
  }

  case 5:
    // exit
    return true;

  default:
    showInvalidOptionError();
  }

  // continue
  return false;
}

int main()
{
  const std::string filePath = "db.csv";

  // read file
  try
  {
    db->readFile(filePath);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Datenbankdatei (db.csv) konnte nicht gelesen werden!" << "\n"
              << "Existierende Datei wird bei Bearbeitungen überschrieben!" << std::endl;
  }

  // restart dialogue after an action has been completed to prevent program restart requirement for further actions
  while (true)
  {
    // true = exit; false = continue
    bool exit = getUserAction(filePath);

    // exit program if user has chosen so
    if (exit)
    {
      return 0;
    }

    std::cout << std::endl;
  }
}
