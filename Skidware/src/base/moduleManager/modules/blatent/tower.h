#pragma once
#include "../../commonData.h"

class Tower : public AbstractModule {
public:
	static Tower* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
private:
	Tower();
};