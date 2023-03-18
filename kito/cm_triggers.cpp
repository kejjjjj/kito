#include "pch.h"


void cg::ShowBrush_f()
{

	if (cmd_args->argc[cmd_args->nesting] != 2) {
		if(!show_all_triggers)
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "usage: showbrush <material>");
		show_all_triggers = false;

		return;
	}
	auto name = *(cmd_args->argv[cmd_args->nesting] + 1);
	show_all_triggers = true;

	if (show_all_triggers) {
		brushes.clear();
		auto b = &cg::cm->brushes[0];
		for (int j = 0; j < cm->numBrushes; j++) {

			for (int x = 0; x < 1; x++) {
				for (int y = 0; y < 3; y++) {
					if (std::string(cm->materials[b->axialMaterialNum[x][y]].material).find(name) != std::string::npos) {
						brushes.push_back(b);
						//std::cout << "yep! [" << j << "]\n";
						goto end;
					}
				}
			}
			if (b->numsides) {
				if (std::string(cm->materials[b->sides[0].materialNum].material).find(name) != std::string::npos) {
					brushes.push_back(b);
					//std::cout << "yep! [" << j << "]\n";
				}
			}
			end:
			++b;
		}
	}

	std::cout << "total trigger brushes: " << brushes.size() << '\n';
	std::cout << "triggers: " << cm->mapEnts->trigger.count << '\n';
}
void cg::CM_GetBrushOriginFromBounds(const cbrush_t* brush, vec3_t out)
{
	for (int i = 0; i < 3; i++)
		out[i] = brush->mins[i] + (brush->maxs[i] - brush->mins[i]) / 2;
}
void cg::CM_DrawBrush(const cbrush_t* b)
{
	if (!b)
		return;

	vec3_t org, mins, maxs;
	CM_GetBrushOriginFromBounds(b, org);

	VectorSubtract(b->maxs, org, maxs);
	VectorSubtract(b->mins, org, mins);

	mins[0] = mins[0] < 0 ? -mins[0] : mins[0];
	mins[1] = mins[1] < 0 ? -mins[1] : mins[1];
	mins[2] = mins[2] < 0 ? -mins[2] : mins[2];

	const auto ps = cg::predictedPlayerState;

	if (!ps)
		return;

	if (fvec3(ps->origin).dist(org) > 1000)
		return;

	const box_s box(org, mins, maxs);

	box.R_DrawConstructedBox(vec4_t{ 0,255,0,55 });
	box.R_DrawConstructedBoxEdges(vec4_t{ 0,255,0,255 });
}