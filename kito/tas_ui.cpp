#include "pch.h"

void TAS_UI::UI_Render()
{
	//no existing project
	if (!draw_save_list && (tas->filesystem.empty() || tas->movement.waiting_for_creation)) {

		static bool bName = false;
		static std::string sName;
		if (bName) {

			ImGui::Begin("Project Name", 0, ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::InputText("##044", &sName);
			
			if (ImGui::ButtonCentered("OK##02")) {
				bName = false;

				TAS_FileSystem fs(sName);

				if (fs.valid) {
					tas->filesystem.push_back(fs);
					tas->cfile = std::make_unique<TAS_FileSystem>(tas->filesystem.back());
					Com_Printf(CON_CHANNEL_SUBTITLE, "tas->cfile->display_name = %s\n", tas->cfile->display_name.c_str());
					tas->movement.waiting_for_creation = true;
				}

			}
			ImGui::SameLine();
			if (ImGui::ButtonCentered("Cancel##02")) {
				bName = false;
			}
			ImGui::End();
			return;
		}

		if (ImGui::ButtonCentered("Create Project") && !tas->movement.waiting_for_creation) { //the 2nd condition could cause memory bugs if it wasn't there
			bName = true;
			return;

		}ImGui::Text("or ");

		if (ImGui::ButtonCentered("Load Project")) {
			tas->ui.savelist = std::unique_ptr<SaveList>(new SaveList);
			draw_save_list = true;
		}

		return;
	}
	else if (draw_save_list) {
		
		if (auto file = savelist->UI_SaveList()) {

			savelist->input = std::unique_ptr<TAS_FileSystem_In>(new TAS_FileSystem_In(file.value()));
			const auto movement = savelist->input->read();

			if (movement) {

				const auto filename = fs::F_GetFileName(file.value());
				const auto extension = fs::GetFileExtension(filename);
				const std::string shortname = (filename.substr(0, filename.size() - extension.size()));

				TAS_FileSystem fs(shortname);

				if (fs.valid) {
					tas->filesystem.push_back(fs);
					tas->cfile = std::make_unique<TAS_FileSystem>(tas->filesystem.back());
					Com_Printf(CON_CHANNEL_SUBTITLE, "tas->cfile->display_name = %s\n", tas->cfile->display_name.c_str());

					tas->movement = *movement->get();
					tas->movement.update_movement_for_each_segment();
					tas->movement.set_current_segment(0);
				}
			}
			delete savelist->input.release();
			delete tas->ui.savelist.release();
			draw_save_list = false;
		}

		if (ImGui::ButtonCentered("Cancel")) {
			draw_save_list = false;
			delete tas->ui.savelist.release();
		}

		return;
	}

	TAS_UI::UI_SegmentEditor();
	TAS_UI::UI_FrameEditor();
	TAS_UI::UI_OtherControls();
	TAS_UI::UI_SelectWeapon();
	TAS_UI::UI_HoldButtons();

	ImGui::NewLine();

	//auto frame = tas->movement.get_frame_data(tas->movement.frame_index);

	//ImGui::Text("events: %i,%i,%i,%i", frame->events[0], frame->events[1], frame->events[2], frame->events[3]);
	//ImGui::Text("velocity: %i", (int)(fvec2(frame->velocity.x, frame->velocity.y).mag()) );
	TAS_UI::UI_FileSystem();


}
std::optional<std::string> SaveList::UI_SaveList()
{
	if (!exists) {
		ImGui::TextCentered("No files available!");
		return std::nullopt;
	}

	ImVec2 mins, maxs, size = ImGui::GetWindowSize(), pos = ImGui::GetWindowPos();
	bool clicked = ImGui::GetIO().MouseClicked[0];
	int idx = 0;
	for (const auto& i : filenames) {
		ImGui::Text(i.c_str());

		mins = ImVec2(pos.x, ImGui::GetItemRectMin().y);
		maxs = ImVec2(pos.x + size.x, ImGui::GetItemRectMax().y);

		if (MouseHovered(mins, maxs)) {
			ImGui::GetForegroundDrawList()->AddRectFilled(mins, maxs, IM_COL32(255, 200, 157, 157), ImGui::GetStyle().FrameRounding);
			if (clicked) {
				return fullnames[idx];
			}
		}
		idx++;
	}

	return std::nullopt;

}
void TAS_UI::UI_SegmentEditor()
{
	static DWORD ms = 0;

	auto cur_seg = tas->movement.request_current_segment();
	if (!cur_seg) {
		Com_Error(ERR_DROP, "tas->movement.request_current_segment() == nullptr");
		return;
	}

	ImGui::PushItemWidth(350);
	if (ImGui::SliderInt_22("Segment", &tas->movement.segment_index, 0, tas->movement.get_segment_count()-1)) {
		tas->movement.set_current_segment(tas->movement.segment_index);
		//tas->movement.frame_index = cur_seg->start_index;
	}
	ImGui::SameLine();

	if (auto font = tas->FetchFont("font90"))
		ImGui::SetCurrentFont(font.value());

	ImGui::Button("]##01", ImVec2(40, 40));
	if (ImGui::IsItemActive()) {
		if (tas->movement.segment_index - 1 > 0 && ms + 100 < Sys_Milliseconds()) {
			tas->movement.segment_index--;
			ms = Sys_Milliseconds();
			tas->movement.set_current_segment(tas->movement.segment_index);

		}
	}
	ImGui::SameLine();
	ImGui::Button("[##01", ImVec2(40, 40));
	if (ImGui::IsItemActive()) {
		if (tas->movement.segment_index + 1 < tas->movement.get_segment_count() && ms + 100 < Sys_Milliseconds()) {
			tas->movement.segment_index++;
			ms = Sys_Milliseconds();
			tas->movement.set_current_segment(tas->movement.segment_index);
		}
	}

	if (auto font = tas->FetchFont("conduit"))
		ImGui::SetCurrentFont(font.value());

	if (ImGui::Button("Add")) {
		tas->movement.add_segment();
		cur_seg = tas->movement.request_current_segment();

	}
	ImGui::SameLine(); 
	if (ImGui::Button("Insert")) {
		tas->movement.insert_segment();
		cur_seg = tas->movement.request_current_segment();

	}
	ImGui::SameLine(); 
	if (cur_seg->segment_index == 0)
		ImGui::BeginDisabled();
	if (ImGui::Button("Remove Selected"))
		tas->movement.delete_segment();
	if (cur_seg->segment_index == 0)
		ImGui::EndDisabled();
	ImGui::NewLine();
	//ImGui::Separator();




}
void TAS_UI::UI_FrameEditor()
{
	static DWORD ms = 0;

	static int add_or_remove_frames_count = 100;
	auto cur_seg = tas->movement.request_current_segment();
	
	ImGui::PushItemWidth(325);
	ImGui::SliderInt_22("Frame", &tas->movement.frame_index, 0, tas->movement.get_frame_count());


	if (auto font = tas->FetchFont("font90"))
		ImGui::SetCurrentFont(font.value());

	ImGui::SameLine();
	ImGui::Button("]##02", ImVec2(40,40));
	if (ImGui::IsItemActive()) {
		if (tas->movement.frame_index > 0 && ms + 100 < Sys_Milliseconds()) {
			tas->movement.frame_index--;
			ms = Sys_Milliseconds();
		}
	}
	ImGui::SameLine();
	ImGui::Button("[##02", ImVec2(40, 40));
	if (ImGui::IsItemActive()) {
		if (tas->movement.frame_index + 1 < tas->movement.get_last_segment()->end_index && ms + 100 < Sys_Milliseconds()) {
			tas->movement.frame_index++;
			ms = Sys_Milliseconds();
		}
	}

	if (auto font = tas->FetchFont("conduit"))
		ImGui::SetCurrentFont(font.value());

	if(tas->movement.player_pov)
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.f, 0.f, 0.f, 0.7f);

	ImGui::SameLine();
	if (ImGui::Button("POV##02", ImVec2(50, 40)))
		tas->movement.player_pov = !tas->movement.player_pov;

	ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(30.f / 255, 30.f / 255, 41.f / 255, 1.f);


	ImGui::PushItemWidth(130);
	ImGui::InputInt("Count", &add_or_remove_frames_count, 1, 100);

	ImGui::SameLine();
	if (ImGui::Button("Add##01"))
		tas->movement.add_frames_to_current_segment(add_or_remove_frames_count);

	ImGui::SameLine();
	if (ImGui::Button("Remove##01"))
		tas->movement.remove_frames_from_current_segment(add_or_remove_frames_count);

	ImGui::NewLine();
	ImGui::Separator();

}
void TAS_UI::UI_OtherControls()
{
	ImGui::BeginGroup();
	auto options = &tas->movement.request_current_segment()->options;
	constexpr const char* viewangle_options[] = {"Fixed turn", "Strafebot", "Aimlock", "Fixed angle"};

	ImGui::PushItemWidth(150);
	if (ImGui::Combo("Angles", &(int&)options->viewangle_type, viewangle_options, IM_ARRAYSIZE(viewangle_options)))
		tas->movement.update_movement_for_each_segment();

	UI_AngleControls_Fixed(options);
	UI_AngleControls_Strafebot(options);
	UI_AngleControls_Aimlock(options);
	UI_AngleControls_FixedAngles(options);


	//if (ImGui::Checkbox2("strafebot", &options->strafebot))
	//	tas->movement.update_movement_for_each_segment();

	//if(ImGui::Checkbox2("bunnyhop", &options->bhop))
	//	tas->movement.update_movement_for_each_segment();

	ImGui::EndGroup();

	UI_ControlsDPAD();

	ImGui::NewLine();

}
void TAS_UI::UI_ControlsDPAD()
{
	

	auto cur_seg = tas->movement.request_current_segment();
	const bool disabled = cur_seg->options.viewangle_type == viewangle_type::STRAFEBOT && cur_seg->options.strafebot.go_straight;
	if (disabled) {
		ImGui::BeginDisabled();
	}

	const auto constructkey = [](char& dir, char value, const char* name) -> void {

		if (dir == value)
			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.f, 0.f, 0.f, 0.7f);

		if (ImGui::Button(name, ImVec2(40,40))) {

			if (dir == value)
				dir = NULL;
			else
				dir = value;

			tas->movement.update_movement_for_each_segment();
		}

		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(30.f / 255, 30.f / 255, 41.f / 255, 1.f);
	};

	ImGui::SameLine();
	ImGui::Text("\t  ");
	ImGui::SameLine();

	ImGui::BeginGroup();
	ImGui::Text("\t   ");
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(0.2f, 0));
	ImGui::SameLine();
	constructkey(cur_seg->options.forwardmove, 127, "W##01");
	constructkey(cur_seg->options.rightmove, -127, "A##01");

	ImGui::SameLine();
	constructkey(cur_seg->options.forwardmove, -127, "S##01");

	ImGui::SameLine();
	constructkey(cur_seg->options.rightmove, 127, "D##01");

	ImGui::EndGroup();

	if (disabled) {
		ImGui::EndDisabled();
	}

	//ImGui::NewLine();
	//ImGui::Separator();

	//ImGui::Text("Debug:\n");

	//ImGui::Text("start: %d", cur_seg->start_index);
	//ImGui::Text("end: %d", cur_seg->end_index);
	//ImGui::Text("frames: %d", cur_seg->frame_count);

}
std::list<ivec2> TAS_UI::SegmentToScreen(const segment_s& segment)
{
	std::list<ivec2> points;
	ivec2 xy;
	for (auto& i : segment.content) {

		if (cg::WorldToScreen(i.origin, &xy)) {
			points.push_back(xy);
		}

	}
	return points;
}
void TAS_UI::UI_AngleControls_Fixed(segment_options* options)
{
	if (options->viewangle_type != viewangle_type::FIXED_TURNRATE)
		return;

	constexpr const char* dir_options[] = { "Left", "Right"};

	ImGui::PushItemWidth(150);
	if (ImGui::InputFloat("Right##01", &options->fixed_turn.right, 0.f, 0.f, "%.3f")) {
		options->fixed_turn.right = std::clamp(options->fixed_turn.right, -180.f, 180.f);
		tas->movement.update_movement_for_each_segment();
	}

	ImGui::PushItemWidth(150);
	if (ImGui::InputFloat("Up##01", &options->fixed_turn.up, 0.f, 0.f, "%.3f")) {
		options->fixed_turn.up = std::clamp(options->fixed_turn.up, -85.f, 85.f);
		tas->movement.update_movement_for_each_segment();
	}



}
void TAS_UI::UI_AngleControls_Strafebot(segment_options* options)
{
	if (options->viewangle_type != viewangle_type::STRAFEBOT)
		return;

	ImGui::PushItemWidth(150);
	if (ImGui::InputFloat("Up##02", &options->strafebot.up, 0.f, 0.f, "%.3f")) {
		options->strafebot.up = std::clamp(options->strafebot.up, -85.f, 85.f);
		tas->movement.update_movement_for_each_segment();
	}
	if (options->strafebot.go_straight) {
		ImGui::PushItemWidth(150);
		if (ImGui::InputInt("Smooth", &options->strafebot.smoothing_window, 1.f, 100.f)) {
			options->strafebot.smoothing_window = std::clamp(options->strafebot.smoothing_window, 0, INT_MAX);
			tas->movement.update_movement_for_each_segment();

		}
	}
	if(ImGui::Checkbox2("Spam##01", &options->strafebot.go_straight))
		tas->movement.update_movement_for_each_segment();

}
void TAS_UI::UI_AngleControls_Aimlock(segment_options* options)
{
	if (options->viewangle_type != viewangle_type::AIMLOCK)
		return;

	ImGui::PushItemWidth(150);
	if (ImGui::InputFloat("X##02", &options->aimlock.target.x, 0.f, 0.f, "%.3f")) {
		tas->movement.update_movement_for_each_segment();
	}ImGui::PushItemWidth(150); 
	if (ImGui::InputFloat("Y##02", &options->aimlock.target.y, 0.f, 0.f, "%.3f")) {
		tas->movement.update_movement_for_each_segment();
	}ImGui::PushItemWidth(150); 
	if (ImGui::InputFloat("Z##02", &options->aimlock.target.z, 0.f, 0.f, "%.3f")) {
		tas->movement.update_movement_for_each_segment();
	}

}
void TAS_UI::UI_AngleControls_FixedAngles(segment_options* options)
{
	if (options->viewangle_type != viewangle_type::FIXED_ANGLES)
		return;

	ImGui::PushItemWidth(150);
	if (ImGui::InputFloat("X##03", &options->fixed_angle.viewangles.x, 0.f, 0.f, "%.3f")) {
		tas->movement.update_movement_for_each_segment();
	}ImGui::PushItemWidth(150);
	if (ImGui::InputFloat("Y##03", &options->fixed_angle.viewangles.y, 0.f, 0.f, "%.3f")) {
		tas->movement.update_movement_for_each_segment();
	}ImGui::PushItemWidth(150);
	if (ImGui::InputFloat("Z##03", &options->fixed_angle.viewangles.z, 0.f, 0.f, "%.3f")) {
		tas->movement.update_movement_for_each_segment();
	}
}
void TAS_UI::UI_SelectWeapon()
{

	auto cur_seg = tas->movement.request_current_segment();
	auto weaplist = cg::G_GetWeaponsList(&cur_seg->end.ps);
	std::vector<const char*> weapons;

	for (auto& [x, y] : weaplist) {
		weapons.push_back(x->szDisplayName+7); //C substr :new_moon_with_face:
	}
	ImGui::PushItemWidth(150);
	if (ImGui::Combo("Weapon##01", &cur_seg->options.iWeapon, weapons.data(), weapons.size())) {
		Com_Printf(CON_CHANNEL_SUBTITLE, "index: %i\n", weaplist[cur_seg->options.iWeapon].second);
		cur_seg->options.weapon = weaplist[cur_seg->options.iWeapon].second;
		tas->movement.update_movement_for_each_segment();
	}
	ImGui::PushItemWidth(150);
	if(ImGui::InputInt("FPS##02", &cur_seg->options.FPS))
		tas->movement.update_movement_for_each_segment();


}

