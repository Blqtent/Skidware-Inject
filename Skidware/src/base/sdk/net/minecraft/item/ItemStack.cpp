#include "ItemStack.h"
#include "../../../strayCache.h"


//CItemStack::CItemStack()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::itemStack_class;
//}
//
//CItemStack::CItemStack(jobject instance) : CItemStack()
//{
//	this->Instance = instance;
//}
//
//jclass CItemStack::getClass()
//{
//	return this->Class;
//}
//
//jobject CItemStack::getInstance()
//{
//	return this->Instance;
//}

jobject CItemStack::GetItem()
{
	return Java::Env->CallObjectMethod(this->getInstance(), StrayCache::itemStack_getItem);
}

int CItemStack::GetItemID()
{
	return Java::Env->CallStaticIntMethod(this->getClass(), StrayCache::itemStack_getIdFromItem, this->GetItem());
}
