#pragma once

#include "../util/math/geometry.h"
#include "../sdk/sdk.h"
#include "../util/logger.h"
#include "../../../ext/jni/jni.h"
#include "AbstractModule.h"
#include "../eventManager/EventManager.hpp"
#include "../eventManager/events/EventUpdate.hpp"

//#include <curl/curl.h>
#define M_PI 3.1415926

/*
This file is mainly for optimization purposes, instead of loading the data inside each module, we just load them here and then pass the data onto
the modules that will eventually use them.

The modules that write data will still need to access required java objects to do so.
*/

class CommonData
{
public:
	CommonData() {
		EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { UpdateData(std::forward<decltype(PH1)>(PH1)); });
	}

	static CommonData* getInstance() {
		static auto* inst = new CommonData();
		return inst;
	}
	bool dataUpdated = false;
	bool post = false;
	Matrix modelView;
	Matrix projection;
	Vector3 renderPos;
	float renderPartialTicks; 
	float fov;
	int thirdPersonView;
	
	struct PlayerData{
		CEntityPlayer obj;
		Vector3 pos;
		Vector3 lastPos;
		BoundingBox boundingBox;
		std::string name;
		float height;
		float health;
		float maxHealth;
	};

	std::vector<PlayerData> nativePlayerList;

	void UpdateData(const EventUpdate e)
	{
		if (!SanityCheck()) return;
		modelView = SDK::Minecraft->activeRenderInfo->ModelViewMatrix();
		projection = SDK::Minecraft->activeRenderInfo->ProjectionMatrix();
		fov = SDK::Minecraft->gameSettings->GetFOV();
		thirdPersonView = SDK::Minecraft->gameSettings->GetThirdPersonView();

		float ySubtractValue = 3.4;
		if (SDK::Minecraft->thePlayer->IsSneaking())
			ySubtractValue -= .175f;

		renderPos = SDK::Minecraft->renderManager->RenderPos() + Vector3{ 0, ySubtractValue, 0 };
		renderPartialTicks = SDK::Minecraft->timer->GetRenderPartialTicks();

		// Storing all the required data that will be used within modules here just to have one for loop for gathering data
		// the rest of the for loops inside modules will be for actually doing what they need to do
		std::vector<PlayerData> newData;
		std::vector<CEntityPlayer> playerList = SDK::Minecraft->theWorld->GetPlayerList();
		for (CEntityPlayer player : playerList) {
			newData.push_back(PlayerData{
					player,
					player.GetPos(),
					player.GetLastTickPos(),
					player.GetBB().GetNativeBoundingBox(),
					player.GetName(),
					player.GetHeight(),
					player.GetHealth(),
					player.GetMaxHealth()
				});
		}
		nativePlayerList = newData;

		dataUpdated = true; // This entire function is stopped, and this is flipped once the world and or player object appears to be null
							// Mainly for sanity checks for rendering functions, it prevents crashing whenever the user is not in a game because some data
							// might be needed from within the render functions.
	}

	// Return false if sanity check failed
	bool SanityCheck() {
		if (!SDK::Minecraft->thePlayer->GetInstance() || !SDK::Minecraft->theWorld->GetInstance())
		{
			CommonData::dataUpdated = false;
			return false;
		}
		return true;
	}
};