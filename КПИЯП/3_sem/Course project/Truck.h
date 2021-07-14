#pragma once
#include "Transport.h"

class Truck : public Transport
{
private:
	string type;
public:
	Truck();						//�����������
	Truck(string type);				//����������� � ����������
	~Truck();						//����������
	void setType(string type);		//������� ���������� �������� � ���� (type)
	string getType();				//������� ��������� �������� �� ���� (type)
	friend istream& operator>>(istream& in, Truck& truck);
	friend ostream& operator<<(ostream& out, Truck& truck);
};
