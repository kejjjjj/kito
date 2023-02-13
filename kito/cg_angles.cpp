#include "pch.h"

void cg::setYaw(float ref, float ang)
{
	//float readonly = *(float*)0x6E17BC;
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	*(float*)0x86872C += ref;

}
void cg::setPitch(float ref, float ang)
{
	//float ref = *(float*)(0x6E17BC - 4);
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	*(float*)(0x86872C - 4) += ref;

}
void cg::setRoll(float ref, float ang)
{
	//float ref = *(float*)(0x6E17BC - 4);
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	*(float*)(0x86872C + 4) += ref;

}
void cg::CG_SetPlayerAngles(vec3_t source, vec3_t target)
{
	setPitch(source[0], target[0]);
	setYaw(source[1], target[1]);
	setRoll(source[2], target[2]);
}
void cg::CG_SetPlayerAngles(fvec3 source, fvec3 target)
{
	setPitch(source.x, target.x);
	setYaw(source.y, target.y);
	setRoll(source.z, target.z);
}

void cg::CG_SetServerAngles(int* a)
{
	vec3_t b = { a[0], a[1], a[2] };

	CG_SetServerAngles(b);
}
void cg::CG_SetServerAngles(vec3_t angles)
{
	//if (NOT_SERVER)
	//	return;

	vec3_t ang;
	VectorCopy(vAngle->angles, ang);
	float yaw = ANGLE2SHORT(ang[YAW]);
	float pitch = ANGLE2SHORT(ang[PITCH]);
	float roll = ANGLE2SHORT(ang[ROLL]);


	usercmd_s* cmd = input->GetUserCmd(input->cmdNumber - 1);

	cmd->serverTime = *(int*)(0x0714BA0) + 1; //oldtime + 1

	if (cmd->serverTime) {

		if (angles[YAW] < 0) {
			angles[YAW] += 180;
			angles[YAW] = (angles[YAW] + 180 % 360);
		}

		yaw -= yaw * 2 - ANGLE2SHORT(angles[YAW]);
		pitch -= pitch * 2 - ANGLE2SHORT(angles[PITCH]);
		roll -= roll * 2 - ANGLE2SHORT(angles[ROLL]);



		cmd->angles[YAW] += yaw;
		cmd->angles[PITCH] += pitch;
		cmd->angles[ROLL] += roll;
	}

}