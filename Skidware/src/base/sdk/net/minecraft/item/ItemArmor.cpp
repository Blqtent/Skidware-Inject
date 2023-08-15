#include "ItemArmor.h"

#include "../../../strayCache.h"


CItemArmor::CItemArmor()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::itemArmor_Class;
}

CItemArmor::CItemArmor(jobject instance) : CItemArmor()
{
	this->Instance = instance;
}

jclass CItemArmor::GetClass()
{
	return this->Class;
}

jobject CItemArmor::GetInstance()
{
	return this->Instance;
}


int CItemArmor::getColor(jobject stack) {
	return Java::Env->CallIntMethod(this->GetInstance(), StrayCache::itemArmor_getColor , stack);
}