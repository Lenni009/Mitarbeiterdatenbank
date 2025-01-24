#include <string>
#include <vector>

class Employee
{
private:
  unsigned int employeeId;
  std::string name;
  std::string firstName;
  unsigned int postalCode; // 12345
  float salary;            // no huge decimal needed, saving memory by using float instead of double
  unsigned int yearsOfEmployment;

public:
  Employee(unsigned int employeeId, std::string name, std::string firstName, int postalCode, float salary, int yearsOfEmployment);
  ~Employee();
  void increaseSalary(unsigned int employeeId);
  void increaseYearsOfEmployment(unsigned int employeeId);
  void removeEmployee(unsigned int employeeId);
  std::vector<Employee> findEmployee(std::string name, std::string firstName);
  std::vector<Employee> employmentAnniversary(unsigned int yearsOfEmployment);
};
