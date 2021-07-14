#include "Employee.h"

Employee::Employee()
{
	this->surname = "";
}

Employee::Employee(string surname)
{
	this->surname = surname;
}

Employee::~Employee()
{
}

void Employee::setSurname(string surname)
{
	this->surname = surname;
}

string Employee::getSurname()
{
	return surname;
}

istream& operator>>(istream& in, Employee& employee)
{
	in >> *(dynamic_cast<Person*>(&employee));
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t¬ведите фамилию:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	employee.surname = MyExc_Vvod::Check_string(12);
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, Employee& employee)
{
	out << *(dynamic_cast<Person*>(&employee));
	out << setw(12) << employee.surname << "|";
	return out;
}
