#include "Minecraft.h"
#include "../../../../java/java.h"
#include "../../../../util/logger.h"

#include "../entity/EntityLivingBase.h"
#include "../../../sdk.h"

//CMinecraft::CMinecraft()
//{
//	Java::AssignClass("net.minecraft.client.Minecraft", this->Class);
//	/*
//	* VANILLA
//	*/
//	/*
//	if (JNIHelper::IsVanilla())
//	{
//		this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->getClass(), "A", "Lave;");
//		this->Instance = Java::Env->CallStaticObjectMethod(this->getClass(), this->MethodIDs["getMinecraft"]);
//
//		this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->getClass(), "h", "Lbew;");
//		this->thePlayer = new CEntityPlayerSP();
//
//		this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->getClass(), "F", "Lbdb;");
//		this->theWorld = new CWorldClient();
//
//		this->activeRenderInfo = new CActiveRenderInfo();
//
//		this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->getClass(), "aa", "Lbiu;");
//		this->renderManager = new CRenderManager();
//
//		this->FieldIDs["timer"] = Java::Env->GetFieldID(this->getClass(), "Y", "Lavl;");
//		this->timer = new CTimer();
//
//		this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->getClass(), "t", "Lavh;");
//		this->gameSettings = new CGameSettings();
//
//		this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->getClass(), "ac", "Lpk;");
//		this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->getClass(), "m", "Lave;");
//
//		this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->getClass(), "s", "Lave;");
//
//		this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->getClass(), "aw", "()V");
//
//		return;
//	}
//	*/
//
//	if (JNIHelper::IsForge()) {
//		this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->getClass(), "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
//		this->Instance = Java::Env->CallStaticObjectMethod(this->getClass(), this->MethodIDs["getMinecraft"]);
//
//		this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->getClass(), "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
//		this->thePlayer = new CEntityPlayerSP();
//
//		this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->getClass(), "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
//		this->theWorld = new CWorldClient();
//
//		this->activeRenderInfo = new CActiveRenderInfo();
//
//		this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->getClass(), "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
//		this->renderManager = new CRenderManager();
//
//		this->FieldIDs["timer"] = Java::Env->GetFieldID(this->getClass(), "field_71428_T", "Lnet/minecraft/util/Timer;");
//		this->timer = new CTimer();
//
//		this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->getClass(), "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
//		this->gameSettings = new CGameSettings();
//
//		this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->getClass(), "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
//		this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->getClass(), "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
//
//		this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->getClass(), "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
//
//		this->FieldIDs["rightClickDelayTimer"] = Java::Env->GetFieldID(this->getClass(), "field_71467_ac", "I");
//
//		// not used lol
//		this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->getClass(), "func_147116_af", "()V");
//		this->MethodIDs["getDebugFPS"] = Java::Env->GetMethodID(this->getClass(), "func_175610_ah", "()I");
//		return;
//	}
//	this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->getClass(), "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
//	this->Instance = Java::Env->CallStaticObjectMethod(this->getClass(), this->MethodIDs["getMinecraft"]);
//
//	this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->getClass(), "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
//	this->thePlayer = new CEntityPlayerSP();
//
//	this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->getClass(), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
//	this->theWorld = new CWorldClient();
//
//	this->activeRenderInfo = new CActiveRenderInfo();
//
//	this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->getClass(), "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
//	this->renderManager = new CRenderManager();
//
//	this->FieldIDs["timer"] = Java::Env->GetFieldID(this->getClass(), "timer", "Lnet/minecraft/util/Timer;");
//	this->timer = new CTimer();
//
//	this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->getClass(), "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
//	this->gameSettings = new CGameSettings();
//
//	this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->getClass(), "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
//	this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->getClass(), "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
//
//	this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->getClass(), "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
//	
//	this->FieldIDs["rightClickDelayTimer"] = Java::Env->GetFieldID(this->getClass(), "rightClickDelayTimer", "I");
//
//	// not used lol
//	this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->getClass(), "clickMouse", "()V");
//	this->MethodIDs["getDebugFPS"] = Java::Env->GetMethodID(this->getClass(), "getDebugFPS", "()I");
//}

//jclass CMinecraft::getClass()
//{
//	return this->Class;
//}
//
//jobject CMinecraft::getInstance()
//{
//	return this->Instance;
//}
//EntityPlayerSP Minecraft::getThePlayer()
//{
//	if (!this->instance) return EntityPlayerSP();
//	return EntityPlayerSP(Ripterms::p_env->GetObjectField(this->instance, Ripterms::classcache->MinecraftClass.fields["thePlayer"]));
//}

CWorldClient CMinecraft::getTheWorld()
{
	if (!this->instance) return CWorldClient();
	return CWorldClient(Java::Env->GetObjectField(this->instance, StrayCache::minecraft_theWorld));
}

CEntityPlayerSP CMinecraft::getThePlayer()
{
	if (!this->instance) return CEntityPlayerSP();
	return CEntityPlayerSP(Java::Env->GetObjectField(this->instance, StrayCache::minecraft_thePlayer));
}

//GameSettings Minecraft::getGameSettings()
//{
//	if (!instance) return GameSettings();
//	return GameSettings(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->MinecraftClass.fields["gameSettings"]));
//}

CEntity CMinecraft::GetRenderViewEntity()
{
	return CEntity(Java::Env->CallObjectMethod(this->getInstance(),StrayCache::minecraft_getRenderViewEntity));
}

bool CMinecraft::IsInGuiState()
{
	if (Java::Env->IsSameObject(Java::Env->GetObjectField(this->getInstance(), StrayCache::minecraft_currentScreen), NULL))
	{
		return false;
	}
	return true;
}

int CMinecraft::getDebugFPS()
{
	return Java::Env->CallIntMethod(this->getInstance(), StrayCache::minecraft_getDebugFPS);
}

void CMinecraft::ClickMouse()
{
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::minecraft_clickMouse);

}

void CMinecraft::setRightClickDelayTimer(jint delay) {
	Java::Env->SetIntField(this->getInstance(), StrayCache::minecraft_rightClickDelayTimer, delay);
}

Object CMinecraft::getPlayerController()
{
	return Object(Java::Env->GetObjectField(this->getInstance(), StrayCache::minecraft_playerController));
}
CRenderManager CMinecraft::GetRenderManager() {
	if (!this->instance) return GetRenderManager();
	*renderManager = CRenderManager(Java::Env->GetObjectField(SDK::Minecraft->getInstance(), StrayCache::minecraft_renderManager));
	return *renderManager;
}
CMovingObjectPosition CMinecraft::GetMouseOver()
{
	return CMovingObjectPosition(Java::Env->GetObjectField(this->getInstance(), StrayCache::minecraft_objectMouseOver));
}
