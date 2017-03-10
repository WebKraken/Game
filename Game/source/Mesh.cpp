#include "Mesh.h"
#include <algorithm>
#include <functional>

Mesh::Mesh()
{
}

Mesh::Mesh(const vector<uint32_t>& indices, const vector<Vertex>& vertices)
{
	AppendMesh(indices, vertices);
}


Mesh::~Mesh()
{
}

bool Mesh::AppendMesh(const vector<uint32_t>& indices, const vector<Vertex>& vertices)
{
	bool inRange = *max_element(indices.begin(), indices.end()) <= vertices.size();
	if (indices.size() % 3 == 0 && inRange)
	{
		uint32_t shift = numeric_cast<uint32_t>(m_Vertices.size());
		for (uint32_t index : indices)
		{
			index += shift;
		}
		m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
		m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::AppendTriangle(const vector<uint32_t>& triangle, const vector<Vertex>& vertices)
{
	if (IsTriangle(triangle))
	{
		return AppendMesh(triangle, vertices);
	}
	else
	{
		return false;
	}
}

bool Mesh::RemoveSingleVertex(uint32_t index)
{
	vector<uint32_t> indices;
	indices.push_back(index);
	return RemoveVertices(indices);
}

bool Mesh::RemoveVertices(const vector<uint32_t>& indices)
{
	if (indices.empty())
	{
		return false;
	}

	vector<Vertex*> deadVertices;
	for (uint32_t index : indices)
	{
		if (IsValidIndex(index))
		{
			deadVertices.push_back(&m_Vertices[index]);
		}
		else 
		{
			return false;
		}
	}

	if (deadVertices.empty() && indices.empty())
	{
		return false;
	}
	else
	{
		RemoveDeadVertices(deadVertices);
		RemoveDeadTriangles(indices);
		return true;
	}
}

bool Mesh::RemoveTriangle(const vector<uint32_t>& indices)
{
	if (IsTriangle(indices))
	{
		return RemoveVertices(indices);
	}
	else
	{
		return false;
	}
}

bool Mesh::RemoveUnusedVertices()
{
	vector<Vertex*> deadVertices;
	for (uint32_t index = 0; index < m_Vertices.size(); index++)
	{
		if (IsValidIndex(index) == false)
		{
			deadVertices.push_back(&m_Vertices[index]);
		}
	}
	if (deadVertices.empty())
	{
		return false;
	}
	else
	{
		RemoveDeadVertices(deadVertices);
		return true;
	}
}

void Mesh::RemoveDeadVertices(const vector<Vertex*>& deadVertices)
{
	m_Vertices.erase(remove_if(m_Vertices.begin(), m_Vertices.end(),
		[deadVertices](Vertex& vertex) {return find(deadVertices.begin(), deadVertices.end(), &vertex) != deadVertices.end(); })
		, m_Vertices.end());
}

// Make sure deadIndices are valid
void Mesh::RemoveDeadTriangles(const vector<uint32_t>& deadIndices)
{
	vector<uint32_t> triangle;
	vector<uint32_t> deadTriangles;
	for (uint32_t index : deadIndices)
	{
		Index2Triangle(index, triangle);
		deadTriangles.insert(deadTriangles.end(), triangle.begin(), triangle.end());
	}
	// Erase duplicates
	sort(deadTriangles.begin(), deadTriangles.end());
	deadTriangles.erase(unique(deadTriangles.begin(), deadTriangles.end()), deadTriangles.end());

	m_Indices.erase(remove_if(m_Indices.begin(), m_Indices.end(),
		[deadTriangles](uint32_t& index) { return find(deadTriangles.begin(), deadTriangles.end(), index) != deadTriangles.end(); })
		, m_Indices.end());
}

bool Mesh::ClearMesh()
{
	if (m_Indices.empty() && m_Vertices.empty())
	{
		return false;
	}
	else
	{
		m_Indices.resize(0);
		m_Vertices.resize(0);
		return true;
	}
}

// Make sure index is valid
void Mesh::Index2Triangle(const uint32_t index, vector<uint32_t>& triangleOut) const
{
	uint32_t pos = numeric_cast<uint32_t>(distance(m_Indices.begin(), find(m_Indices.begin(), m_Indices.end(), index)));
		
	triangleOut.resize(3);
	if (pos % 3 == 0)
	{
		triangleOut[0] = pos + 0;
		triangleOut[1] = pos + 1;
		triangleOut[2] = pos + 2;
	}
	if (pos % 3 == 1)
	{
		triangleOut[0] = pos - 1;
		triangleOut[1] = pos - 0;
		triangleOut[2] = pos + 1;
	}
	if (pos % 3 == 2)
	{
		triangleOut[0] = pos - 2;
		triangleOut[1] = pos - 1;
		triangleOut[2] = pos - 0;
	}
}

bool Mesh::IsTriangle(const vector<uint32_t>& triangle) const
{
	if (triangle.size() == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::IsValidIndex(const uint32_t index) const
{
	if (find(m_Indices.begin(), m_Indices.end(), index) != m_Indices.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}