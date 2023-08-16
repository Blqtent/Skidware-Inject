#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../commonData.h"

class Teams :public AbstractModule {
public:
	static Teams* getInstance();
	void onEnable();
	void onDisable();
	void RenderMenu();
	bool isTeam(CommonData::PlayerData p) {


		//TODO:make the wrapper cleaner

		if (p.obj == nullptr || p.pos.x == NULL)
		{
			return true;
		}
		/*std::cout << "1" << std::endl;*/
		CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

		if (thePlayer->GetInventory().GetClass() == nullptr || p.obj.GetInventory().GetClass() == nullptr)
		{
			return true;
		}
		//std::cout << "2" << std::endl;
		CItemStack myHead = thePlayer->GetInventory().GetArmorItem(3);
		CItemStack entityHead = p.obj.GetInventory().GetArmorItem(3);

		if (entityHead.GetClass() == nullptr || myHead.GetClass() == nullptr)
		{
			return true;
		}
		//std::cout << "3" << std::endl;
		if (entityHead.GetItem() == nullptr || myHead.GetItem()== nullptr)
		{
			return true;
		}

		/*std::cout << "4" << std::endl;*/
		auto colorMe = CItemArmor(myHead.GetItem()).getColor(myHead.GetInstance());
		auto colorU = CItemArmor(entityHead.GetItem()).getColor(entityHead.GetInstance());
	/*	std::cout << colorMe << " " << colorU << std::endl;*/
		return colorMe ==  colorU;
	}
private:
	Teams();
};