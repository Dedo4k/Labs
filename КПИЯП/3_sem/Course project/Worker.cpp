#include "Worker.h"

istream& operator>>(istream& in, Worker& worker)
{
	in >> *(dynamic_cast<Employee*>(&worker));
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите должность: " << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	worker.position = MyExc_Vvod::Check_string(12);
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите зарплату: " << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	worker.salary = MyExc_Vvod::Check_double(0.99);
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, Worker& worker)
{
	out << *(dynamic_cast<Employee*>(&worker));
	out << setw(12) << worker.position << "|" << setw(12) << worker.salary << "|" << endl;
	return out;
}

Worker::Worker()
{
	this->position = "";
	this->salary = 0.0;
}

Worker::Worker(string position, double salary)
{
	this->position = position;
	this->salary = salary;
}

Worker::~Worker()
{
}

void Worker::shapka()
{
	cout << "\t\t\t\t\t\t\t\t\t\t|" << setw(12) << "Имя    " << "|" << setw(12) << "Фамилия  " << "|" << setw(12) << "Должность " << "|" << setw(12) << "Зарплата   " << "|" << endl;
}

void Worker::setPosition(string position)
{
	this->position = position;
}

void Worker::setSalary(double salary)
{
	this->salary = salary;
}

string Worker::getPosition()
{
	return position;
}

double Worker::getSalary()
{
	return salary;
}
