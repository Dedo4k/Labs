#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual void Print() = 0;
};