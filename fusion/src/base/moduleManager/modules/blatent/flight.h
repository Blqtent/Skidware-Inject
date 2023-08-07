#pragma once
#include "../../commonData.h"
struct Flight
{
	inline static int bind = 0;

	inline static bool Enabled = false;
	inline static bool antikick = false;
	inline static int mode = 0;
	inline static float glideSpeed = 0;
	inline static const char* modes[5]{"MotionY", "Airjump"};
	static void Update();
	static void RenderMenu();
};