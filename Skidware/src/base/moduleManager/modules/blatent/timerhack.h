#pragma once
#include "../../commonData.h"
class TimerHack : public AbstractModule
{
public:
	static TimerHack* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	inline static float speed = 2.0f;
	inline static float speed2 = 0.01f;
	inline static float boostTicks = 10;
	inline static int mode = 0;
	inline static const char* modes[5]{ "Normal", "Tickbase", "Boost", "Bypass"};

private:
	TimerHack();
};

