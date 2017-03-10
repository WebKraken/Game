#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#pragma once
#include <directxmath.h>

using namespace DirectX;

namespace PColor
{
	XMFLOAT4 white = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	XMFLOAT4 red = XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	XMFLOAT4 green = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	XMFLOAT4 blue = XMFLOAT4(0.f, 0.f, 1.f, 1.f);
};

namespace PGeo
{
	XMFLOAT3A origin = XMFLOAT3A(0.f, 0.f, 0.f);
};
#endif