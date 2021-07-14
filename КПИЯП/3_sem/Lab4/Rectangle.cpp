#include "Rectangle.h"

Rectangle::Rectangle(int w, int h)
{
	cout << "Rectangle constructor" << endl;
	this->width = w;
	this->height = h;
}

Rectangle::~Rectangle()
{
	cout << "Rectangle destructor" << endl;
}

void Rectangle::Print()
{
	cout << endl << "type - " << type << endl;
	cout << "color - " << getColor() << endl;
	cout << "area - " << area << endl;
}

void Rectangle::Count()
{
	area = (double)width * (double)height;
}