#pragma once
#include "ThreeDShape.h"

class Sphere : public ThreeDShape
{
private:
	char type[7] = "Sphere";
	int radius = 0;
	double area = 0;
	double volume = 0;
public:
	Sphere(int r);
	~Sphere();
	void Print()override;
	void Count();
};