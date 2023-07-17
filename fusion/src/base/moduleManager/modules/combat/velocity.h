#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>

struct Velocity
{
	inline static int bind;

	inline static bool Enabled = false;

	inline static float Horizontal = 0.f;

	inline static float Vertical = 1.0f;

	inline static float Chance = 100;

	inline static bool onlyMoving = false;

	static void Update();

	static void RenderMenu();
};

