#include "Pyramid.h"

Pyramid::Pyramid(int w, int h, int l)
{
	cout << "Pyramid constructor" << endl;
	this->height = h;
	this->width = w;
	this->length = l;
}

Pyramid::~Pyramid()
{
	cout << "Pyramid destructor" << endl;
}

void Pyramid::Print()
{
	cout << endl << "type - " << type << endl;
	cout << "color - " << getColor() << endl;
	cout << "area - " << area << endl;
	cout << "volume - " << volume << endl;
}

void Pyramid::Count()
{
	volume = (double)width * (double)length * (double)height / 3.0;
	area = (double)width * sqrt((double)height * (double)height - (double)length * (double)length / 4.0) + (double)length * sqrt((double)height * (double)height - (double)width * (double)width / 4.0) + (double)width * (double)length;
}