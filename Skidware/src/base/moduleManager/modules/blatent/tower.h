#pragma once
#include "../../commonData.h"

class Tower : public AbstractModule {
public:
	static Tower* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	bool tower = false;
private:
	Tower();
	float orYaw = 0;
	float orPitch = 0;
	float reverseYaw = 0;
};