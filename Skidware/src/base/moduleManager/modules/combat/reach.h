#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <string>
#include <vector>
#include "../../../sdk/sdk.h"
//struct Reach : public module
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//
//	inline static float ReachDistance = .5f;
//
//	static void Update();
//
//	static void RenderMenu();
//};

class Reach :public AbstractModule {
public:
	static Reach* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	std::vector<Vector3> prev;
	float ReachDistance = .5f;
	float tick = 4;
	inline static int mode = 0;
	inline static const char* modes[5]{ "Gasper", "Backtrack", "Normal"};
	CEntityPlayer target;
	long long dist = 99999999999999999;
	bool blatent = true;
	bool bypass = true;
	long long ticks = 0;
	float ms = 0;
	float prev_reach = -1.0f;

private:
	Reach();
};