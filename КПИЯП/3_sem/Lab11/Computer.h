#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
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
	friend fstream& operator>>(fstream& in, Computer& computer);
	friend fstream& operator<<(fstream& out, Computer& computer);
	friend ifstream& operator>>(ifstream& in, Computer& computer);
	friend ofstream& operator<<(ofstream& out, Computer& computer);
	void setBrand(string brand);
	string getBrand();
};