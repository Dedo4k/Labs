#pragma once
#include "Transport.h"

class Truck : public Transport
{
private:
	string type;
public:
	Truck();						//конструктор
	Truck(string type);				//конструктор с параметром
	~Truck();						//деструктор
	void setType(string type);		//функция добавления значения в поле (type)
	string getType();				//функция получения значения из поля (type)
	friend istream& operator>>(istream& in, Truck& truck);
	friend ostream& operator<<(ostream& out, Truck& truck);
};
