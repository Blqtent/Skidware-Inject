#include "EntityPlayer.h"

#include "../../../../../java/java.h"

//CEntityPlayer::CEntityPlayer()
//{
//	Java::AssignClass("net.minecraft.entity.player.EntityPlayer", StrayCache::entityPlayer_class);
//	if (StrayCache::entityPlayer_class == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		StrayCache::entityPlayer_class = StrayCache::entityPlayer_class;
//	}
//	if (JNIHelper::IsForge()) {
//		this->FieldIDs["inventory"] = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
//		return;
//	}
//	this->FieldIDs["inventory"] = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
//}
//
//CEntityPlayer::CEntityPlayer(jobject instance) : CEntityPlayer()
//{
//	this->Instance = instance;
//}
//
//
//jclass CEntityPlayer::getClass()
//{
//	return StrayCache::entityPlayer_class;
//}
//
//jobject CEntityPlayer::getInstance()
//{
//	return this->Instance;
//}

CInventoryPlayer CEntityPlayer::GetInventory()
{
	if (!this->isValid() || this->isNULL()) return CInventoryPlayer{};
	return CInventoryPlayer(Java::Env->GetObjectField(this->getInstance(), StrayCache::entityPlayer_inventory));
}

bool CEntityPlayer::isBlocking()
{
	if (!this->isValid() || this->isNULL()) return false;

	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::entityPlayer_isBlocking);
}
