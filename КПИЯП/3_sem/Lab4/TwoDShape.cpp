#include "TwoDShape.h"

TwoDShape::TwoDShape()
{
	cout << "TwoDShape constructor" << endl;
}

TwoDShape::~TwoDShape()
{
	cout << "TwoDShape destructor" << endl;
}

char* TwoDShape::getColor()
{
	return color;
}