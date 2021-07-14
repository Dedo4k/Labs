#pragma once
#include "Portable.h"

class MPhone : public Portable
{
private:
	string screen;
	double screenSize;
public:
	MPhone();
	~MPhone();
	friend istream& operator>>(istream& in, MPhone& mphome);
	friend ostream& operator<<(ostream& out, MPhone& mphone);
	friend fstream& operator>>(fstream& in, MPhone& mphone);
	friend fstream& operator<<(fstream& out, MPhone& mphone);
	friend ifstream& operator>>(ifstream& in, MPhone& mphone);
	friend ofstream& operator<<(ofstream& out, MPhone& mphone);
	bool operator==(MPhone mphone);
	bool operator>(MPhone mphone);
	bool operator<(const MPhone& cmp)const
	{
		return brand < cmp.brand;
	}
	//bool operator<(MPhone mphone);
	void shapka();
	void getProc() {};
	void setScreen(string screen);
	string getScreen();
	void setScreenSize(double screenSize);
	double getScreenSize();
};