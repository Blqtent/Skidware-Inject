#pragma once
#include "eventManager/events/EventKey.hpp"
struct Base
{
	static void Init();
	static void initEvent();
	static void initModule();
	static void handleEventKey(const EventKey k);
	static void Kill();

	/*static void CheatLoop();*/
	static void RenderLoop();

	static inline bool Running;
	static inline bool justPressed;

	//1 = Lunar, 2 = Forge, 3 = Vanilla/Badlion

};

