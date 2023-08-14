#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <string>
#include <vector>

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

	float ReachDistance = .5f;
private:
	Reach();
};