#pragma once
#include "Shape.h"

class ThreeDShape : public Shape
{
private:
	char color[5] = "BLUE";
public:
	ThreeDShape();
	~ThreeDShape();
	char* getColor();
};