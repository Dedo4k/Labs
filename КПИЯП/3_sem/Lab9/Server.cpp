#include "Server.h"
#include "MyExc_Vvod.h"

Server::Server()
{
	//cout << "Server constructor" << endl << endl;
	memHD = 0;
}

Server::~Server()
{
	//cout << endl << "Server destructor" << endl;
}

bool Server::operator==(Server server)
{
	return this->getBrand() == server.getBrand() && this->getProc() == server.getProc() && this->getProcModel() == server.getProcModel() && this->getMemHD() == server.getMemHD() && this->getVoltage() == server.getVoltage();
}

void Server::shapka()
{
	cout << endl << "|" << setw(7) << "Brand " << "|" << setw(10) << "Procesor " << "|" << setw(13) << "Proc. model " << "|" << setw(9) << "Voltage " << "|" << setw(13) << "HDD Memory " << "|" << endl;
}

void Server::setMemHD(int memHD)
{
	this->memHD = memHD;
}

int Server::getMemHD()
{
	return memHD;
}

istream& operator>>(istream& in, Server& server)
{
	Static* stat;
	stat = &server;
	in >> *(dynamic_cast<Static*>(stat));
	cout << "Enter hard drive memory: ";
	server.memHD = MyExc_Vvod::Check_int();
	return in;
}

ostream& operator<<(ostream& out, Server& server)
{
	Static* stat;
	stat = &server;
	out << *(dynamic_cast<Static*>(stat));
	out << "|" << setw(13)  << server.memHD << "|" << endl;
	return out;
}
