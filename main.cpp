#include <iostream>
#include <limits> // for numeric_limits
#include <memory> // for unique_ptr
// include cpp files so they are automatically included in the final bundle
#include "employee.cpp"
#include "database.cpp"

static std::unique_ptr<Database> db = std::make_unique<Database>();

/// @brief Prevents an infinite loop on invalid input
void resetCin();
void resetCin()
{
  // clear error flags
  std::cin.clear();

  // ignore everything until a newline
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/// @brief Shows an error about the given option being invalid and handles the console's error state to prevent infinite loops
void showInvalidOptionError();
void showInvalidOptionError()
{
  std::cerr << "Ungültige Option" << std::endl;

  resetCin();
}

/// @brief Handles the UI for editing an employee
/// @param employeeId ID of the employee to edit
/// @param editAction Number of the action to perform on the employee object. Expected to be one of 1,2,3
void handleEmployeeEdit(int employeeId, int editAction);
void handleEmployeeEdit(int employeeId, int editAction)
{
  switch (editAction)
  {
  case 1:
  {
    // increase salary
    std::cout << "Faktor für Gehaltserhöhung (z. B. 1.2 = +20%): ";
    float factor;
    std::cin >> factor;

    if (factor <= 0 || std::cin.fail())
    {
      std::cerr << "Faktor darf nicht 0 oder negativ sein!" << std::endl;
      resetCin();
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
    int yearsOfEmployment = employee.getYearsOfEmployment();
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
/// @param findAction Number of the action to be executed. Expected to be 1 or 2.
void handleEmployeeSearch(int findAction);
void handleEmployeeSearch(int findAction)
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

    std::vector<int> employeeIds = db->findEmployeesByName(name, firstName);

    std::cout << "Folgende Mitarbeiternummern sind mit dem Namen " << firstName << " " << name << " assoziiert:" << std::endl;
    for (int &employeeId : employeeIds)
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
    int absYearsOfEmployment = std::abs(yearsOfEmployment);

    std::vector<int> employeeIds = db->findEmployeesByYearsOfEmployment(absYearsOfEmployment);

    std::cout << "Folgende Mitarbeiternummern haben " << absYearsOfEmployment << "-jähriges Jubiläum:" << std::endl;
    for (int &employeeId : employeeIds)
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
bool getUserAction(std::string filePath);
bool getUserAction(std::string filePath)
{
  // get user action
  std::cout << "[1] Datenbank ansehen" << std::endl;
  std::cout << "[2] Mitarbeiter*in hinzufügen" << std::endl;
  std::cout << "[3] Mitarbeiter*in bearbeiten" << std::endl;
  std::cout << "[4] Mitarbeiter*in suchen" << std::endl;
  std::cout << "[5] Programm beenden" << std::endl;
  std::cout << "Gewählte Option: ";

  int action;
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

    if (std::cin.fail())
    {
      std::cerr << "Gehalt muss Zahl sein! Vorgang wird abgebrochen." << std::endl;
      resetCin();
      break;
    }

    int employeeId = db->addEmployee(name, firstName, limitedPostalCode, validatedSalary, 0);

    std::cout << "Mitarbeiter*in " << firstName << " " << name << " mit der Mitarbeiternummer " << employeeId << " erfolgreich hinzugefügt" << std::endl;
    db->saveFile(filePath);
    break;
  }

  case 3:
  {
    // edit employee
    std::cout << "Zu bearbeitende Mitarbeiternummer: ";
    int employeeIdToEdit;
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

    int editAction;
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

    int findAction;
    std::cin >> findAction;

    std::cout << std::endl;

    handleEmployeeSearch(findAction);
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
  catch (const std::exception &)
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
