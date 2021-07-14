#include "Computer.h"

Computer::Computer()
{
	cout << endl << "computer constructor" << endl;
	brand = '\0';
}

Computer::~Computer()
{
	cout << "Computer destructor" << endl;
}

void Computer::setBrand(string brand)
{
	this->brand = brand;
}

string Computer::getBrand()
{
	return brand;
}

istream& operator>>(istream& in, Computer& computer)
{
	cout << "Enter brand - ";
	in >> computer.brand;
	return in;
}

ostream& operator<<(ostream& out, const Computer& computer)
{
	out << endl << "Brand: " << computer.brand << "|";
	return out;
}