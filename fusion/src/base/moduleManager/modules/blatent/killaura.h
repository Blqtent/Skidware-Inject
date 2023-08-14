#pragma once
#include "../../commonData.h"
//struct Killaura : public module
//{
//	inline static int bind = 'G';
//
//	inline static bool Enabled = false;
//
//	inline static float leftMaxCps = 14;
//	inline static float leftMinCps = 8;
//	inline static float range = 3.5;
//	inline static bool pitchInfluenced = false;
//	inline static bool autoblock = false;
//	inline static bool keepsprint = false;
//	inline static Vector3 data;
//	inline static int targetPriority = 2;
//	inline static float fov = 360.0f;
//	inline static const char* targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
//	
//	inline static int mode = 0;
//	inline static const char* modes[3]{ "Legit", "Normal", ""};
//
//	static void Update();
//	static void RenderMenu();
//	
//private:
//	static CEntityPlayer player;
//	static float currdistance;
//};

class Killaura : public AbstractModule
{
public:
	static Killaura* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	float leftMaxCps = 14;
	float leftMinCps = 8;
	float range = 3.5;
	bool pitchInfluenced = false;
	bool autoblock = false;
	bool keepsprint = false;
	Vector3 data;
	int targetPriority = 2;
	float fov = 360.0f;
	CEntityPlayer player;
	float currdistance;
	const char* modes[3]{ "Legit", "Normal", "" };
	const char* targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
private:
	Killaura();
};