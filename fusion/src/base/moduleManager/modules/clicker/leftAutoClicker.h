#pragma once
#include "../../AbstractModule.h"
#include "../../../eventManager/events/EventUpdate.hpp"
//struct LeftAutoClicker
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//
//	inline static float leftMaxCps = 14;
//	inline static float leftMinCps = 8;
//	inline static bool ignoreBlocks = true;
//	inline static bool blockhit = false;
//	inline static float blockHitChance = 3.f;
//	inline static bool inInventory = false;
//
//	static void Update();
//	static void RenderMenu();
//};

class LeftAutoClicker :public AbstractModule {
public:
	static LeftAutoClicker* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	float leftMaxCps = 14;
	float leftMinCps = 8;
	bool ignoreBlocks = true;
	bool blockhit = false;
	float blockHitChance = 3.f;
	bool inInventory = false;
private:
	LeftAutoClicker();
};