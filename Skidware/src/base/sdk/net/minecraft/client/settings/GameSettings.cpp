#include "GameSettings.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

CGameSettings::CGameSettings()
{
	Java::AssignClass("net.minecraft.client.settings.GameSettings", this->Class);
	if (this->Class == nullptr)
	{
		if (!StrayCache::initialized) StrayCache::Initialize();
		this->Class = StrayCache::gamesettings_class;
	}
	/*
	if (JNIHelper::IsVanilla()) {
		this->FieldIDs["thirdPersonView"] = Java::Env->GetFieldID(this->Class, "aA", "I");
		this->FieldIDs["fovSetting"] = Java::Env->GetFieldID(this->Class, "aH", "F");

		this->FieldIDs["keyBindFullscreen"] = Java::Env->GetFieldID(this->Class, "ap", "Lavb;");
		this->MethodIDs["setOptionKeyBinding"] = Java::Env->GetMethodID(this->Class, "a", "(Lavb;I)V");
		return;
	}
	*/
	if (JNIHelper::IsForge()) {
		this->FieldIDs["thirdPersonView"] = Java::Env->GetFieldID(this->Class, "field_74320_O", "I");
		this->FieldIDs["fovSetting"] = Java::Env->GetFieldID(this->Class, "field_74334_X", "F");
		this->FieldIDs["gammaSetting"] = Java::Env->GetFieldID(this->Class, "field_74333_Y", "F");

		this->FieldIDs["keyBindFullscreen"] = Java::Env->GetFieldID(this->Class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
		this->MethodIDs["setOptionKeyBinding"] = Java::Env->GetMethodID(this->Class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
		return;
	}

	this->FieldIDs["thirdPersonView"] = Java::Env->GetFieldID(this->Class, "thirdPersonView", "I");
	this->FieldIDs["fovSetting"] = Java::Env->GetFieldID(this->Class, "fovSetting", "F");
	this->FieldIDs["gammaSetting"] = Java::Env->GetFieldID(this->Class, "gammaSetting", "F");

	this->FieldIDs["keyBindFullscreen"] = Java::Env->GetFieldID(this->Class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
	this->MethodIDs["setOptionKeyBinding"] = Java::Env->GetMethodID(this->Class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
}

jclass CGameSettings::GetClass()
{
	return this->Class;
}

jobject CGameSettings::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["gameSettings"]);
}

float CGameSettings::GetFOV()
{
	return Java::Env->GetFloatField(GetInstance(), this->FieldIDs["fovSetting"]);
}

void CGameSettings::SetGamma(float gamma)
{
	jobject instance = this->GetInstance();
	Java::Env->SetFloatField(instance, this->FieldIDs["gammaSetting"], gamma);
}

float CGameSettings::GetGamma()
{
	return Java::Env->GetFloatField(this->GetInstance(), this->FieldIDs["gammaSetting"]);
}

void CGameSettings::SetFullscreenKeyToNull()
{
	jobject instance = this->GetInstance();
	Java::Env->CallVoidMethod(instance, this->MethodIDs["setOptionKeyBinding"], Java::Env->GetObjectField(instance, this->FieldIDs["keyBindFullscreen"]), 0);
}

void CGameSettings::RestoreFullscreenKey()
{
	jobject instance = this->GetInstance();
	Java::Env->CallVoidMethod(instance, this->MethodIDs["setOptionKeyBinding"], Java::Env->GetObjectField(instance, this->FieldIDs["keyBindFullscreen"]), 87);
}


int CGameSettings::GetThirdPersonView()
{
	return Java::Env->GetIntField(GetInstance(), this->FieldIDs["thirdPersonView"]);
}

