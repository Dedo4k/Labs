#pragma once
#include "Shape.h"

class TwoDShape : public Shape
{
private:
	char color[4] = "RED";
public:
	TwoDShape();
	~TwoDShape();
	char* getColor();
};