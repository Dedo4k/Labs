#include "ThreeDShape.h"

ThreeDShape::ThreeDShape()
{
	cout << "ThreeDShape constructor" << endl;
}

ThreeDShape::~ThreeDShape()
{
	cout << "ThreeDShape destructor" << endl;
}

char* ThreeDShape::getColor()
{
	return color;
}