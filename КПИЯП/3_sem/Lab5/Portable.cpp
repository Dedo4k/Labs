#include "Portable.h"

Portable::Portable()
{
	cout << "Portable constructor" << endl;
	battery = 0;
}

Portable::~Portable()
{
	cout << "Portable destructor" << endl;
}

void Portable::setBattery(int battery)
{
	this->battery = battery;
}

int Portable::getBattery()
{
	return battery;
}

istream& operator>>(istream& in, Portable& portable)
{
	Computer* computer;
	computer = &portable;
	in >> *(dynamic_cast<Computer*>(computer));
	cout << "Enter battery - ";
	in >> portable.battery;
	return in;
}

ostream& operator<<(ostream& out, Portable& portable)
{
	Computer* computer;
	computer = &portable;
	out << *(dynamic_cast<Computer*>(computer));
	out << "Battery: " << portable.battery << endl;
	return out;
}