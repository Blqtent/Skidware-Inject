#include "Minecraft.h"
#include "../../../../java/java.h"
#include "../../../../util/logger.h"

#include "../entity/EntityLivingBase.h"

CMinecraft::CMinecraft()
{
	Java::AssignClass("net.minecraft.client.Minecraft", this->Class);
	/*
	* VANILLA
	*/
	/*
	if (JNIHelper::IsVanilla())
	{
		this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->GetClass(), "A", "Lave;");
		this->Instance = Java::Env->CallStaticObjectMethod(this->GetClass(), this->MethodIDs["getMinecraft"]);

		this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->GetClass(), "h", "Lbew;");
		this->thePlayer = new CEntityPlayerSP();

		this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->GetClass(), "F", "Lbdb;");
		this->theWorld = new CWorldClient();

		this->activeRenderInfo = new CActiveRenderInfo();

		this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->GetClass(), "aa", "Lbiu;");
		this->renderManager = new CRenderManager();

		this->FieldIDs["timer"] = Java::Env->GetFieldID(this->GetClass(), "Y", "Lavl;");
		this->timer = new CTimer();

		this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->GetClass(), "t", "Lavh;");
		this->gameSettings = new CGameSettings();

		this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->GetClass(), "ac", "Lpk;");
		this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->GetClass(), "m", "Lave;");

		this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->GetClass(), "s", "Lave;");

		this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->GetClass(), "aw", "()V");

		return;
	}
	*/

	if (JNIHelper::IsForge()) {
		this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->GetClass(), "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
		this->Instance = Java::Env->CallStaticObjectMethod(this->GetClass(), this->MethodIDs["getMinecraft"]);

		this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->GetClass(), "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
		this->thePlayer = new CEntityPlayerSP();

		this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->GetClass(), "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
		this->theWorld = new CWorldClient();

		this->activeRenderInfo = new CActiveRenderInfo();

		this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->GetClass(), "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
		this->renderManager = new CRenderManager();

		this->FieldIDs["timer"] = Java::Env->GetFieldID(this->GetClass(), "field_71428_T", "Lnet/minecraft/util/Timer;");
		this->timer = new CTimer();

		this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->GetClass(), "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
		this->gameSettings = new CGameSettings();

		this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->GetClass(), "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
		this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->GetClass(), "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");

		this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->GetClass(), "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");

		this->FieldIDs["rightClickDelayTimer"] = Java::Env->GetFieldID(this->GetClass(), "field_71467_ac", "I");

		// not used lol
		this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->GetClass(), "func_147116_af", "()V");
		this->MethodIDs["getDebugFPS"] = Java::Env->GetMethodID(this->GetClass(), "func_175610_ah", "()I");
		return;
	}
	this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->GetClass(), "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	this->Instance = Java::Env->CallStaticObjectMethod(this->GetClass(), this->MethodIDs["getMinecraft"]);

	this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->GetClass(), "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	this->thePlayer = new CEntityPlayerSP();

	this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->GetClass(), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
	this->theWorld = new CWorldClient();

	this->activeRenderInfo = new CActiveRenderInfo();

	this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->GetClass(), "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
	this->renderManager = new CRenderManager();

	this->FieldIDs["timer"] = Java::Env->GetFieldID(this->GetClass(), "timer", "Lnet/minecraft/util/Timer;");
	this->timer = new CTimer();

	this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->GetClass(), "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
	this->gameSettings = new CGameSettings();

	this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->GetClass(), "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
	this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->GetClass(), "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");

	this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->GetClass(), "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
	
	this->FieldIDs["rightClickDelayTimer"] = Java::Env->GetFieldID(this->GetClass(), "rightClickDelayTimer", "I");

	// not used lol
	this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->GetClass(), "clickMouse", "()V");
	this->MethodIDs["getDebugFPS"] = Java::Env->GetMethodID(this->GetClass(), "getDebugFPS", "()I");
}

jclass CMinecraft::GetClass()
{
	return this->Class;
}

jobject CMinecraft::GetInstance()
{
	return this->Instance;
}

CEntity CMinecraft::GetRenderViewEntity()
{
	return CEntity(Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["getRenderViewEntity"]));
}

bool CMinecraft::IsInGuiState()
{
	if (Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]) != NULL) return true;
	return false;
}

int CMinecraft::getDebugFPS()
{
	return Java::Env->CallIntMethod(this->GetInstance(), this->MethodIDs["getDebugFPS"]);
}

void CMinecraft::ClickMouse()
{
	Java::Env->CallVoidMethod(this->GetInstance(), this->MethodIDs["clickMouse"]);

}

void CMinecraft::setRightClickDelayTimer(jint delay) {
	Java::Env->SetIntField(this->GetInstance(), this->FieldIDs["rightClickDelayTimer"], delay);
}

jobject CMinecraft::getPlayerController()
{
	if (JNIHelper::IsForge()) {
		jfieldID field = Java::Env->GetFieldID(this->GetClass(), "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
		return Java::Env->GetObjectField(this->GetInstance(), field);
	}
	jfieldID field = Java::Env->GetFieldID(this->GetClass(), "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
	return Java::Env->GetObjectField(this->GetInstance(), field);
}

CMovingObjectPosition CMinecraft::GetMouseOver()
{
	return CMovingObjectPosition(Java::Env->GetObjectField(this->Instance, this->FieldIDs["objectMouseOver"]));
}
