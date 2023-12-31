#include "Entity.h"
#include "../../../../java/java.h"
#include "../../../java/lang/String.h"
#include "../../../strayCache.h"

#include "../../../../util/logger.h"
#include "../../../../security/ObfuscateString.hpp"

//CEntity::CEntity()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::entity_class;
//}
//
//CEntity::CEntity(jobject instance) : CEntity()
//{
//	this->Instance = Java::Env->NewGlobalRef(instance);
//}
//
//jclass CEntity::getClass()
//{
//	return this->Class;
//}
//
//jobject CEntity::getInstance()
//{
//	return this->Instance;
//}

std::string CEntity::GetName()
{
	if (this->getInstance() == nullptr) {
		return "";
	}

	String str = String(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::entity_getName));
	
	if (str.getInstance() == nullptr)
		return "";

	if (str.ToString().starts_with("Smellon6942")) {
		return "Skidware Developer";
	}

	if (str.ToString().starts_with("BlqtentCheater")) {
		return "Skidware Developer";
	}
	//TODO:fix crashes here(idk why crash
	return str.ToString();
}

Vector3 CEntity::GetPos()
{
	return Vector3{
		(float)(double) Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_posX),
		(float)(double) Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_posY),
		(float)(double) Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_posZ)
	};
}

Vector3 CEntity::GetPrevPos()
{
	return Vector3{
		(float)(double)Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_prev_posX),
		(float)(double)Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_prev_posY),
		(float)(double)Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_prev_posZ)
	};
}

Vector3 CEntity::GetEyePos()
{
	Vector3 pos = GetPos();
	return Vector3{
		pos.x,
		(float)(double)(pos.y + (this->GetHeight() * 0.85)),
		pos.z
	};
}

Vector3 CEntity::GetLastTickPos()
{
	return Vector3{
		(float)(double) Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_lastTickPosX),
		(float)(double) Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_lastTickPosY),
		(float)(double) Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_lastTickPosZ)
	};
}

void CEntity::setMotion(Vector3 motion) {
	if (motion.x != 100000000000) {
		Java::Env->SetDoubleField(this->getInstance(), StrayCache::entity_motionX, motion.x);
	}
	if (motion.y != 100000000000) {
		Java::Env->SetDoubleField(this->getInstance(), StrayCache::entity_motionY, motion.y);
	}
	if (motion.z != 100000000000) {
		Java::Env->SetDoubleField(this->getInstance(), StrayCache::entity_motionZ, motion.z);
	}
}

void CEntity::setSprint(bool state)
{
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::entity_setSprint, state);
}

Vector3 CEntity::getMotion() {
	return Vector3{
		(float)(double)Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_motionX),
		(float)(double)Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_motionY),
		(float)(double)Java::Env->GetDoubleField(this->getInstance(), StrayCache::entity_motionZ)
	};
}

bool CEntity::isOnGround()
{
	if (!this->isValid() || this->isNULL()) return false;
	return Java::Env->GetBooleanField(this->getInstance(), StrayCache::entity_onGround);
}

bool CEntity::inWater()
{
	if (!this->isValid() || this->isNULL()) return false;
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::entity_inWater);

}

bool CEntity::isDead()
{
	if (!this->isValid() || this->isNULL()) return true;
	return Java::Env->GetBooleanField(this->getInstance(), StrayCache::entity_isDead);
}

bool CEntity::isInvisible()
{
	if (!this->isValid() || this->isNULL()) return true;
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::entity_isInvisible);
}

float CEntity::fallDistance()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_fallDistance);
}

void CEntity::setFallDistance(float i)
{
	if (!this->isValid() || this->isNULL()) return;
	Java::Env->SetFloatField(this->getInstance(), StrayCache::entity_fallDistance, i);

}

int CEntity::ticksExisted()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetIntField(this->getInstance(), StrayCache::entity_ticksExisted);

}

void CEntity::setPos(double x, double y, double z)
{
	if (!this->isValid() || this->isNULL()) return;
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::entity_setPosition, x, y, z);

}

void CEntity::setOnGround(bool state)
{
	if (!this->isValid() || this->isNULL()) return;
	Java::Env->SetBooleanField(this->getInstance(), StrayCache::entity_onGround, state);
}

bool CEntity::IsSneaking()
{
	if (!this->isValid() || this->isNULL()) return false;
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::entity_isSneaking);
}

void CEntity::setSneaking(bool state)
{
	if (!this->isValid() || this->isNULL()) return;
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::entity_setSneaking, state);
}

float CEntity::GetHeight()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_height);
}

float CEntity::GetWidth()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_width);
}

float CEntity::GetDistanceWalkedModified()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_distanceWalkedModified);
}

float CEntity::GetPrevDistanceWalkedModified()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_prevDistanceWalkedModified);
}

float CEntity::GetRotationYaw()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_rotationYaw);
}

float CEntity::GetRotationPitch()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_rotationPitch);
}

float CEntity::GetPrevRotationYaw()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_prevRotationYaw);
}

float CEntity::GetPrevRotationPitch()
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entity_prevRotationPitch);
}

Vector2 CEntity::GetAngles()
{
	if (!this->isValid() || this->isNULL()) return Vector2{};
	return Vector2(CEntity::GetRotationYaw(), CEntity::GetRotationPitch());
}

Vector2 CEntity::GetPrevAngles()
{
	if (!this->isValid() || this->isNULL()) return Vector2{};
	return Vector2(CEntity::GetPrevRotationYaw(), CEntity::GetPrevRotationPitch());
}

void CEntity::SetAngles(Vector2 angles) 
{
	if (!this->isValid() || this->isNULL()) return;
	Java::Env->SetFloatField(this->getInstance(), StrayCache::entity_rotationYaw, angles.x);
	Java::Env->SetFloatField(this->getInstance(), StrayCache::entity_rotationPitch, angles.y);
};

CAxisAlignedBB CEntity::GetBB()
{
	if (!this->isValid() || this->isNULL()) return CAxisAlignedBB{};
	return CAxisAlignedBB(
		Java::Env->GetObjectField(this->getInstance(), StrayCache::entity_boundingBox)
	);
}

void CEntity::SetBB(BoundingBox bb)
{
	if (!this->isValid() || this->isNULL()) return;
	this->GetBB().SetBoundingBox(bb);
}
