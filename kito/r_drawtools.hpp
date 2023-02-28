#pragma once

#ifndef drawtools
#define drawtools

#include "pch.h"

namespace r {
	void CG_AdjustFrom640(float& x, float& y, float& w, float& h);

	Material* R_RegisterMaterial(const std::string& mtl);
	Font_s* R_RegisterFont(const std::string& fontname);

	char* __cdecl R_AddCmdDrawText(const char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
	void R_DrawText(const std::string& text, const char* fontname, float x, float y, float xScale, float yScale, float rotation, vec4_t color, int style);

	void R_AddCmdDrawTextWithEffects(char* text, Font_s* font, float x, float y, float xScale, float yScale, float rotation, float* color, 
		int style, float* glowColor, Material* fxMaterial, Material* fxMaterialGlow, int fxBirthTime, 
		int fxLetterTime, int fxDecayStartTime, int fxDecayDuration); //holy this takes a lot of args

	void R_DrawTextWithEffects(const std::string& text, const char* fontname, float x, float y, float xScale, float yScale, float rotation, float* color, int style, float* glowColor);

}
#endif