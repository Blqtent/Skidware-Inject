#pragma once
#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../module.h"
struct Fullbright
{
	inline static int bind;

	inline static bool Enabled = false;

	inline static bool justToggled = false;

	static void Update();

	static void RenderMenu();
private:
	static float oldGamma;
};

