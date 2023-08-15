#include "EntityPlayer.h"

#include "../../../../../java/java.h"

CEntityPlayer::CEntityPlayer()
{
	Java::AssignClass("net.minecraft.entity.player.EntityPlayer", this->Class);
	if (this->Class == nullptr)
	{
		if (!StrayCache::initialized) StrayCache::Initialize();
		this->Class = StrayCache::entityPlayer_class;
	}
	if (JNIHelper::IsForge()) {
		this->FieldIDs["inventory"] = Java::Env->GetFieldID(this->Class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
		return;
	}
	this->FieldIDs["inventory"] = Java::Env->GetFieldID(this->Class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
}

CEntityPlayer::CEntityPlayer(jobject instance) : CEntityPlayer()
{
	this->Instance = instance;
}


jclass CEntityPlayer::GetClass()
{
	return this->Class;
}

jobject CEntityPlayer::GetInstance()
{
	return this->Instance;
}

CInventoryPlayer CEntityPlayer::GetInventory()
{
	return CInventoryPlayer(Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["inventory"]));
}
