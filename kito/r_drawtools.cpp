#include "pch.h"

void r::CG_AdjustFrom640(float& x, float& y, float& w, float& h)
{
	const float scale = (float)cg::refdef->width / 640.f;

	x *= scale;
	y *= scale;
	w *= scale;
	h *= scale;
}
Material* r::R_RegisterMaterial(const std::string& mtl)
{
	return ((Material * (*)(const char* mtl, int size))0x5D5DF0)(mtl.c_str(), mtl.size());
}
Font_s* r::R_RegisterFont(const std::string& fontname)
{
	return ((Font_s * (*)(const char* fontname, int size))0x5D5230)(fontname.c_str(), fontname.size());

}
char* __cdecl r::R_AddCmdDrawText(const char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style)
{
	const static uint32_t R_AddCmdDrawText_func = 0x5DB7B0;
	__asm
	{
		push	style;
		sub     esp, 14h;
		fld		rotation;
		fstp[esp + 10h];
		fld		yScale;
		fstp[esp + 0Ch];
		fld		xScale;
		fstp[esp + 8];
		fld		y;
		fstp[esp + 4];
		fld		x;
		fstp[esp];
		push	font;
		push	maxChars;
		push	text;
		mov		ecx, [color];
		call	R_AddCmdDrawText_func;
		add		esp, 24h;
	}
}
void r::R_AddCmdDrawTextWithEffects(char* text, Font_s* font, float x, float y, float xScale, float yScale, float rotation, float* color,
	int style, float* glowColor, Material* fxMaterial, Material* fxMaterialGlow, int fxBirthTime,
	int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	const static uint32_t R_AddCmdDrawTextWithEffects_f = 0x5DB9E0;

	return ((void(__cdecl*)(char* text, Font_s * font, float x, float y, float xScale, float yScale, float rotation, float* color,
		int style, float* glowColor, Material * fxMaterial, Material * fxMaterialGlow, int fxBirthTime,
		int fxLetterTime, int fxDecayStartTime, int fxDecayDuration))R_AddCmdDrawTextWithEffects_f)(text, font, x, y, xScale, yScale, rotation, color,
			style, glowColor, fxMaterial, fxMaterialGlow,
			fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);
}
void r::R_DrawTextWithEffects(const std::string& text, const char* fontname, float x, float y, float xScale, float yScale, float rotation, float* color, int style, float* glowColor)
{
	auto font = R_RegisterFont(fontname);

	Material* fxMaterial = r::R_RegisterMaterial("decode_characters");
	Material* fxMaterialGlow = r::R_RegisterMaterial("decode_characters_glow");

	if (!font || !fxMaterial || !fxMaterialGlow)
		return;

	//CG_AdjustFrom640(x, y, xScale, yScale);
	return R_AddCmdDrawTextWithEffects((char*)text.c_str(), font, x, y, xScale, yScale, rotation, color, style, glowColor, fxMaterial, fxMaterialGlow, 0, 500, 1000, 2000);
}
void r::R_DrawText(const std::string& text, const char* fontname, float x, float y, float xScale, float yScale, float rotation, vec4_t color, int style)
{
	auto font = R_RegisterFont(fontname);

	if (!font)
		return;

	//CG_AdjustFrom640(x, y, xScale, yScale);
	R_AddCmdDrawText(text.c_str(), text.size(), font, x, y, xScale, yScale, rotation, color, style);

}
void r::R_AddCmdDrawStretchPic(Material* material, float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* color)
{
	const static uint32_t R_AddCmdDrawStretchPic_func = 0x5DB2A0;
	__asm
	{
		pushad;
		push	color;
		mov		eax, [material];
		sub		esp, 20h;
		fld		t1;
		fstp[esp + 1Ch];
		fld		s1;
		fstp[esp + 18h];
		fld		t0;
		fstp[esp + 14h];
		fld		s0;
		fstp[esp + 10h];
		fld		h;
		fstp[esp + 0Ch];
		fld		w;
		fstp[esp + 8h];
		fld		y;
		fstp[esp + 4h];
		fld		x;
		fstp[esp];
		call	R_AddCmdDrawStretchPic_func;
		add		esp, 24h;
		popad;
	}
}
void r::R_DrawRect(const char* material, float x, float y, float w, float h, const float* color)
{
	//CG_AdjustFrom640(x, y, w, h);
	Material* mat = R_RegisterMaterial(material);
	R_AddCmdDrawStretchPic(mat, (x), (y), (w), (h), 0, 0, 0, 0, color);


}