#include "Person.h"

Person::Person()
{
	name = "";
	//cout << endl << "Person constructor" << endl;
}

Person::Person(string name)
{
	this->name = name;
	//cout << endl << "Person constructor with parameters" << endl;
}

Person::~Person()
{
	//cout << endl << "Person destructor" << endl;
}

void Person::setName(string name)
{
	this->name = name;
}

string Person::getName()
{
	return name;
}

istream& operator>>(istream& in, Person& person)
{
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите имя:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	person.name = MyExc_Vvod::Check_string(12);
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, const Person& person)
{
	out << "\t\t\t\t\t\t\t\t\t\t|" << setw(12) << person.name << "|";
	return out;
}
