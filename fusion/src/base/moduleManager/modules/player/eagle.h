#pragma once
#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../module.h"
struct Eagle : public module
{
	inline static int bind = 'Y';

	inline static bool Enabled = false;

	static void Update();

	static void RenderMenu();
};

