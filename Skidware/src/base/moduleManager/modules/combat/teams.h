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
	bool isTeam(CEntityPlayer p) {


		//TODO:make the wrapper cleaner

		if (Java::Env->IsSameObject(p.getInstance(), NULL)) {
			return true;
		}

		if (!p.isValid() || p.isNULL())
		{
			return true;
		}

		/*std::cout << "1" << std::endl;*/
		CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

		if (!thePlayer->GetInventory().isValid()|| p.GetInventory().isNULL())
		{
			return true;
		}
		//std::cout << "2" << std::endl;
		CItemStack myHead = thePlayer->GetInventory().GetArmorItem(3);
		CItemStack entityHead = p.GetInventory().GetArmorItem(3);

		if (!myHead.isValid() || myHead.isNULL())
		{
			return true;
		}
		
		if (!entityHead.isValid() || entityHead.isNULL())
		{
			return true;
		}

		//std::cout << "3" << std::endl;
		if (entityHead.GetItem().getInstance() == nullptr || myHead.GetItem().getInstance() == nullptr)
		{
			return true;
		}

		/*std::cout << "4" << std::endl;*/
		auto colorMe = CItemArmor(myHead.GetItem()).getColor(myHead.getInstance());
		auto colorU = CItemArmor(entityHead.GetItem()).getColor(entityHead.getInstance());
	/*	std::cout << colorMe << " " << colorU << std::endl;*/
		return colorMe ==  colorU;
	}
private:
	Teams();
};