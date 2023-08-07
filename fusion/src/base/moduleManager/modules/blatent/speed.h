#pragma once
#include "../../commonData.h"
struct Speed
{
	inline static int bind = 0;

	inline static bool Enabled = false;

	inline static float speed = 1.18f;
	inline static float maxspeed = 0.9f;
	inline static int mode = 0;
	inline static const char* modes[5]{ "Normal", "Legit", "Ground", "YPort"};

	static void Update();
	static void RenderMenu();
};

