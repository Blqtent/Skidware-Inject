#pragma once
#include "../../commonData.h"
//struct Nofall
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//	inline static float speed = 1.0f;
//	inline static int mode = 0;
//	inline static const char* modes[3]{ "Normal", "AAC3"};
//	static void Update();
//	static void RenderMenu();
//};

class Antivoid : public AbstractModule {
public:
	static Antivoid* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	const char* modes[6]{ "BlocksMC", "Flagless BMC", "Old NCP"};
	Vector3 groundPos;
private:
	Antivoid();
};