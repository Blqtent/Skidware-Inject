#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../module.h"
struct Reach : public module
{
	inline static int bind = 0;

	inline static bool Enabled = false;

	inline static float ReachDistance = .5f;

	static void Update();

	static void RenderMenu();
};

