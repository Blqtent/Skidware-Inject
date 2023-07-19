#pragma once
#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../module.h"
struct Fastplace : public module
{
	inline static int bind = 0;

	inline static bool Enabled = false;

	inline static float delay = 0;

	static void Update();

	static void RenderMenu();
};

