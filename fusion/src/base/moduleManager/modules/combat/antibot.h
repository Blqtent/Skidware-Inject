#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../module.h"
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
struct Antibot
{
	inline static int bind = 0;

	inline static bool Enabled = false;
	
	inline static std::vector<CEntityPlayer> bots;

	static void Update();

	static void RenderMenu();

	static bool isBot(CommonData::PlayerData p) {
		if (p.obj.GetName().contains("§c")) {

			bots.push_back(p.obj);
			return true;
		}
		else if (p.obj.GetName().contains("[NPC] ")) {
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
		else if (p.obj.GetName().contains("-")) {
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
};

