#pragma once
#include "Employee.h"

class Worker : public Employee
{
private:
	string position;											//должность
	double salary;												//заработная плата
public:
	Worker();
	Worker(string position, double salary);
	~Worker();
	void shapka();
	void setPosition(string position);							//функция добавления значения в поле (position)
	void setSalary(double salary);								//функция добавления значения в поле (salary)
	string getPosition();										//функция получения значения из поля (position)
	double getSalary();											//функция получения значения из поля (salary)
	friend istream& operator>>(istream& in, Worker& worker);
	friend ostream& operator<<(ostream& out, Worker& worker);
};

