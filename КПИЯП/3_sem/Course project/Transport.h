#pragma once
#include <iostream>
#include <iomanip>
#include "MyExc_Vvod.h"
using namespace std;

class Transport
{
private:
	int number;						//номер транспортного средства
public:
	Transport();					//конструктор
	~Transport();					//деструктор
	void setNumber(int number);		//функция для добавления значения в поле (number)
	int getNumber();				//функция получения значения из поля (number)
	friend istream& operator>>(istream& in, Transport& transport);
	friend ostream& operator<<(ostream& out, const Transport& transport);
};