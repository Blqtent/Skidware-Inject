#pragma once

#include "Entity.h"

struct CEntityLivingBase : CEntity
{
	CEntityLivingBase();

	jclass GetClass();
	jobject GetInstance();

	float GetHealth();
	float GetMaxHealth();
	float getMoveStrafe();
	float getMoveForward();
	bool CanEntityBeSeen(jobject entity);
	int getHurtTime();
	void swingItem();
	void jump();
	void setMoveStrafe(float i);
	void setMoveForward(float i);
};

