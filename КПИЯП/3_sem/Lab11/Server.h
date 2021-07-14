#pragma once
#include "Static.h"

class Server : public Static
{
private:
	int memHD;
public:
	Server();
	~Server();
	friend istream& operator>>(istream& in, Server& server);
	friend ostream& operator<<(ostream& out, Server& server);
	friend fstream& operator>>(fstream& in, Server& server);
	friend fstream& operator<<(fstream& out, Server& server);
	friend ifstream& operator>>(ifstream& in, Server& server);
	friend ofstream& operator<<(ofstream& out, Server& server);
	bool operator==(Server server);
	bool operator>(Server server);
	bool operator<(const Server& cmp)const
	{
		return brand < cmp.brand;
	}
	//bool operator<(Server server);
	void shapka();
	void setMemHD(int memHD);
	int getMemHD();
};