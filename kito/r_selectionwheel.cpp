#include "pch.h"

SWheel::SWheel(const ivec2 _ref, std::list<WheelObj> _objects, float _radius)
{	
	Init(_ref, _objects, _radius);
}
void SWheel::Init(const ivec2 _reference_point, std::list<WheelObj> _objects, float _radius)
{
	ref = _reference_point;
	objects = _objects;
	radius = _radius;
	if (!(items = objects.size())) {
		Com_Error(ERR_DROP, "SWheel::SWheel(): empty list of objects");
		return;
	}



}
void SWheel::Init(const ivec2 _reference_point, float _radius)
{
	ref = _reference_point;
	radius = _radius;
}
void SWheel::OnBlurEvent()
{
	static float blurAmount = 0.f;
	static float blur_t = 0.f;
	constexpr float MAX_BLUR = 5.f;

	static dvar_s* blur = Dvar_FindMalleableVar("r_blur");

	

	if (keyheld) {
		blurAmount = std::lerp(0.f, MAX_BLUR, std::clamp(keyduration*3, 0.f, 1.f));
		blur->current.value = blurAmount;
		blur_t = 1;
	}
	else if(blur->current.value != NULL && blur_t >= 0.f) {
		blurAmount =  std::lerp(0.f, MAX_BLUR, blur_t);
		blur->current.value = blurAmount;
		blur_t -= 0.01f;
	}

}
void SWheel::OnKeyEvent()
{
	if ((keyduration = ImGui::GetIO().KeysDownDuration['B']) >= 0.0f && keyduration <= ImGui::GetIO().DeltaTime) { //key just pressed
		ImGui::GetIO().MouseDrawCursor = true;
		keyheld = true;
		IN_ActivateMouse(false);
		UI_SetSystemCursorPos(320, 240); //centered

		SWheel::Init(ivec2{ int(cg::refdef->width / 2), int(cg::refdef->height / 2)}, 256);
		SWheel::Insert("+gostand", []() { Com_Printf(CON_CHANNEL_SUBTITLE, "jumping..."); Cbuf_AddText("+gostand; wait; wait; -gostand;\n", 0); }, { 255,0,0,120 }, nullptr);
		SWheel::Insert("noclip", []() { Com_Printf(CON_CHANNEL_SUBTITLE, "noclip!"); Cbuf_AddText("noclip\n", 0); }, { 0,255,0,120 }, nullptr);
		SWheel::Insert("die", []() { Com_Printf(CON_CHANNEL_SUBTITLE, "kill!"); Cbuf_AddText("kill\n", 0); },	{ 0,0,255,120 }, nullptr);

		return;
	}

	else if (keyduration < 0 && keyheld) {
		keyheld = false;
		ImGui::GetIO().MouseDrawCursor = false;
		IN_ActivateMouse(true);
		UI_SetSystemCursorPos(320, 240); //centered
		if (lastSelected)
			lastSelected->action();

		SWheel::EraseAll();
	}

	else if ((keyduration = ImGui::GetIO().KeysDownDuration[VK_OEM_PLUS]) >= 0.0f && keyduration <= ImGui::GetIO().DeltaTime)
	{
		static int i = 0;
		std::string ok = std::string("what") + std::to_string(i++);
		SWheel::Insert(ok, []() { Com_Printf(CON_CHANNEL_SUBTITLE, "lol..\n"); }, {uint8_t(rand() % 255),uint8_t(rand() % 255),uint8_t(rand() % 255),120}, nullptr);

	}
	else if ((keyduration = ImGui::GetIO().KeysDownDuration[VK_OEM_MINUS]) >= 0.0f && keyduration <= ImGui::GetIO().DeltaTime)
	{
		if(!objects.empty())
			objects.pop_front();
	}
}
void SWheel::Draw()
{

	SWheel::OnKeyEvent();
	SWheel::OnBlurEvent();

	if (!keyheld)
		return;

	SWheel::OnDrawWheel();

	mpos = GetCPos();
	angle = VectorAngle(ref, mpos) + 90; 

	if (angle < 0) {
		angle += 180;
		angle = (angle + 180 % 360);
	}

	ImGui::GetBackgroundDrawList()->AddLine(ref, GetCPos(), 0xFFFFFFFF, 2.f);

}

void SWheel::OnDrawWheel()
{


	if (objects.size() < 2) {
		Com_Error(ERR_DROP, "SWheel::OnDrawWheel(): objects.size() < 2");
		return;
	}

	float angle = 0;
	width = 360.f / objects.size();

	for (auto& i : objects) {

		DrawSingularPoly(i, angle+1);
		
		angle += width;
	}
	angle = 0;
	for (auto& i : objects) {

		DrawSingularOutline(i, angle + 1);

		angle += width;
	}
	//ImGui::GetBackgroundDrawList()->AddCircleFilled(ref, 10, Pixel{ 0,0,0,255 });
}
void SWheel::DrawSingularPoly(WheelObj& obj, float start_angle)
{

	ivec2 tri[3];

	tri[0] = ref;

	tri[1] = { 
			ref.x + int(sin((start_angle) * PI / 180) * radius), 
			ref.y - int(cos((start_angle) * PI / 180) * radius) };

	tri[2] = {
		ref.x + int(sin((start_angle+width)*PI / 180) * radius),
		ref.y - int(cos((start_angle+width)*PI / 180) * radius) };


	if (angle >= start_angle && angle <= start_angle + width && mpos != ref) {
		obj.color.r = 100;
		obj.color.g = 200;
		obj.color.b = 0;
		obj.color.a = 255;
		lastSelected = &obj;
	}
	else {
		obj.color.r = 25;
		obj.color.g = 23;
		obj.color.b = 27;
		obj.color.a = 200;
	}
	ivec2 center = { (tri[0] + tri[1]+ tri[2]) / 3};
	float maxWidth = std::min({ tri[1].x - tri[0].x, tri[2].x - tri[0].x, tri[1].x - tri[2].x });

	auto size = ImGui::CalcTextSize(obj.display_text.c_str());

	

	center.x -= size.x / 2;
	center.y -= size.y / 2;



	ImGui::GetBackgroundDrawList()->AddTriangleFilled(tri[0], tri[1], tri[2], obj.color);

	ImGui::GetBackgroundDrawList()->AddText(center, 0xFFFFFFFF, obj.display_text.c_str());

}
void SWheel::DrawSingularOutline(WheelObj& obj, float start_angle)
{
	ivec2 tri[3];


	tri[0] = ref;
	tri[2] = {
	ref.x + int(sin((start_angle + width) * PI / 180) * radius * 1.1f),
	ref.y - int(cos((start_angle + width) * PI / 180) * radius * 1.1f) };

	float angle = -VectorAngle(ref, tri[2]);

	const float left = angle - 90;
	const float right = left - 90;


	//tri[0] = {
	//ref.x + int(sin((left) * PI / 180) * 10),
	//ref.y - int(cos((left) * PI / 180) * 10) };

	//tri[1] = {
	//	ref.x + int(sin((right) * PI / 180) * 10),
	//	ref.y - int(cos((right) * PI / 180) * 10) };


	//ImGui::GetBackgroundDrawList()->AddTriangle(tri[0], tri[1], tri[2], Pixel{ 0,0,0,255 });
	ImGui::GetBackgroundDrawList()->AddLine(tri[0], tri[2], Pixel{ 25,200,0,255 }, 3);

}