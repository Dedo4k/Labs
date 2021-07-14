#include "MyExc.h"

MyExc::MyExc()
{
	//cout << "MyExc constructor" << endl;
	this->message = "";
}

MyExc::MyExc(string message)
{
	this->message = message;
}

MyExc::~MyExc()
{
	//cout << "MyExc destructor" << endl;
}

void MyExc::setMessage(string message)
{
	this->message = message;
}

void MyExc::Terminate()
{
	cout << endl << "Terminate" << endl;
	abort();
}

string MyExc::getMessage()
{
	return message;
}
