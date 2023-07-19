#include "EntityPlayerSP.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

#include "../../../../../util/logger.h"

CEntityPlayerSP::CEntityPlayerSP() : CEntityPlayer()
{
	Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", this->Class);
}

jclass CEntityPlayerSP::GetClass()
{
	return this->Class;
}

jobject CEntityPlayerSP::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["thePlayer"]);
}

void CEntityPlayerSP::setSneak(bool state)
{
	if (JNIHelper::IsForge()) {
		CGameSettings* settings = SDK::Minecraft->gameSettings;

		jfieldID sneak = Java::Env->GetFieldID(settings->GetClass(), "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");
		jobject sneakObj = Java::Env->GetObjectField(settings->GetInstance(), sneak);
		jclass keybind_class = Java::Env->GetObjectClass(sneakObj);

		jfieldID pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");

		Java::Env->SetBooleanField(sneakObj, pressed, state);
		return;
	}
	CGameSettings* settings = SDK::Minecraft->gameSettings;

	jfieldID sneak = Java::Env->GetFieldID(settings->GetClass(), "keyBindSneak", "Lnet/minecraft/client/settings/KeyBinding;");
	jobject sneakObj = Java::Env->GetObjectField(settings->GetInstance(), sneak);
	jclass keybind_class = Java::Env->GetObjectClass(sneakObj);

	jfieldID pressed = Java::Env->GetFieldID(keybind_class, "pressed", "Z");

	Java::Env->SetBooleanField(sneakObj, pressed, state);
	
}

void CEntityPlayerSP::attackEntity(CEntityPlayerSP* player, jobject entity)
{
	jclass playerControllerClazz;
	Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerClazz);
	if (JNIHelper::IsForge()) {
		jobject playerControllerObj = SDK::Minecraft->getPlayerController();
		jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
		return Java::Env->CallVoidMethod(playerControllerObj, attackMid, player->GetInstance(), entity);
	}
	jobject playerControllerObj = SDK::Minecraft->getPlayerController();
	jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity /Entity;)V");
	return Java::Env->CallVoidMethod(playerControllerObj, attackMid, player->GetInstance(), entity);
}

bool CEntityPlayerSP::sendUseItem(CEntityPlayer* player, CWorld* world, CItemStack item)
{
	jclass playerControllerClazz;
	Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerClazz);
	if (JNIHelper::IsForge()) {
		jobject playerControllerObj = SDK::Minecraft->getPlayerController();
		jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
		return Java::Env->CallBooleanMethod(playerControllerObj, attackMid, player->GetInstance(), world, item.GetInstance());
	}
	jobject playerControllerObj = SDK::Minecraft->getPlayerController();
	jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "sendUseItem", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
	return Java::Env->CallBooleanMethod(playerControllerObj, attackMid, player->GetInstance(), world, item.GetInstance());
}

double CEntityPlayerSP::get_motion_x()
{
	if (GetClass() == NULL) return NULL;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID xfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70159_w" : "motionX", "D");
	double x = (double)JNIHelper::env->GetDoubleField(GetInstance(), StrayCache::entity_motionX);
	JNIHelper::env->DeleteLocalRef(playerclass);
	return x;
}

void CEntityPlayerSP::set_motion_x(double x)
{
	if (GetClass() == NULL) return;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	JNIHelper::env->SetDoubleField(GetInstance(), StrayCache::entity_motionX, (jdouble)x);
	JNIHelper::env->DeleteLocalRef(playerclass);
}

double CEntityPlayerSP::get_motion_y()
{
	if (GetClass() == NULL) return NULL;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	double y = (double)JNIHelper::env->GetDoubleField(GetInstance(), StrayCache::entity_motionY);
	JNIHelper::env->DeleteLocalRef(playerclass);
	return y;
}

void CEntityPlayerSP::set_motion_y(double y)
{
	if (GetClass() == NULL) return;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID yfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70181_x" : "motionY", "D");
	JNIHelper::env->SetDoubleField(GetInstance(), StrayCache::entity_motionY, (jdouble)y);
	JNIHelper::env->DeleteLocalRef(playerclass);
}

double CEntityPlayerSP::get_motion_z()
{
	if (GetClass() == NULL) return NULL;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID xfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70179_y" : "motionZ", "D");
	double z = (double)JNIHelper::env->GetDoubleField(GetInstance(), StrayCache::entity_motionZ);
	JNIHelper::env->DeleteLocalRef(playerclass);
	return z;
}

void CEntityPlayerSP::set_motion_z(double z)
{
	if (GetClass() == NULL) return;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID xfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70179_y" : "motionZ", "D");
	JNIHelper::env->SetDoubleField(GetInstance(), StrayCache::entity_motionZ, (jdouble)z);
	JNIHelper::env->DeleteLocalRef(playerclass);
}
