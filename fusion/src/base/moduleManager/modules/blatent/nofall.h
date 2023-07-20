#pragma once
#include "../../commonData.h"
struct Nofall
{
	inline static int bind = 0;

	inline static bool Enabled = false;
	inline static float speed = 1.0f;
	inline static int mode = 0;
	inline static const char* modes[3]{ "Normal" };
	static void Update();
	static void RenderMenu();
};

