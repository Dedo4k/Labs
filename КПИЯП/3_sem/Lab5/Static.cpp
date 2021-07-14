#include "Static.h"

Static::Static()
{
	cout << "Static constructor" << endl;
	proc = '\0';
	procModel = 0;
	voltage = 0;
}

Static::~Static()
{
	cout << "Static destructor" << endl;
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
	Computer* computer;
	computer = &stat;
	in >> *(dynamic_cast<Computer*>(computer));
	cout << "Enter procesor - ";
	in >> stat.proc;
	cout << "Enter procesor model - ";
	in >> stat.procModel;
	cout << "Enter voltage - ";
	in >> stat.voltage;
	return in;
}

ostream& operator<<(ostream& out, Static& stat)
{
	Computer* computer;
	computer = &stat;
	out << *(dynamic_cast<Computer*>(computer));
	out << "Proc: " << stat.proc << "|"<< "Proc Model: " << stat.procModel << "|"<< "Voltage: " << stat.voltage << "|";
	return out;
}