#pragma once
#include "../../commonData.h"
//struct LongJump
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//	inline static int mode = 0;
//	inline static float speed = 2;
//	inline static const char* modes[5]{ "TNT"};
//	static void Update();
//	static void RenderMenu();
//};
class LongJump :public AbstractModule {
public:
	static LongJump* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	const char* modes[5]{ "TNT", "Polar"};
	float speed = 2;
private:
	LongJump();
};