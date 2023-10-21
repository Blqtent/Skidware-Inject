#pragma once
#include "../../../util/math/geometry.h"
#include "../../../util/type/ArrayList.h"
#include <string>
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
#include <string>
#include <vector>

class Antibot : public AbstractModule {
public:
	static Antibot* getInstance();
	void onEnable();
	void onDisable();
	static bool isBot(CEntityPlayer p) {
		if (p.GetName().length() < 3) {
			bots.push_back(p);
			return true;
		}
		else if ((p.isInvisible() && !p.isOnGround())) {
			bots.push_back(p);
			return true;
		}
		else if (p.ticksExisted() > 9999) {
			bots.push_back(p);
			return true;
		}
		std::string DisplayName = p.GetName();
		bool ContainsIllegalChars = DisplayName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_") != std::string::npos;
		if (ContainsIllegalChars) {
			return true;
		}
		return false;
	}
	void RenderMenu();
private:
	static std::vector<CEntityPlayer> bots;
	Antibot();
	ArrayList<CEntityPlayer> HeightBots;
	ArrayList<CEntityPlayer> flyingBots;
	/*ArrayList<CEntityPlayer> ticksExistedEntities;*/
	ArrayList<CEntityPlayer> sleepingEntities;
};