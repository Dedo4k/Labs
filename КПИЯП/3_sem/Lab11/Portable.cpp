#include "Portable.h"
#include "MyExc_Vvod.h"

Portable::Portable()
{
	//cout << "Portable constructor" << endl;
	battery = 0;
}

Portable::~Portable()
{
	//cout << "Portable destructor" << endl;
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
	cout << "Enter battery: ";
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

fstream& operator>>(fstream& in, Portable& portable)
{
	in >> *(dynamic_cast<Computer*>(&portable));
	in >> portable.battery;
	return in;
}

fstream& operator<<(fstream& out, Portable& portable)
{
	out << *(dynamic_cast<Computer*>(&portable));
	out << portable.battery << "\n";
	return out;
}

ifstream& operator>>(ifstream& in, Portable& portable)
{
	in >> *(dynamic_cast<Computer*>(&portable));
	in >> portable.battery;
	return in;
}

ofstream& operator<<(ofstream& out, Portable& portable)
{
	out << *(dynamic_cast<Computer*>(&portable));
	out << portable.battery << "\n";
	return out;
}
