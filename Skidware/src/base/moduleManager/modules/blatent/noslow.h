#pragma once
#include "../../commonData.h"

class NoSlow : public AbstractModule {
public:
	static NoSlow* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	const char* modes[2]{ "Hypixel", "Normal"};
private:
	NoSlow();
};