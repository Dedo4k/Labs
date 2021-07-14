#include "Server.h"

Server::Server()
{
	cout << "Server constructor" << endl << endl;
	memHD = 0;
}

Server::~Server()
{
	cout << endl << "Server destructor" << endl;
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
	cout << "Enter hard drive memory - ";
	in >> server.memHD;
	return in;
}

ostream& operator<<(ostream& out, Server& server)
{
	Static* stat;
	stat = &server;
	out << *(dynamic_cast<Static*>(stat));
	out << "Hard Drive capacity: " << server.memHD << endl;
	return out;
}