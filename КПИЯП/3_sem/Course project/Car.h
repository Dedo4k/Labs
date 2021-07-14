#pragma once
#include "Transport.h"

class Car : public Transport
{
private:
	string type;					//��� ������������� ��������
public:
	Car();							//�����������
	Car(string type);				//����������� � ����������
	~Car();							//����������
	void setType(string type);		//������� ���������� �������� � ���� (type)
	string getType();				//������� ��������� �������� �� ���� (type)
	friend istream& operator>>(istream& in, Car& car);
	friend ostream& operator<<(ostream& out, Car& car);
};
