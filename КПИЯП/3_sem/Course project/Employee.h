#pragma once
#include "Person.h"
class Employee :     public Person
{
private:
	string surname;												//�������
public:
	Employee();
	Employee(string surname);
	~Employee();
	void setSurname(string surname);
	string getSurname();
	friend istream& operator>>(istream& in, Employee& employee);
	friend ostream& operator<<(ostream& out, Employee& employee);
};

