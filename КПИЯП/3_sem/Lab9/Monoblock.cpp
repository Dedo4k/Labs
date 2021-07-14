#include "Monoblock.h"
#include "MyExc_Vvod.h"

Monoblock::Monoblock()
{
	//cout << "Monoblock constructor" << endl;
	memCap = 0;
}

Monoblock::~Monoblock()
{
	//cout << endl << "Monoblock destructor" << endl;
}

bool Monoblock::operator==(Monoblock monoblock)
{
	return this->getBrand()==monoblock.getBrand()&&this->getProc()==monoblock.getProc()&&this->getProcModel()==monoblock.getProcModel()&&this->getMemCap()==monoblock.getMemCap()&&this->getVoltage()==monoblock.getVoltage();
}

void Monoblock::shapka()
{
	cout << endl << "|" << setw(7) << "Brand " << "|" << setw(10) << "Procesor " << "|" << setw(13) << "Proc. model " << "|" << setw(9) << "Voltage " << "|" << setw(9) << "Memory " << "|" << endl;
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
	in >> *(dynamic_cast<Static*>(&monoblock));
	cout << "Enter memory capacity: ";
	monoblock.memCap = MyExc_Vvod::Check_int();
	return in;
}

ostream& operator<<(ostream& out, Monoblock& monoblock)
{
	Static* stat;
	stat = &monoblock;
	out << *(dynamic_cast<Static*>(stat));
	out << "|" << setw(9) << monoblock.memCap << "|" << endl;
	return out;
}
