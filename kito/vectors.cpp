#include "pch.h"


float VectorAngle(const fvec2& s, const fvec2 e)
{

	//const auto vec =  s - e;
	//return atan((float)vec.y / (float)vec.x) * 180.f / PI;

	auto sub = s - e;
	float angle = atan2(-sub.y, -sub.x) * 180.f / PI;


	return angle;
}
float VectorAngle(const ivec2& e)  //where s = 0,0 
{	
	//			opposite	  adjacent
	return atan((float)e.y / (float)e.x) * 180.f / PI;
}
fvec2 VectorLinearCombination(const fvec2& a, const fvec2& b, const float scalarX, const float scalarY)
{
	return a * scalarX + b * scalarY;
}
fvec2 VectorConvexCombination(const fvec2& a, const fvec2& b, const float alpha, const float beta)
{
	if (alpha + beta != 1)
		return{};

	return { a * alpha + b * beta };
}
float VectorAngleDifference(const fvec2& a, const fvec2& b)
{
	return acos(a.dot(b) / (a.mag() * b.mag())) * 180.f / PI;
}
bool VectorSimultaneousEquation(const fvec2& x, const fvec2& y, const fvec2& linearcombination, fvec2& out)
{
	//printf("%.1f = %.0fx + %.0fy\n",linearcombination.x, x.x, x.y);
	//printf("%.1f = %.0f + %.0fy\n\n",linearcombination.y, y.x, y.y);

	//scale both until equal X
	const float scaleX = (x.x * y.x) / x.x;
	const float scaleY = (x.x * y.x) / y.x;

	//subtract equations and eliminate X
	const float subtractedX = x.x * scaleX - y.x * scaleY;
	const float subtractedY = x.y * scaleX - y.y * scaleY;

	const float resultA = linearcombination.x * scaleX - linearcombination.y * scaleY;

	//printf("scale {%.1f, %.1f}\n\n", scaleX, scaleY);
	//printf("  %.1f = %.1fx + %.1fy\n", linearcombination.x * scaleX,x.x * scaleX, x.y * scaleX);
	//printf("- %.1f = %.1fx + %.1fy\n", linearcombination.y * scaleY, y.x * scaleY, y.y * scaleY);
	//printf("--------------\n");
	//printf("   %.1f = %.1fx + %.1fy\n\n", resultA, subtractedX, subtractedY);

	if (subtractedY == 0)
		return false;

	const float solvedY = resultA / subtractedY;

	////y found
	//printf("y =  %.1f / %.1f\n", resultA, subtractedY);
	//printf("y =  %.1f\n\n", solvedY);

	////find x
	//printf("%.1f = %.1fx + %.1f * %.1f\n", linearcombination.y, y.x, y.y, solvedY);
	//printf("%.1f = %.1fx + %.1f\n", linearcombination.y, y.x, y.y * solvedY);
	//printf("%.1f - %.1f = %.1fx\n", linearcombination.y, y.y * solvedY, y.x);
	//printf("%.1f = %.1fx\n\n", linearcombination.y - y.y * solvedY, y.x);

	const float solvedX = (linearcombination.y - y.y * solvedY) / y.x;
	//printf("x = %.1f / %.1f\n", linearcombination.y - y.y * solvedY, y.x);
	//printf("x = %.1f\n", solvedX);

	out = { solvedX, solvedY };

	return true;
}