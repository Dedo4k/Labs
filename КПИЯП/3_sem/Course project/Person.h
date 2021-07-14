#pragma once
#include <iostream>
#include <iomanip>
#include "MyExc_Vvod.h"
using namespace std;

class Person
{
private:
	string name;												//имя
public:
	Person();													//конструктор
	Person(string name);										//конструктор с параметрами
	~Person();													//деструктор
	void setName(string name);									//функция добавления значения в поле (name)
	string getName();											//функция получения значения из поля (name)
	friend istream& operator>>(istream& in, Person& person);
	friend ostream& operator<<(ostream& out, const Person& person);
};
