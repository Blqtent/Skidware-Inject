#pragma once

#include "../EntityLivingBase.h"
#include "InventoryPlayer.h"

class CEntityPlayer : public CEntityLivingBase
{
public:
	bool operator==(const CEntityPlayer& other) const {
		if (getInstance() == nullptr || other.getInstance() == nullptr)
		{
			return false;
		}
		return Java::Env->IsSameObject(getInstance(),other.getInstance());
	}
	using CEntityLivingBase::CEntityLivingBase;
	CInventoryPlayer GetInventory();
	bool isBlocking();
};

