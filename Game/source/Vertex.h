#pragma once
#include <directxmath.h>

using namespace DirectX;

class Vertex
{
public:
	Vertex();
	~Vertex();
	Vertex(const XMVECTOR pos);
	Vertex(const XMVECTOR pos, const XMVECTOR normal, XMVECTOR color, const XMVECTOR texCoord);

	// The order of these elements matters for D3D
	XMVECTOR pos;
	XMVECTOR normal;
	XMVECTOR color;
	XMVECTOR texCoord;
};