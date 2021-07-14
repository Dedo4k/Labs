#include "Truck.h"

Truck::Truck()
{
	type = "truck";
	//cout << endl << "Truck constructor" << endl;
}

Truck::Truck(string type)
{
	this->type = type;
	//cout << endl << "Truck constructor with parameter" << endl;
}

Truck::~Truck()
{
	//cout << endl << "Truck destructor" << endl;
}

void Truck::setType(string type)
{
	this->type = type;
}

string Truck::getType()
{
	return type;
}

istream& operator>>(istream& in, Truck& truck)
{
	in >> *(dynamic_cast<Transport*>(&truck));
	return in;
}

ostream& operator<<(ostream& out, Truck& truck)
{
	out << *(dynamic_cast<Transport*>(&truck));
	out << "|" << setw(12) << truck.type;
	return out;
}
