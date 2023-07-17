#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../module.h"
struct Reach
{
	inline static int bind;

	inline static bool Enabled = false;

	inline static float ReachDistance = .5f;

	static void Update();

	static void RenderMenu();
};

