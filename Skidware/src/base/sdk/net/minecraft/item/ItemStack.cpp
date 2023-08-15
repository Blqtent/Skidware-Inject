#include "ItemStack.h"
#include "../../../strayCache.h"


CItemStack::CItemStack()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::itemStack_class;
}

CItemStack::CItemStack(jobject instance) : CItemStack()
{
	this->Instance = instance;
}

jclass CItemStack::GetClass()
{
	return this->Class;
}

jobject CItemStack::GetInstance()
{
	return this->Instance;
}

jobject CItemStack::GetItem()
{
	return Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::itemStack_getItem);
}

int CItemStack::GetItemID()
{
	//idk why it crashed,the mapping is correct
	//TODO:FIX
	if (StrayCache::itemStack_getItemID == nullptr)
	{
		if (StrayCache::itemStack_class == nullptr)
			Java::AssignClass("net.minecraft.item.ItemStack", StrayCache::itemStack_class);
		if(JNIHelper::IsForge())
			StrayCache::itemStack_getItemID =Java::Env->GetStaticMethodID(StrayCache::itemStack_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
		StrayCache::itemStack_getItemID =Java::Env->GetStaticMethodID(StrayCache::itemStack_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I");

	}
	return Java::Env->CallStaticIntMethod(this->GetClass(), StrayCache::itemStack_getItemID, this->GetItem());
}
