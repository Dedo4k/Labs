#pragma once
#include "Employee.h"

class Worker : public Employee
{
private:
	string position;											//���������
	double salary;												//���������� �����
public:
	Worker();
	Worker(string position, double salary);
	~Worker();
	void shapka();
	void setPosition(string position);							//������� ���������� �������� � ���� (position)
	void setSalary(double salary);								//������� ���������� �������� � ���� (salary)
	string getPosition();										//������� ��������� �������� �� ���� (position)
	double getSalary();											//������� ��������� �������� �� ���� (salary)
	friend istream& operator>>(istream& in, Worker& worker);
	friend ostream& operator<<(ostream& out, Worker& worker);
};

