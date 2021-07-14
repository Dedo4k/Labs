#include "Car.h"

Car::Car()
{
	type = "car";
	//cout << endl << "Car constructor" << endl;
}

Car::Car(string type)
{
	this->type = type;
	//cout << endl << "Car constructor with parameter" << endl;
}

Car::~Car()
{
	//cout << endl << "Car destructor" << endl;
}

void Car::setType(string type)
{
	this->type = type;
}

string Car::getType()
{
	return type;
}

istream& operator>>(istream& in, Car& car)
{
	in >> *(dynamic_cast<Transport*>(&car));
	return in;
}

ostream& operator<<(ostream& out, Car& car)
{
	out << *(dynamic_cast<Transport*>(&car));
	out << "|" << setw(12) << car.type;
	return out;
}
