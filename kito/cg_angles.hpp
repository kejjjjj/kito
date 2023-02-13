#pragma once


#ifndef cgangle
#define cgangle

#include "pch.h"

namespace cg {
	void setYaw(float ref, float ang);
	void setPitch(float ref, float ang);
	void setRoll(float ref, float ang);
	void CG_SetPlayerAngles(vec3_t source, vec3_t target);
	void CG_SetPlayerAngles(fvec3 source, fvec3 target);

	void CG_SetServerAngles(int* a);
	void CG_SetServerAngles(vec3_t angles);
}
#endif