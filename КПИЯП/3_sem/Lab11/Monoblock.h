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
	friend fstream& operator>>(fstream& in, Monoblock& monoblock);
	friend fstream& operator<<(fstream& out, Monoblock& monoblock);
	friend ifstream& operator>>(ifstream& in, Monoblock& monoblock);
	friend ofstream& operator<<(ofstream& out, Monoblock& monoblock);
	bool operator==(Monoblock monoblock);
	bool operator>(Monoblock monoblock);
	//bool operator<(Monoblock monoblock);
	//bool operator<(const Monoblock &cmp)const
	//{
	//	return brand < cmp.brand;
	//}
	void shapka();
	void setMemCap(int memCap);
	int getMemCap();
};