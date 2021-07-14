#pragma once
#include "Computer.h"


class Static : public Computer
{
protected:
	string proc;
	int procModel;
	int voltage;
public:
	Static();
	~Static();
	friend istream& operator>>(istream& in, Static& stat);
	friend ostream& operator<<(ostream& out, Static& stat);
	void setProc(string proc);
	string getProc();
	void setProcModel(int procModel);
	int getProcModel();
	void setVoltage(int voltage);
	int getVoltage();
};