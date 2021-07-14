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
	return this->getBrand() == monoblock.getBrand() && this->getProc() == monoblock.getProc() && this->getProcModel() == monoblock.getProcModel() && this->getMemCap() == monoblock.getMemCap() && this->getVoltage() == monoblock.getVoltage();
}

bool Monoblock::operator>(Monoblock monoblock)
{
	if(this->getBrand()>monoblock.getBrand())
		return true;
}

//bool Monoblock::operator<(Monoblock monoblock)
//{
//	if (this->getBrand() < monoblock.getBrand())
//		return true;
//}

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

fstream& operator>>(fstream& in, Monoblock& monoblock)
{
	size_t length;
	char* buf;
	
	in.read((char*)&length, sizeof(size_t));
	buf = new char[length + 1];
	in.read(buf,length);
	buf[length] = 0;
	monoblock.brand = buf;
	delete[]buf;

	in.read((char*)&length, sizeof(size_t));
	buf = new char[length + 1];
	in.read(buf, length);
	buf[length] = 0;
	monoblock.proc = buf;
	delete[]buf;

	in.read((char*)&monoblock.procModel, sizeof(int));
	in.read((char*)&monoblock.voltage, sizeof(int));
	in.read((char*)&monoblock.memCap, sizeof(int));
	return  in;
}

fstream& operator<<(fstream& out, Monoblock& monoblock)
{
	size_t length;

	length = monoblock.getBrand().length();
	out.write((char*)&length, sizeof(size_t));
	out.write(monoblock.getBrand().data(), length);
	length = monoblock.getProc().length();
	out.write((char*)&length, sizeof(size_t));
	out.write(monoblock.getProc().data(), length);
	out.write(reinterpret_cast<char*>(&monoblock.procModel), sizeof(int));
	out.write(reinterpret_cast<char*>(&monoblock.voltage), sizeof(int));
	out.write(reinterpret_cast<char*>(&monoblock.memCap), sizeof(int));
	return out;
}

ifstream& operator>>(ifstream& in, Monoblock& monoblock)
{
	in >> *(dynamic_cast<Static*>(&monoblock));
	in >> monoblock.memCap;
	return  in;
}

ofstream& operator<<(ofstream& out, Monoblock& monoblock)
{
	out << *(dynamic_cast<Static*>(&monoblock));
	out << monoblock.memCap << "\n";
	return out;
}
