#pragma once
#include <iostream>
#include <string>
using namespace std;

class MyExc
{
private:
	string message;
public:
	MyExc();
	MyExc(string message);
	~MyExc();
	void setMessage(string message);
	static void Terminate();
	string getMessage();
	virtual string what() = 0;
};