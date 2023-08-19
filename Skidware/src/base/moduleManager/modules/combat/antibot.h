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
	bool isBot(CEntityPlayer p) {

		if (Java::Env->IsSameObject(p.getInstance(), NULL)) {
			return true;
		}

		if (p.GetHeight() <= 0.5f)
		{
			HeightBots.add(p);
		}
		else {
			HeightBots.remove(p);
		}

		if (p.isPlayerSleeping())
		{
			sleepingEntities.add(p);
		}
		else {
			sleepingEntities.remove(p);
		}


		return HeightBots.contains(p) || sleepingEntities.contains(p);
	}
	void RenderMenu();
private:
	std::vector<CEntityPlayer> bots;
	Antibot();
	ArrayList<CEntityPlayer> HeightBots;
	/*ArrayList<CEntityPlayer> ticksExistedEntities;*/
	ArrayList<CEntityPlayer> sleepingEntities;
};