#include "Circle.h"

Circle::Circle(int r)
{
	cout << "Circle constructor" << endl;
	this->radius = r;
}
 
Circle::~Circle()
{
	cout << "Circle destructor" << endl;
}

void Circle::Count()
{
	area = M_PI * radius * radius;
}

void Circle::Print()
{
	cout << endl << "type - " << type << endl;
	cout << "color - " << getColor() << endl;
	cout << "area - " << area << endl;
}
