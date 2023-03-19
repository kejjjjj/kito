#include "pch.h"

box_s::box_s(const fvec3& origin, const fvec3& mins, const fvec3& maxs)
{
	//box_s box{};

	fvec3 lowA, lowB, lowC, lowD;
	fvec3 highA, highB, highC, highD;

	lowA.x = origin.x - mins.x;
	lowA.y = origin.y - mins.y;
	lowA.z = origin.z - mins.z;

	lowB.x = origin.x + mins.x;
	lowB.y = origin.y + mins.y;
	lowB.z = origin.z - mins.z;

	lowC.x = origin.x - mins.x;
	lowC.y = origin.y + mins.y;
	lowC.z = origin.z - mins.z;

	lowD.x = origin.x + mins.x;
	lowD.y = origin.y - mins.y;
	lowD.z = origin.z - mins.z;

	highA.x = lowA.x;
	highA.y = lowA.y;
	highA.z = origin.z + maxs.z;

	highB.x = lowB.x;
	highB.y = lowB.y;
	highB.z = origin.z + maxs.z;

	highC.x = lowC.x;
	highC.y = lowC.y;
	highC.z = origin.z + maxs.z;

	highD.x = lowD.x;
	highD.y = lowD.y;
	highD.z = origin.z + maxs.z;

	this->lowA_valid = cg::WorldToScreen(lowA, &this->lowA);
	this->lowB_valid = cg::WorldToScreen(lowB, &this->lowB);
	this->lowC_valid = cg::WorldToScreen(lowC, &this->lowC);
	this->lowD_valid = cg::WorldToScreen(lowD, &this->lowD);

	this->highA_valid = cg::WorldToScreen(highA, &this->highA);
	this->highB_valid = cg::WorldToScreen(highB, &this->highB);
	this->highC_valid = cg::WorldToScreen(highC, &this->highC);
	this->highD_valid = cg::WorldToScreen(highD, &this->highD);

	//return box;
}
void box_s::R_DrawConstructedBoxEdges(vec4_t col) const
{
	if (!ImGui::GetCurrentContext())
		return;

	if (this->lowA_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowA.x, this->lowA.y), ImVec2(this->lowC.x, this->lowC.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowB_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowB.x, this->lowB.y), ImVec2(this->lowD.x, this->lowD.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowC_valid && this->lowB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowC.x, this->lowC.y), ImVec2(this->lowB.x, this->lowB.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowD_valid && this->lowA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowD.x, this->lowD.y), ImVec2(this->lowA.x, this->lowA.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highA_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highA.x, this->highA.y), ImVec2(this->highC.x, this->highC.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highB.x, this->highB.y), ImVec2(this->highD.x, this->highD.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highC_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highC.x, this->highC.y), ImVec2(this->highB.x, this->highB.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highD_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highD.x, this->highD.y), ImVec2(this->highA.x, this->highA.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowA_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowA.x, this->lowA.y), ImVec2(this->highA.x, this->highA.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowB_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowB.x, this->lowB.y), ImVec2(this->highB.x, this->highB.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowC_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowC.x, this->lowC.y), ImVec2(this->highC.x, this->highC.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowD_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowD.x, this->lowD.y), ImVec2(this->highD.x, this->highD.y), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);
}
void box_s::R_DrawConstructedBox(vec4_t col) const
{
	if (!ImGui::GetCurrentContext())
		return;

	if (this->lowA_valid && this->highC_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA.x, this->lowA.y), ImVec2(this->highC.x, this->highC.y), ImVec2(this->lowC.x, this->lowC.y), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowA_valid && this->highA_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA.x, this->highA.y), ImVec2(this->lowA.x, this->lowA.y), ImVec2(this->highC.x, this->highC.y), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowB_valid && this->highD_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowB.x, this->lowB.y), ImVec2(this->highD.x, this->highD.y), ImVec2(this->lowD.x, this->lowD.y), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowB_valid && this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highB.x, this->highB.y), ImVec2(this->lowB.x, this->lowB.y), ImVec2(this->highD.x, this->highD.y), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowC_valid && this->highB_valid && this->lowB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowC.x, this->lowC.y), ImVec2(this->highB.x, this->highB.y), ImVec2(this->lowB.x, this->lowB.y), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowC_valid && this->highC_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highC.x, this->highC.y), ImVec2(this->lowC.x, this->lowC.y), ImVec2(this->highB.x, this->highB.y), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowD_valid && this->highA_valid && this->lowA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowD.x, this->lowD.y), ImVec2(this->highA.x, this->highA.y), ImVec2(this->lowA.x, this->lowA.y), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowD_valid && this->highD_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highD.x, this->highD.y), ImVec2(this->lowD.x, this->lowD.y), ImVec2(this->highA.x, this->highA.y), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->highA_valid && this->highB_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA.x, this->highA.y), ImVec2(this->highB.x, this->highB.y), ImVec2(this->highC.x, this->highC.y), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->highA_valid && this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA.x, this->highA.y), ImVec2(this->highB.x, this->highB.y), ImVec2(this->highD.x, this->highD.y), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowA_valid && this->lowB_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA.x, this->lowA.y), ImVec2(this->lowB.x, this->lowB.y), ImVec2(this->lowC.x, this->lowC.y), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowA_valid && this->lowB_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA.x, this->lowA.y), ImVec2(this->lowB.x, this->lowB.y), ImVec2(this->lowD.x, this->lowD.y), IM_COL32(col[0], col[1], col[2], col[3]));
}

