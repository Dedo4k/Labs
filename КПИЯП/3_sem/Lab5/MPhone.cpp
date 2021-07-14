#include "MPhone.h"

MPhone::MPhone()
{
	cout << "MPhone constructor" << endl << endl;
	screen = '\0';
	screenSize = 0.0;
}

MPhone::~MPhone()
{
	cout << endl << "MPhone destructor" << endl;
}

void MPhone::setScreen(string screen)
{
	this->screen = screen;
}

string MPhone::getScreen()
{
	return screen;
}

void MPhone::setScreenSize(double screenSize)
{
	this->screenSize = screenSize;
}

double MPhone::getScreenSize()
{
	return screenSize;
}

istream& operator>>(istream& in, MPhone& mphome)
{
	Portable* portable;
	portable = &mphome;
	in >> *(dynamic_cast<Portable*>(portable));
	cout << "Enter screen - ";
	in >> mphome.screen;
	cout << "Enter screen size - ";
	in >> mphome.screenSize;
	return in;
}

ostream& operator<<(ostream& out, MPhone& mphone)
{
	Portable* portable;
	portable = &mphone;
	out << *(dynamic_cast<Portable*>(portable));
	out << "Screen: " << mphone.screen << endl;
	out << "Screen size: " << mphone.screenSize << endl;
	return out;
}