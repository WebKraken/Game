#pragma once
#include "SmartMesh.h"

class Shape 
	: public SmartMesh
{
public:
	Shape();
	~Shape();

	void Sphere(float radius, int slices, int stacks);
};

