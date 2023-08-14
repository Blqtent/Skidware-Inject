#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../../sdk/sdk.h"
#include "../../commonData.h"

class Antibot :public AbstractModule {
public:
	static Antibot* getInstance();
	void onEnable();
	void onDisable();
	bool isBot(CommonData::PlayerData p) {
		if (p.obj.GetName().find("§c") ) {

			bots.push_back(p.obj);
			return true;
		}
		else if (p.obj.GetName().find("[NPC] ") != -1) {
			bots.push_back(p.obj);

			return true;
		}
		else if (p.obj.GetName().length() < 3) {
			bots.push_back(p.obj);
			return true;
		}
		else if ((p.obj.isInvisible() && !p.obj.isOnGround())) {
			bots.push_back(p.obj);
			return true;
		}
		else if (p.obj.GetName().find("-") != -1) {
			bots.push_back(p.obj);
			return true;
		}
		std::string DisplayName = p.obj.GetName();
		bool ContainsIllegalChars = DisplayName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_") != std::string::npos;
		if (ContainsIllegalChars) {
			return true;
		}
		return false;
	}
	void RenderMenu();
private:
	std::vector<CEntityPlayer> bots;
	Antibot();
};