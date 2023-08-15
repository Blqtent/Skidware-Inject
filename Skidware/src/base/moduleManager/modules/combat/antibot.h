#pragma once
#include "../../../util/math/geometry.h"
#include "../../../util/type/ArrayList.h"
#include <string>
#include "../../../sdk/sdk.h"
#include "../../commonData.h"

class Antibot :public AbstractModule {
public:
	static Antibot* getInstance();
	void onEnable();
	void onDisable();
	bool isBot(CommonData::PlayerData p) {
		if (p.obj == nullptr || p.pos.x == NULL) 
		{
			return true;
		}

		if (p.height <= 0.5f)
		{
			HeightBots.add(p.obj);
			std::cout << p.obj.GetName() << " is Bot[1]" << std::endl;
		}
		else {
			HeightBots.remove(p.obj);
		}

		if (p.obj.isPlayerSleeping())
		{
			std::cout << p.obj.GetName() << " is Bot[2]" << std::endl;
			sleepingEntities.add(p.obj);
		}
		else {
			sleepingEntities.remove(p.obj);
		}

		/*if (p.obj.ticksExisted() < 100.f)
		{
			std::cout << p.obj.GetName() << " is Bot[2]" << std::endl;
			ticksExistedEntities.add(p.obj);
		}
		else {
			ticksExistedEntities.remove(p.obj);
		}*/

		return /*ticksExistedEntities.contains(p.obj) ||*/ HeightBots.contains(p.obj) || sleepingEntities.contains(p.obj);
	}
	void RenderMenu();
private:
	std::vector<CEntityPlayer> bots;
	Antibot();
	ArrayList<CEntityPlayer> HeightBots;
	/*ArrayList<CEntityPlayer> ticksExistedEntities;*/
	ArrayList<CEntityPlayer> sleepingEntities;
};