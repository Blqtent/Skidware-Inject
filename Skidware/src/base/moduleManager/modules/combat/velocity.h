#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"


#include <string>
#include <vector>


class Velocity :public AbstractModule {
public:
	static Velocity* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	float Horizontal = 0.f;
	float Vertical = 1.0f;
	bool onlyTargeting = false;
	const char* modes[6]{ "Normal", "Intave", "Push", "Strafe", "NoBypass", "Flag"};
private:
	Velocity();
};