#pragma once
#include "TwoDShape.h"

class Circle : public TwoDShape
{
private:
	char type[7] = "Circle";
	int radius = 0;
	double area = 0;
public:
	Circle(int r);
	~Circle();
	void Print()override;
	void Count();
};