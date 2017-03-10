#include "Shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

void Shape::Sphere(float radius, int slices, int stacks)
{
	float PI_Stacks = XM_PI / float(stacks);
	float PI2_Slices = XM_2PI / float(slices);

	float Theta, Phi, CosP, SinP;
	int i, i2, vc = 0, ic = 0;
	m_Vertices.resize(slices * (stacks - 1) + 2);
	m_Indices.resize(slices * 6 * (stacks - 1));

	Vertex vertex;
	for (i = 1; i < stacks; i++)
	{
		Phi = float(i) * PI_Stacks;
		CosP = cosf(Phi);
		SinP = sinf(Phi);

		for (i2 = 0; i2 < slices; i2++)
		{
			Theta = float(i2) * PI2_Slices;
			vertex.pos = XMVectorSet(radius * cosf(Theta) * SinP, radius * sinf(Theta) * SinP, radius * CosP, 0.f);
			m_Vertices[vc++] = vertex;    //add the vertex to the mesh
		}
	}

	//add the top and bottom vertices to the mesh
	int TopVertex = vc, BottomVertex = vc + 1;
	vertex.pos = XMVectorSet(0.f, 0.f, radius, 0.f);
	m_Vertices[vc++] = vertex;
	vertex.pos = XMVectorSet(0.f, 0.f, -radius, 0.f);
	m_Vertices[vc++] = vertex;

	//add the top and bottom triangles (all triangles involving the TopVertex and BottomVertex)
	int ip1, i2p1;
	for (i = 0; i < slices; i++)
	{
		ip1 = i + 1;
		if (ip1 == slices) ip1 = 0;

		m_Indices[ic++] = i;
		m_Indices[ic++] = TopVertex;                    //top triangle
		m_Indices[ic++] = ip1;

		m_Indices[ic++] = ip1 + (stacks - 2) * slices;
		m_Indices[ic++] = BottomVertex;                    //bottom triangle
		m_Indices[ic++] = i + (stacks - 2) * slices;
	}

	//add all the remaining triangles
	for (i = 0; i < stacks - 2; i++)
	{
		for (i2 = 0; i2 < slices; i2++)
		{
			i2p1 = i2 + 1;
			if (i2p1 == slices) i2p1 = 0;

			m_Indices[ic++] = (i + 1) * slices + i2;
			m_Indices[ic++] = i * slices + i2;
			m_Indices[ic++] = i * slices + i2p1;

			m_Indices[ic++] = (i + 1) * slices + i2;
			m_Indices[ic++] = i * slices + i2p1;
			m_Indices[ic++] = (i + 1) * slices + i2p1;
		}
	}

	GenerateNormals();
}
