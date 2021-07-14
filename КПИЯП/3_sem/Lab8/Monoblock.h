#pragma once
#include "Static.h"

class Monoblock : public Static
{
private:
	int memCap;
public:
	Monoblock();
	~Monoblock();
	friend istream& operator>>(istream& in, Monoblock& monoblock);
	friend ostream& operator<<(ostream& out, Monoblock& monoblock);
	void shapka();
	void setMemCap(int memCap);
	int getMemCap();
};