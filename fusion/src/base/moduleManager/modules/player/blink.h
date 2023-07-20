#pragma once
#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../module.h"
struct Blink
{
	inline static int bind = 'H';
	inline static float Milliseonds = 3000;

	inline static bool Enabled = false;

	static void Update();

	static void RenderMenu();
	static void onPacketSend();
	static void RenderUpdate();
};
