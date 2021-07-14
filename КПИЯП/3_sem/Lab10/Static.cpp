#include "Static.h"
#include "MyExc_Vvod.h"

Static::Static()
{
	//cout << "Static constructor" << endl;
	proc = '\0';
	procModel = 0;
	voltage = 0;
}

Static::~Static()
{
	//cout << "Static destructor" << endl;
}

void Static::setProc(string proc)
{
	this->proc = proc;
}

string Static::getProc()
{
	return proc;
}

void Static::setProcModel(int procModel)
{
	this->procModel = procModel;
}

int Static::getProcModel()
{
	return procModel;
}

void Static::setVoltage(int voltage)
{
	this->voltage = voltage;
}

int Static::getVoltage()
{
	return voltage;
}

istream& operator>>(istream& in, Static& stat)
{
	in >> *(dynamic_cast<Computer*>(&stat));
	cout << "Enter procesor: ";
	stat.proc = MyExc_Vvod::Check_string(10);
	cout << "Enter procesor model: ";
	stat.procModel = MyExc_Vvod::Check_int();
	cout << "Enter voltage: ";
	stat.voltage = MyExc_Vvod::Check_int();
	return in;
}

ostream& operator<<(ostream& out, Static& stat)
{
	Computer* computer;
	computer = &stat;
	out << *(dynamic_cast<Computer*>(computer));
	out << "|" << setw(10) << stat.proc << "|"<< setw(13) << stat.procModel << "|"<< setw(9) << stat.voltage;
	return out;
}

fstream& operator>>(fstream& in, Static& stat)
{
	in >> *(dynamic_cast<Computer*>(&stat));
	in >> stat.proc;
	in >> stat.procModel;
	in >> stat.voltage;
	return in;
}

fstream& operator<<(fstream& out, Static& stat)
{
	out << *(dynamic_cast<Computer*>(&stat));
	out << stat.proc << "\n";
	out << stat.procModel << "\n";
	out << stat.voltage << "\n";
	return out;
}

ifstream& operator>>(ifstream& in, Static& stat)
{
	in >> *(dynamic_cast<Computer*>(&stat));
	in >> stat.proc;
	in >> stat.procModel;
	in >> stat.voltage;
	return in;
}

ofstream& operator<<(ofstream& out, Static& stat)
{
	out << *(dynamic_cast<Computer*>(&stat));
	out << stat.proc << "\n";
	out << stat.procModel << "\n";
	out << stat.voltage << "\n";
	return out;
}
