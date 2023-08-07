#pragma once
#include "../../../util/math/geometry.h"

#include "../../module.h"

#include <string>
#include <vector>

struct Velocity : public module
{
	inline static int bind = 0;

	inline static bool Enabled = false;

	inline static float Horizontal = 0.f;

	inline static float Vertical = 1.0f;

	inline static int mode = 0;
	inline static const char* modes[3]{ "Normal", "Intave", "Push"};

	static void Update();

	static void RenderMenu();
};