bool cg::WorldToScreen(const fvec3& location, ivec2* out)
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
std::optional<ivec2> cg::WorldToScreen(const fvec3& location)
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
		return std::nullopt;
	}
	ivec2 out;

	out.x = centerX * (1 - (vTransform.x / refdef->tanHalfFovX / vTransform.z));
	out.y = centerY * (1 - (vTransform.y / refdef->tanHalfFovY / vTransform.z));
	

	if (vTransform.z > 0)
		return out;

	return std::nullopt;
}
void cg::CG_DrawCoordinates()
{
	char buff[256];
	//if (tas->ui.editing) {

	//	const auto frame = tas->movement.get_frame_data(tas->movement.frame_index);

	//	if (!frame)
	//		return;

	//	sprintf_s(buff, "x:     %.6f\ny:     %.6f\nz:     %.6f\nyaw: %.6f", frame->origin.x, frame->origin.y, frame->origin.z, frame->viewangles.y);

	//	r::R_DrawTextWithEffects(buff, "fonts/normalfont", 0, 400, 1.25f, 1.25f, 0, vec4_t{ 0,1,0,1 }, 3, vec4_t{ 0,0,0,1 });
	//	return;

	//}
	auto ps = predictedPlayerState;
	auto cmd = input->GetUserCmd(input->cmdNumber - 1);
	if (!ps || !cmd)
		return;

	//sprintf_s(buff, "x:     %.6f\ny:     %.6f\nz:     %.6f\nyaw: %.6f\ntime: %d\nwtime: %d\ndelay: %d", ps->origin[0], ps->origin[1], ps->origin[2], ps->viewangles[1], cmd->serverTime, ps->weaponTime, ps->weaponDelay);
	sprintf_s(buff, "%.6f\n%.6f\n%.6f\n%.6f\n%d", ps->origin[0], ps->origin[1], ps->origin[2], ps->viewangles[1], (int)(fvec2(ps->velocity[0], ps->velocity[1]).mag()));

	r::R_DrawTextWithEffects(buff, "fonts/normalfont", 0, 50, 1.25f, 1.25f, 0, vec4_t{ 1,1,1,0.7f }, 3, vec4_t{ 1,0,0,0 });



}
void cg::CG_DrawVelocity()
{
	char buff[32];
	if (tas->ui.editing) {

		const auto frame = tas->movement.get_frame_data(tas->movement.frame_index);

		if (!frame)
			return;

		sprintf_s(buff, "%i", (int)(fvec2(frame->velocity.x, frame->velocity.y).mag()));

		r::R_DrawTextWithEffects(buff, "fonts/objectivefont", refdef->width / 2 - strlen(buff) * 2, refdef->height / 2, 1.f, 1.f, 0, vec4_t{ 1,1,1,1 }, 3, vec4_t{ 1,0,0,1 });
		return;

	}
	auto ps = predictedPlayerState;

	if (!ps)
		return;

	sprintf_s(buff, "%i", (int)(fvec2(ps->velocity[0], ps->velocity[1]).mag()));
	r::R_DrawTextWithEffects(buff, "fonts/objectivefont", refdef->width/2-strlen(buff)*2, refdef->height / 2, 1.f, 1.f, 0, vec4_t{1,1,1,1}, 3, vec4_t{1,0,0,1});


}
void cg::CG_DrawPlayback()
{

	if (tas->movement.recorder) {
		if (tas->movement.recorder->IsPlayback()) {

			auto current = tas->movement.recorder->CurrentCmd();
			
			if (current && cg::predictedPlayerState) {
				float dist = current->origin.dist(cg::predictedPlayerState->origin);

				char buff[64];

				sprintf_s(buff, "%.6f\ntime: %d",dist, current->serverTime);
				r::R_DrawTextWithEffects(buff, "fonts/objectivefont", refdef->width / 1.5f - strlen(buff) * 2, refdef->height / 1.5f, 1.f, 1.f, 0, vec4_t{ 1,1,1,1 }, 3, vec4_t{ 1,0,0,1 });


				//ImGui::GetBackgroundDrawList()->AddText(ImVec2(1600, 800), 0xFFFFFFFF, std::format("sync: {:.6f}\n{:.6f}", dist, current->camera_yaw).c_str());
			}
		}
	}
}
void cg::CG_DrawSnapshot()
{
	auto ps = predictedPlayerState;
	char buff[128];
	if (!ps)
		return;

	sprintf_s(buff, "cmdTime: %i\npTime: %i\n%i", input->GetUserCmd(input->cmdNumber-1)->serverTime, predictedPlayerState->commandTime, cg::PM_GetSprintLeft(ps, input->GetUserCmd(input->cmdNumber)->serverTime));
	r::R_DrawTextWithEffects(buff, "fonts/normalfont", 0, float(refdef->height) / 1.2f, 1.25f, 1.25f, 0, vec4_t{1,1,1,0.7f}, 3, vec4_t{1,0,0,0});
}
void cg::CG_StaminaBar()
{
	const auto ps = predictedPlayerState;
	if (!ps)
		return;

	const int max_time = std::clamp(int(Dvar_FindMalleableVar("player_sprintTime")->current.value * 1000.0f * BG_WeaponNames[ps->weapon]->sprintDurationScale), 0, 0x3fff);
	const int time_left = PM_GetSprintLeft(ps, input->GetUserCmd(input->cmdNumber)->serverTime);

	const float remaining = float(time_left) / float(max_time);
	const float width = (200.f * remaining);

	r::R_DrawRect("white", refdef->width/2-100, refdef->height - 10, width, 10, vec4_t{1.f - remaining, 0.f + remaining,0,1});
	r::R_DrawRect("white", refdef->width / 2-100 +width, refdef->height-10, 200.f - width, 10, vec4_t{ 0,0,0,1 });

}
void cg::CG_CalibrationRequired()
{
	if (tas->movement.calibration_required.empty())
		return;

	const char* str = "Calibration required";
	const int center_x = refdef->width / 2 - (strlen(str)*5);
	const int y = refdef->height - 90;


	r::R_DrawTextWithEffects(str, "fonts/normalfont", center_x, y, 2.f, 2.f, 0, vec4_t{ 1,1,1,1 }, 3, vec4_t{ 1,0,0,0 });

}