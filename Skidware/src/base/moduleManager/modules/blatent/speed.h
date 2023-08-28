#pragma once
#include "../../commonData.h"
//struct Speed
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//
//	inline static float speed = 1.18f;
//	inline static float maxspeed = 0.9f;
//	inline static int mode = 0;
//	inline static const char* modes[5]{ "Normal", "Legit", "Ground", "YPort"};
//
//	static void Update();
//	static void RenderMenu();
//};

class Speed :public AbstractModule {
public:
	static Speed* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	const char* modes[5]{ "Normal", "Legit", "Ground", "YPort", "Watchdog"};
	float speed = 1.18f;
	float maxspeed = 0.9f;
private:
	Speed();
};