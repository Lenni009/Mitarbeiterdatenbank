#include <iostream>
#include "database.hpp"

int main()
{
  // instantiate DB class
  // creating this on the stack since the DB will be in scope for the entire runtime
  Database db = Database();

  // read file
  db.readFile("./db.csv");

  // get user action
  int action;

  std::cout << "[1] Datenbank ansehen" << std::endl;
  std::cout << "[2] Mitarbeiter*in hinzufügen" << std::endl;
  std::cout << "[3] Mitarbeiter*in bearbeiten" << std::endl;
  std::cout << "[4] Mitarbeiter*in suchen" << std::endl;
  std::cout << "Gewählte Option: ";

  std::cin >> action;

  switch (action)
  {
  case 1:
    db.viewDB();
    break;
  }
}
