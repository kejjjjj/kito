#pragma once

#ifndef _abra
#define _abra

#include "pch.h"

float VectorAngle(const fvec2& s, const fvec2 e);
float VectorAngle(const ivec2& e); //where s = 0,0 
float VectorAngleDifference(const fvec2& a, const fvec2& b);
fvec2 VectorLinearCombination(const fvec2& a, const fvec2& b, const float scalarX = .5f, const float scalarY = .5f);
fvec2 VectorConvexCombination(const fvec2& a, const fvec2& b, const float alpha, const float beta);
bool VectorSimultaneousEquation(const fvec2& a, const fvec2& b, const fvec2& linearcombination, fvec2& out);
inline bool MouseHovered(const ivec2& mins, const ivec2& maxs)
{
	tagPOINT p;
	GetCursorPos(&p);

	return 
			p.x > mins.x && p.x < maxs.x
		&&	p.y > mins.y && p.y < maxs.y;
}
inline ivec2 GetCPos()
{
	tagPOINT p;
	GetCursorPos(&p);

	return { p.x, p.y };
}
#endif