#pragma once
#include "Transport.h"

class Car : public Transport
{
private:
	string type;					//тип транспортного средства
public:
	Car();							//конструктор
	Car(string type);				//конструктор с параметром
	~Car();							//деструктор
	void setType(string type);		//функция добавления значения в поле (type)
	string getType();				//функция получения значения из поля (type)
	friend istream& operator>>(istream& in, Car& car);
	friend ostream& operator<<(ostream& out, Car& car);
};
