#include "SmartMesh.h"

SmartMesh::SmartMesh()
{
}
SmartMesh::~SmartMesh()
{
}

void SmartMesh::GenerateNormals()
{
	XMVECTOR V1, V2;

	for (Vertex v : m_Vertices)
	{
		v.normal = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	}

	for (uint32_t i = 0; i < m_Indices.size(); i += 3)
	{
		Vertex& v1 = m_Vertices[m_Indices[i + 0]];
		Vertex& v2 = m_Vertices[m_Indices[i + 1]];
		Vertex& v3 = m_Vertices[m_Indices[i + 2]];

		V1 = v3.pos - v1.pos;
		V2 = v2.pos - v1.pos;

		XMVECTOR normal = XMVector3Cross(V1, V2);

		v1.normal += normal;
		v2.normal += normal;
		v3.normal += normal;
	}

	for (Vertex v : m_Vertices)
	{
		v.normal = XMVector3NormalizeEst(v.normal);
	}
}

