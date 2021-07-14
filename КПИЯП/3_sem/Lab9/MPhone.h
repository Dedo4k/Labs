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
	bool operator==(MPhone mphone);
	void shapka();
	void setScreen(string screen);
	string getScreen();
	void setScreenSize(double screenSize);
	double getScreenSize();
};