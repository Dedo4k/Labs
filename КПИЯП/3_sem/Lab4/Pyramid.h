#pragma once
#include "ThreeDShape.h"

class Pyramid : public ThreeDShape
{
private:
	char type[8] = "Pyramid";
	int width = 0;
	int length = 0;
	int height = 0;
	double area = 0;
	double volume = 0;
public:
	Pyramid(int w, int h, int l);
	~Pyramid();
	void Print()override;
	void Count();
};