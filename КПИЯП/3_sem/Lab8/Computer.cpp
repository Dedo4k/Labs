#include "Computer.h"
#include "MyExc_Vvod.h"

Computer::Computer()
{
	//cout << endl << "computer constructor" << endl;
	brand = '\0';
}

Computer::~Computer()
{
	//cout << "Computer destructor" << endl;
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
	system("CLS");
	cout << "Enter brand: ";
	computer.brand = MyExc_Vvod::Check_string(7);
	return in;
}

ostream& operator<<(ostream& out, const Computer& computer)
{
	out << "|" << setw(7) << computer.brand;
	return out;
}
