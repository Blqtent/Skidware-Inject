#pragma once
#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <Windows.h>

	
#include <string>
#include <vector>
#include "../../../sdk/net/minecraft/client/entity/EntityPlayerSP.h"
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

class Blink :public AbstractModule {
public:
	static Blink* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	void OnReceiveData();
	const char* modes[6]{ "Toggle", "Hold", "Throttle", "Dynamic"};
	bool shouldSpoof = false;
	long long timer = 0;
	bool running;
	bool wasActive;
	float Milliseonds = 100;
	float Chance = 2;
	Vector3 data;
	CEntityPlayer target;

private:
	Blink();
};
