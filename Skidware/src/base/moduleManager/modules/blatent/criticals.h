#pragma once
#pragma once
#include "../../commonData.h"

class Criticals : public AbstractModule {
public:
	static Criticals* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	int hits = 0;
	const char* modes[1]{ "No Ground" };
private:
	Criticals();
};