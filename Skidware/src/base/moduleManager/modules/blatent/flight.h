#pragma once
#include "../../commonData.h"

class Flight : public AbstractModule {
public:
	static Flight* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	float glideSpeed = 0;
	const char* modes[5]{ "MotionY", "Airjump", "Motion", "Vulcan", "Test"};
	long long count = 0;
	bool isHurt = false;
private:
	Flight();
};