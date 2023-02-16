#include "pch.h"


bool cg::WorldToScreen(const fvec3 location, ivec2* out)
{
	const int centerX = refdef->width / 2;
	const int centerY = refdef->height / 2;

	const fvec3 vright = refdef->viewaxis[1];
	const fvec3 vup = refdef->viewaxis[2];
	const fvec3 vfwd = refdef->viewaxis[0];

	const fvec3 vLocal = location - refdef->vieworg;
	fvec3 vTransform;

	vTransform.x = vLocal.dot(vright);
	vTransform.y = vLocal.dot(vup);
	vTransform.z = vLocal.dot(vfwd);

	if (vTransform.z < 0.01) {
		return 0;
	}

	if (out) {
		out->x = centerX * (1 - (vTransform.x / refdef->tanHalfFovX / vTransform.z));
		out->y = centerY * (1 - (vTransform.y / refdef->tanHalfFovY / vTransform.z));
	}

	return vTransform.z > 0;

}