#include "InventoryPlayer.h"

#include "../../../../strayCache.h"

//CInventoryPlayer::CInventoryPlayer()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::inventoryPlayer_class;
//}
//
//CInventoryPlayer::CInventoryPlayer(jobject instance) : CInventoryPlayer()
//{
//	this->Instance = instance;
//}
//
//jclass CInventoryPlayer::getClass()
//{
//	return this->Class;
//}
//
//jobject CInventoryPlayer::getInstance()
//{
//	return this->Instance;
//}

CItemStack CInventoryPlayer::GetCurrentItem()
{
	return CItemStack(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::inventoryPlayer_getCurrentItem));
}

void CInventoryPlayer::SetCurrentItem(int index)
{
	Java::Env->SetIntField(this->getInstance(), StrayCache::inventoryPlayer_currentItem, index);
}

int CInventoryPlayer::GetCurrentItemIndex()
{
	return Java::Env->GetIntField(this->getInstance(), StrayCache::inventoryPlayer_currentItem);

}

CItemStack CInventoryPlayer::GetIndexItem(int index)
{
	jobject mainInventory = Java::Env->GetObjectField(this->getInstance(), StrayCache::inventoryPlayer_mainInv);
	jobject itemstack = Java::Env->GetObjectArrayElement((jobjectArray)mainInventory, index);
	return CItemStack(itemstack);

}
CItemStack CInventoryPlayer::GetStackInSlot(int index)
{
	//jobject mainInventory = Java::Env->GetObjectField(this->getInstance(), StrayCache::inventoryPlayer_mainInv);
	//jobject itemstack = Java::Env->GetObjectArrayElement((jobjectArray)mainInventory, index);
	return CItemStack(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::inventoryPlayer_getStackInSlot,index));

}

CItemStack CInventoryPlayer::GetArmorItem(int index)
{
	if (!isValid() || isNULL())
	{
		return CItemStack{};
	}
	jobject armorInventory = Java::Env->GetObjectField(this->getInstance(), StrayCache::inventoryPlayer_armorInv);
	jobject itemstack = Java::Env->GetObjectArrayElement((jobjectArray)armorInventory, index);
	return CItemStack(itemstack);

}
