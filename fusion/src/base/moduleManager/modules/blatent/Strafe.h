#pragma once
#include "../../commonData.h"
struct Strafe
{
	inline static int bind = 0;

	inline static bool Enabled = false;

	inline static float speed = 1.0f;
	inline static int mode = 0;
	inline static const char* modes[3]{ "Normal", "Legit", "Vulcan" };

	static void Update();
	static void RenderMenu();
};

