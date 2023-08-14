#pragma once
#include "../../AbstractModule.h"
#include "../../../eventManager/events/EventUpdate.hpp"
//struct RightAutoClicker : public module
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//
//	inline static float rightMaxCps = 20;
//	inline static float rightMinCps = 15;
//	inline static bool blocksOnly = true;
//
//	static void Update();
//	static void RenderMenu();
//};

class RightAutoClicker :public AbstractModule {
public:
	static RightAutoClicker* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	float rightMaxCps = 14;
	float rightMinCps = 8;
	bool ignoreBlocks = true;
	bool blockhit = false;
	bool blocksOnly = true;
	float blockHitChance = 3.f;
	bool inInventory = false;
private:
	RightAutoClicker();
};