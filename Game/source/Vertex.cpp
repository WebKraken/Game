#include "Vertex.h"
#include "Constants.h"

Vertex::Vertex()
{
	pos = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	normal = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	color = XMVectorSet(1.f, 1.f, 1.f, 1.f);
	texCoord = XMVectorSet(0.f, 0.f, 0.f, 0.f);
}

Vertex::~Vertex()
{
}


Vertex::Vertex(const XMVECTOR pos)
{
	this->pos = pos;
	normal = XMVectorSet(0.f, 0.f, 0.f, 0.f);
	color = XMVectorSet(1.f, 1.f, 1.f, 1.f);
	texCoord = XMVectorSet(0.f, 0.f, 0.f, 0.f);
}

Vertex::Vertex(const XMVECTOR pos, const XMVECTOR normal, XMVECTOR color, const XMVECTOR texCoord)
{
	this->pos = pos;
	this->normal = normal;
	this->color = color;
	this->texCoord = texCoord;
}
