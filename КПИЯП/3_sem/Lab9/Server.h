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
	bool operator==(Server server);
	void shapka();
	void setMemHD(int memHD);
	int getMemHD();
};