int32_t TAS_UI::UI_HoldButtons()
{

	ImGui::Text("Hold Buttons");

	static bool show_actions = false;

	constexpr int ITEMS_PER_LINE = 5;
	int items = 0;
	int32_t& hold_buttons = tas->movement.request_current_segment()->options.hold_buttons;
	for (auto& [x, y] : cmd_buttons) {
	
		if ((hold_buttons & y) != 0) {
			items++;
			ImGui::Text(x.c_str());

			if ((items % 4 == 0 && items != 0) == false)
				ImGui::SameLine();
		}
	}
	
	if (ImGui::Button("+"))
		show_actions = !show_actions;
	
	const ImVec2 location = ImGui::GetItemRectMax();

	if (show_actions) {
		static ImVec2 mins, maxs, size = ImGui::GetWindowSize(), pos = ImGui::GetWindowPos();

		auto framepadding = ImGui::GetStyle().FramePadding;
		ImGui::Begin("##01", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
		bool clicked = ImGui::GetIO().MouseClicked[0];
		for (auto& [x, y] : cmd_buttons) {

			ImGui::Text(x.c_str());

			mins = ImVec2(pos.x, ImGui::GetItemRectMin().y);
			maxs = ImVec2(pos.x + size.x, ImGui::GetItemRectMax().y);

			if (MouseHovered(mins, maxs)) {
				ImGui::GetForegroundDrawList()->AddRectFilled(mins, maxs, IM_COL32(255, 200, 157, 157), ImGui::GetStyle().FrameRounding);
				if (clicked) {

					((hold_buttons & y) == 0) == true ? 
						hold_buttons += y :
						hold_buttons -= y;

					show_actions = false;

					tas->movement.update_movement_for_each_segment();
				}
			}

			if ((hold_buttons & y) != 0) {
				ImGui::GetForegroundDrawList()->AddRectFilled(mins, maxs, IM_COL32(255, 200, 157, 157), ImGui::GetStyle().FrameRounding);
			}

			if (clicked && show_actions) { //clicked out of frame
				show_actions = false;
			}

		}
		size = ImGui::GetWindowSize(); 
		pos = ImGui::GetWindowPos();
		ImGui::SetWindowPos(ImVec2(location.x + framepadding.x, location.y - framepadding.y * 3 - size.y));

		ImGui::End();

	}
	return 0;
}
int32_t TAS_UI::UI_SpamButtons()
{
	return 0;
}

void TAS_UI::UI_FileSystem()
{
	static std::string file_name;

	ImGui::Separator();

	if (auto font = tas->FetchFont("font90"))
		ImGui::SetCurrentFont(font.value());

	if (ImGui::Button("S##04", ImVec2(30, 30))) {

		tas->TAS_AutoSave();

	}

	if (auto font = tas->FetchFont("conduit"))
		ImGui::SetCurrentFont(font.value());

	ImGui::SameLine();

	ImGui::PushItemWidth(ImGui::GetWindowWidth() / 1.5f);
	ImGui::InputText("##00111", &file_name);

	if (auto font = tas->FetchFont("font90"))
		ImGui::SetCurrentFont(font.value());

	ImGui::SameLine();

	if (ImGui::Button("F##01", ImVec2(30, 30))) {
		tas->movement.frame_index = 0;

	}
	ImGui::SameLine();
	if (ImGui::Button("D##01123", ImVec2(30, 30))) {
		if (auto ps = tas->movement.get_pmove_from_frame(tas->movement.frame_index)) {
			std::cout << "origin: " << fvec3(ps.value()->ps.origin) << '\n';
			tas->movement.overwrite_pmove.first = true;
			tas->movement.overwrite_pmove.second = *ps.value();

		}
		else
			std::cout << "NO!\n";
	}
	ImGui::SameLine();
	if (ImGui::Button("A##012341", ImVec2(30, 30))) {
		tas->movement.frame_index = tas->movement.get_last_segment()->end_index-1;
	}
	if (auto font = tas->FetchFont("conduit"))
		ImGui::SetCurrentFont(font.value());
}