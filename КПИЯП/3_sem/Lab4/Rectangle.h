#pragma once
#include "TwoDShape.h"

class Rectangle : public TwoDShape
{
private:
	char type[10] = "Rectangle";
	int width = 0;
	int height = 0;
	double area = 0;
public:
	Rectangle(int w, int h);
	~Rectangle();
	void Print()override;
	void Count();
};