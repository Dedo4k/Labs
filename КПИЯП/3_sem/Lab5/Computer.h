#pragma once
#include <iostream>
#include <string>
using namespace std;

class Computer
{
protected:
	string brand;
public:
	Computer();
	~Computer();
	friend istream& operator>>(istream& in, Computer& computer);
	friend ostream& operator<<(ostream& out, const Computer& computer);
	void setBrand(string brand);
	string getBrand();
};