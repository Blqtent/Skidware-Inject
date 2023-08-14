#include "EntityLivingBase.h"

#include "../../../../java/java.h"
#include "../../../strayCache.h"

CEntityLivingBase::CEntityLivingBase()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::entityLivingBase_class;
}

jclass CEntityLivingBase::GetClass()
{
	return this->Class;
}

jobject CEntityLivingBase::GetInstance()
{
	return this->Instance;
}

float CEntityLivingBase::GetHealth()
{
	return Java::Env->CallFloatMethod(this->GetInstance(), StrayCache::entityLivingBase_getHealth);
}

float CEntityLivingBase::GetMaxHealth()
{
	return Java::Env->CallFloatMethod(this->GetInstance(), StrayCache::entityLivingBase_getMaxHealth);
}

float CEntityLivingBase::getMoveStrafe()
{

	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entityLivingBase_moveStrafe);
}

float CEntityLivingBase::getMoveForward()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entityLivingBase_moveForward);

}

bool CEntityLivingBase::CanEntityBeSeen(jobject entity) 
{
	return Java::Env->CallBooleanMethod(this->GetInstance(), StrayCache::entityLivingBase_canEntityBeSeen, entity);
}

int CEntityLivingBase::getHurtTime() {
	return Java::Env->GetIntField(this->GetInstance(), StrayCache::entityLivingBase_hurttime);
}

void CEntityLivingBase::swingItem()
{
	Java::Env->CallVoidMethod(this->GetInstance(), StrayCache::entityLivingBase_swingItem);
}

void CEntityLivingBase::jump()
{
	Java::Env->CallVoidMethod(this->GetInstance(), StrayCache::entityLivingBase_jump);
}

void CEntityLivingBase::setMoveStrafe(float i)
{
	Java::Env->SetFloatField(this->GetInstance(), StrayCache::entityLivingBase_moveStrafe, i);
}

void CEntityLivingBase::setMoveForward(float i)
{
	Java::Env->SetFloatField(this->GetInstance(), StrayCache::entityLivingBase_moveForward, i);

}
