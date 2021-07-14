#include "Portable.h"
#include "MyExc_Vvod.h"

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
	bool fl;
	Computer* computer;
	computer = &portable;
	in >> *(dynamic_cast<Computer*>(computer));
	cout << endl << "Enter battery - ";
	portable.battery = MyExc_Vvod::Check_int();
	return in;
}

ostream& operator<<(ostream& out, Portable& portable)
{
	Computer* computer;
	computer = &portable;
	out << *(dynamic_cast<Computer*>(computer));
	out << "|" << setw(9) << portable.battery;
	return out;
}