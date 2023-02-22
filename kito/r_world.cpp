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