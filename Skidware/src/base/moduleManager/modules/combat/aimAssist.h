#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"

class AimAssist :public AbstractModule {
public:
	static AimAssist* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderUpdate();
	void RenderMenu();
	Vector3 renderData;
	bool visibilityCheck = true;
	bool aimAssistFeedback = true;
	bool fovCircle = true;
	Vector3 data;
	bool pitchInfluenced = false;
	bool aimKey = true;
	bool adaptive = true;
	float adaptiveOffset = 3;
	float fov = 35.0f;
	float smooth = 15.f;
	float aimDistance = 4.f;
	float randomYaw = 2;
	float randomPitch = .075f;
	int targetPriority = 2;
	const char* targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
private:
	AimAssist();
};