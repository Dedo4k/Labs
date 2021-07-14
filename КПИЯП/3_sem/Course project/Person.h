#pragma once
#include <iostream>
#include <iomanip>
#include "MyExc_Vvod.h"
using namespace std;

class Person
{
private:
	string name;												//���
public:
	Person();													//�����������
	Person(string name);										//����������� � �����������
	~Person();													//����������
	void setName(string name);									//������� ���������� �������� � ���� (name)
	string getName();											//������� ��������� �������� �� ���� (name)
	friend istream& operator>>(istream& in, Person& person);
	friend ostream& operator<<(ostream& out, const Person& person);
};
