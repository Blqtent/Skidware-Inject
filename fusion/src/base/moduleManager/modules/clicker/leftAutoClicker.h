#pragma once
#include "../../module.h"
struct LeftAutoClicker
{
	inline static int bind = 0;

	inline static bool Enabled = false;

	inline static float leftMaxCps = 14;
	inline static float leftMinCps = 8;
	inline static bool ignoreBlocks = true;
	inline static bool blockhit = false;
	inline static float blockHitChance = 3.f;
	inline static bool inInventory = false;

	static void Update();
	static void RenderMenu();
};

