#pragma once
#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../../eventManager/EventManager.hpp"
#include "../../AbstractModule.h"
#include <Windows.h>


#include <string>
#include <vector>
//struct Blink
//{
//	inline static ULONGLONG timer;
//	inline static bool running;
//	inline static bool wasActive;
//	inline static int bind = 'H';
//	inline static float Milliseonds = 10;
//
//	inline static bool Enabled = false;
//	//inline static bool throttle = false;
//
//	static void Update();
//
//	static void RenderMenu();
//	static void OnReceiveData();
//};
#include "../../../menu/menu.h"
#include "../../commonData.h"

class Disabler :public AbstractModule {
public:
	static Disabler* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	void OnReceiveData();
	const char* modes[6]{ "Timer Balance" };
	long long timer = 0;


private:
	Disabler();
};
