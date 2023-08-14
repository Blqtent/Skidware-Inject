#pragma once
#include "../../../util/math/geometry.h"

#include <vector>
#include <string>
#include "../../commonData.h"
//struct Fulbright
//{
//    inline static int bind = 0;
//
//    inline static bool Enabled = false;
//
//    static void Update();
//
//    static void RenderMenu();
//};

class Fulbright :public AbstractModule {
public:
	static Fulbright* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
private:
	Fulbright();
};