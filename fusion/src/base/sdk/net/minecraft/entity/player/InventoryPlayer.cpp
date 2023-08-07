#include "InventoryPlayer.h"

#include "../../../../strayCache.h"

CInventoryPlayer::CInventoryPlayer()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::inventoryPlayer_class;
}

CInventoryPlayer::CInventoryPlayer(jobject instance) : CInventoryPlayer()
{
	this->Instance = instance;
}

jclass CInventoryPlayer::GetClass()
{
	return this->Class;
}

jobject CInventoryPlayer::GetInstance()
{
	return this->Instance;
}

CItemStack CInventoryPlayer::GetCurrentItem()
{
	return CItemStack(Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::inventoryPlayer_getCurrentItem));
}

void CInventoryPlayer::SetCurrentItem(int index)
{
	Java::Env->SetIntField(this->Instance, StrayCache::inventoryPlayer_currentItem, index);
}

CItemStack CInventoryPlayer::GetIndexItem(int index)
{
	jobject mainInventory = Java::Env->GetObjectField(this->Instance, StrayCache::inventoryPlayer_mainInv);
	jobject itemstack = Java::Env->GetObjectArrayElement((jobjectArray)mainInventory, index);
	return CItemStack(itemstack);

}
