#include "item.h"

#include "../../../strayCache.h"

CItem::CItem()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::itemStack_class;
}

CItem::CItem(jobject instance) : CItem()
{
	this->Instance = instance;
}

jclass CItem::GetClass()
{
	return this->Class;
}

jobject CItem::GetInstance()
{
	return this->Instance;
}
