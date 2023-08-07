#pragma once
#pragma once
#include "../../../util/math/geometry.h"
#include <Windows.h>

#include <string>
#include <vector>
#include "../../module.h"
struct Blink
{
	inline static ULONGLONG timer;
	inline static bool running;
	inline static bool wasActive;
	inline static int bind = 'H';
	inline static float Milliseonds = 10;

	inline static bool Enabled = false;
	//inline static bool throttle = false;

	static void Update();

	static void RenderMenu();
	static void OnReceiveData();
};
