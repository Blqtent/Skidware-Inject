#pragma once
#include "../../module.h"
struct RightAutoClicker
{
	inline static int bind;


	inline static bool Enabled = false;

	inline static float rightMaxCps = 20;
	inline static float rightMinCps = 15;
	inline static bool blocksOnly = true;

	static void Update();
	static void RenderMenu();
};

