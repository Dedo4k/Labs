#include "Monoblock.h"

Monoblock::Monoblock()
{
	cout << "Monoblock constructor" << endl << endl;
	memCap = 0;
}

Monoblock::~Monoblock()
{
	cout << endl << "Monoblock destructor" << endl;
}

void Monoblock::setMemCap(int memCap)
{
	this->memCap = memCap;
}

int Monoblock::getMemCap()
{
	return memCap;
}

istream& operator>>(istream& in, Monoblock& monoblock)
{
	Static* stat;
	stat = &monoblock;
	in >> *(dynamic_cast<Static*>(stat));
	cout << "Enter memory capacity - ";
	in >> monoblock.memCap;
	return in;
}

ostream& operator<<(ostream& out, Monoblock& monoblock)
{
	Static* stat;
	stat = &monoblock;
	out << *(dynamic_cast<Static*>(stat));
	out << "Memory capacity: " << monoblock.memCap << endl;
	return out;
}