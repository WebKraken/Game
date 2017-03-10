#pragma once
#include <boost/numeric/conversion/cast.hpp>
#include <vector>
#include "Vertex.h"

using namespace std;
using boost::numeric_cast;

class Mesh
{
public:
	Mesh();
	Mesh(const vector<uint32_t>& indices, const vector<Vertex>& vertices);
	virtual ~Mesh();

	// Accessors
	__forceinline const uint32_t& IndexCount() const { return numeric_cast<uint32_t>(m_Indices.size()); };
	__forceinline const uint32_t& VertexCount() const { return numeric_cast<uint32_t>(m_Vertices.size()); };
	__forceinline vector<uint32_t>& Indices() { return m_Indices; };
	__forceinline vector<Vertex>& Vertices() { return m_Vertices; };

	// MeshManipulation
	bool AppendMesh(const vector<uint32_t>& indices, const vector<Vertex>& vertices);
	bool AppendTriangle(const vector<uint32_t>& triangle, const vector<Vertex>& vertices = {});
	bool RemoveSingleVertex(uint32_t index);
	bool RemoveVertices(const vector<uint32_t>& indices);
	bool RemoveTriangle(const vector<uint32_t>& indices);
	bool RemoveUnusedVertices();
	bool ClearMesh();

protected:
	vector<uint32_t> m_Indices;
	vector<Vertex> m_Vertices;

private:
	void RemoveDeadVertices(const vector<Vertex*>& deadVertices);
	void RemoveDeadTriangles(const vector<uint32_t>& deadIndices);
	void Index2Triangle(const uint32_t index, vector<uint32_t>& triangleOut) const;
	bool IsValidIndex(const uint32_t index) const;
	bool IsTriangle(const vector<uint32_t>& triangle) const;
};

