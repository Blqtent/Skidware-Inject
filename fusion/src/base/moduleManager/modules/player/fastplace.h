#pragma once
#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <string>
#include <vector>
//#include "../../module.h"
//struct Fastplace : public module
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//
//	inline static float delay = 0;
//
//	static void Update();
//
//	static void RenderMenu();
//};

class Fastplace :public AbstractModule {
public:
	static Fastplace* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	float delay = 0;
private:
	Fastplace();
};