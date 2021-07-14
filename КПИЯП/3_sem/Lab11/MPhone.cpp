#include "MPhone.h"
#include "MyExc_Vvod.h"

MPhone::MPhone()
{
	//cout << "MPhone constructor" << endl << endl;
	screen = '\0';
	screenSize = 0.0;
}

MPhone::~MPhone()
{
	//cout << endl << "MPhone destructor" << endl;
}

bool MPhone::operator==(MPhone mphone)
{
	return this->getBrand() == mphone.getBrand() && this->getScreenSize() == mphone.getScreenSize() && this->getScreen() == mphone.getScreen() && this->getBattery() == mphone.getBattery();
}

bool MPhone::operator>(MPhone mphone)
{
	if (this->getBrand() > mphone.getBrand())
		return true;
}

//bool MPhone::operator<(MPhone mphone)
//{
//	if (this->getBrand() < mphone.getBrand())
//		return true;
//}

void MPhone::shapka()
{
	cout << endl << "|" << setw(7) << "Brand " << "|" << setw(9) << "Battery " << "|" << setw(8) << "Screen " << "|" << setw(13) << "Screen size " << "|" << endl;
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
	cout << "Enter screen: ";
	mphome.screen = MyExc_Vvod::Check_string(8);
	cout << "Enter screen size: ";
	mphome.screenSize = MyExc_Vvod::Check_int();
	return in;
}

ostream& operator<<(ostream& out, MPhone& mphone)
{
	Portable* portable;
	portable = &mphone;
	out << *(dynamic_cast<Portable*>(portable));
	out << "|" << setw(8) << mphone.screen << "|" << setw(13) << mphone.screenSize << "|" << endl;
	return out;
}

fstream& operator>>(fstream& in, MPhone& mphone)
{
	in >> *(dynamic_cast<Portable*>(&mphone));
	in >> mphone.screen;
	in >> mphone.screenSize;
	return in;
}

fstream& operator<<(fstream& out, MPhone& mphone)
{
	out << *(dynamic_cast<Portable*>(&mphone));
	out << mphone.screen << "\n";
	out << mphone.screenSize << "\n";
	return  out;
}

ifstream& operator>>(ifstream& in, MPhone& mphone)
{
	in >> *(dynamic_cast<Portable*>(&mphone));
	in >> mphone.screen;
	in >> mphone.screenSize;
	return in;
}

ofstream& operator<<(ofstream& out, MPhone& mphone)
{
	out << *(dynamic_cast<Portable*>(&mphone));
	out << mphone.screen << "\n";
	out << mphone.screenSize << "\n";
	return  out;
}
