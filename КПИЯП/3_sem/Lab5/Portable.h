#pragma once
#include "Computer.h"

class Portable : public Computer
{
protected:
	int battery;
public:
	Portable();
	~Portable();
	friend istream& operator>>(istream& in, Portable& portable);
	friend ostream& operator<<(ostream& out, Portable& portable);
	void setBattery(int battery);
	int getBattery();
};