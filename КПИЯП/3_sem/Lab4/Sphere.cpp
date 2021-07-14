#include "Sphere.h"

Sphere::Sphere(int r)
{
	cout << "Sphere constructor" << endl;
	this->radius = r;
}

Sphere::~Sphere()
{
	cout << "Shere destructor" << endl;
}

void Sphere::Count()
{
	area = 4 * M_PI * (double)radius * (double)radius;
	volume = 4.0 / 3.0 * M_PI * (double)radius * (double)radius * (double)radius;
}

void Sphere::Print()
{
	cout << endl << "type - " << type << endl;
	cout << "color - " << getColor() << endl;
	cout << "area - " << area << endl;
	cout << "volume - " << volume << endl;
}