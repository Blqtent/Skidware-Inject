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
	bool isBot(CEntityPlayer entity) {
		std::string name = entity.GetName();

		if (Java::Env->IsSameObject(SDK::Minecraft->thePlayer->getInstance(), entity.getInstance())
			|| entity.ticksExisted() > 99999
			|| name.find("-")
			|| name.find("[")
			|| name.find("]")
			|| name.find(" ")
			|| entity.isInvisible()
			|| name.length() <= 2) {
			return true;
		}
		else {
			return false;
		}
	}
	void RenderMenu();
private:
	std::vector<CEntityPlayer> bots;
	Antibot();
	ArrayList<CEntityPlayer> HeightBots;
	ArrayList<CEntityPlayer> flyingBots;
	/*ArrayList<CEntityPlayer> ticksExistedEntities;*/
	ArrayList<CEntityPlayer> sleepingEntities;
};