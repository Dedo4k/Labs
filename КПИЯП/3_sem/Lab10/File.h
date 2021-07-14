#pragma once
#include <iostream>
#include <string>
using namespace std;

class File
{
protected:
	string fileName;
public:
	File(const string name) { this->fileName = name; }

};

