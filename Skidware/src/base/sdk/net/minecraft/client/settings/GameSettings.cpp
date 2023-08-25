#include "GameSettings.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

//CGameSettings::CGameSettings()
//{
//	Java::AssignClass("net.minecraft.client.settings.GameSettings", StrayCache::gamesettings_class);
//	if (StrayCache::gamesettings_class == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		StrayCache::gamesettings_class = StrayCache::gamesettings_class;
//	}
//	/*
//	if (JNIHelper::IsVanilla()) {
//		this->FieldIDs["thirdPersonView"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "aA", "I");
//		this->FieldIDs["fovSetting"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "aH", "F");
//
//		this->FieldIDs["keyBindFullscreen"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "ap", "Lavb;");
//		this->MethodIDs["setOptionKeyBinding"] = Java::Env->GetMethodID(StrayCache::gamesettings_class, "a", "(Lavb;I)V");
//		return;
//	}
//	*/
//	if (JNIHelper::IsForge()) {
//		this->FieldIDs["thirdPersonView"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74320_O", "I");
//		this->FieldIDs["fovSetting"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74334_X", "F");
//		this->FieldIDs["gammaSetting"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74333_Y", "F");
//
//		this->FieldIDs["keyBindFullscreen"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
//		this->MethodIDs["setOptionKeyBinding"] = Java::Env->GetMethodID(StrayCache::gamesettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
//		return;
//	}
//
//	this->FieldIDs["thirdPersonView"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "thirdPersonView", "I");
//	this->FieldIDs["fovSetting"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "fovSetting", "F");
//	this->FieldIDs["gammaSetting"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "gammaSetting", "F");
//
//	this->FieldIDs["keyBindFullscreen"] = Java::Env->GetFieldID(StrayCache::gamesettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
//	this->MethodIDs["setOptionKeyBinding"] = Java::Env->GetMethodID(StrayCache::gamesettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
//}
//
//jclass CGameSettings::getClass()
//{
//	return StrayCache::gamesettings_class;
//}

//jobject CGameSettings::getInstance()
//{
//	return Java::Env->GetObjectField(SDK::Minecraft->getInstance(), SDK::Minecraft->FieldIDs["gameSettings"]);
//}

float CGameSettings::GetFOV()
{
	return Java::Env->GetFloatField(this->getInstance() , StrayCache::gamesettings_fovSetting);
}

void CGameSettings::SetGamma(float gamma)
{
	jobject instance = this->getInstance();
	Java::Env->SetFloatField(this->getInstance(), StrayCache::gamesettings_gammaSetting, gamma);
}

float CGameSettings::GetGamma()
{
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::gamesettings_gammaSetting);
}

void CGameSettings::SetFullscreenKeyToNull()
{

	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::gamesettings_setOptionKeyBinding, Java::Env->GetObjectField(this->getInstance(), StrayCache::gamesettings_keyBindFullscreen), 0);
}

void CGameSettings::RestoreFullscreenKey()
{
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::gamesettings_setOptionKeyBinding, Java::Env->GetObjectField(this->getInstance(), StrayCache::gamesettings_keyBindFullscreen), 87);
}



int CGameSettings::GetThirdPersonView()
{
	return Java::Env->GetIntField(this->getInstance(), StrayCache::gamesettings_thirdPersonView);
}

