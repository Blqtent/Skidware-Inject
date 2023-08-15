#pragma once

#include "../EntityLivingBase.h"
#include "InventoryPlayer.h"

struct CEntityPlayer : CEntityLivingBase
{
	CEntityPlayer();
	CEntityPlayer(jobject instance);
	bool operator==(const CEntityPlayer& other) const {
		if (Instance == nullptr || other.Instance == nullptr)
		{
			return false;
		}
		return Instance == other.Instance;
	}
	jclass GetClass();
	jobject GetInstance();

	CInventoryPlayer GetInventory();
};

