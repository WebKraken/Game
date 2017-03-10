#pragma once
#include "Mesh.h"
class SmartMesh :
	public Mesh
{
public:
protected:
	SmartMesh();
	virtual ~SmartMesh();
	void GenerateNormals();
};

