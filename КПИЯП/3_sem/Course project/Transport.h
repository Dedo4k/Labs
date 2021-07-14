#pragma once
#include <iostream>
#include <iomanip>
#include "MyExc_Vvod.h"
using namespace std;

class Transport
{
private:
	int number;						//����� ������������� ��������
public:
	Transport();					//�����������
	~Transport();					//����������
	void setNumber(int number);		//������� ��� ���������� �������� � ���� (number)
	int getNumber();				//������� ��������� �������� �� ���� (number)
	friend istream& operator>>(istream& in, Transport& transport);
	friend ostream& operator<<(ostream& out, const Transport& transport);
};