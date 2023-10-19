#include "patcher.h"
#include "../util/logger.h"
#include "../../../ext/minhook/minhook.h"

#include "../../../ext/jni/jni.h"
#include "../sdk/sdk.h"

typedef void(__cdecl* OnUpdate) (void**, void**);
OnUpdate originalOnUpdate;
OnUpdate patchedOnUpdate;
void OnUpdatePatch(void** p1, void** p2)
{
	originalOnUpdate(p1, p2);
}

typedef void(__cdecl* OnTick) (void**, void**);
OnTick originalOnTick;
OnTick patchedOnTick;
void OnTickPatch(void** p1, void** p2)
{
	originalOnTick(p1, p2);
}

typedef void(__cdecl* SetSprinting) (void**, void**, jobject);
SetSprinting originalSetSprinting;
SetSprinting patchedSetSprinting;
void SetSprintingPatch(void** t1, void** t2, jobject packet)
{

	originalSetSprinting(t1, t2, packet);
}


/*
void Patching::PatchOnUpdate()
{
	MH_STATUS status = MH_UNKNOWN;
	while (status != MH_OK)
	{
		Minecraft minecraftInstance = LaunchWrapper::getMinecraft();
		if (minecraftInstance.GetCurrentClass() == NULL) return;

		jmethodID OnUpdateMethod = JNIHelper::env->GetMethodID(minecraftInstance.GetCurrentClass(), "func_99999_d", "()V"); // maybe i should use func_71411_J instead?
		if (OnUpdateMethod == NULL) return;

		patchedOnUpdate = OnUpdate(*(unsigned __int64*)(*(unsigned __int64*)OnUpdateMethod + 0x40));

		status = MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));
		if (status != MH_OK) Sleep(50);
	}

	Logger::LogDebug("OnUpdate Patched");
}

void Patching::PatchOnTick()
{
	MH_STATUS status = MH_UNKNOWN;
	while (status != MH_OK)
	{
		Minecraft minecraftInstance = LaunchWrapper::getMinecraft();
		if (minecraftInstance.GetCurrentClass() == NULL) return;

		jmethodID OnTickMethod = JNIHelper::env->GetMethodID(minecraftInstance.GetCurrentClass(), "func_71407_l", "()V");
		if (OnTickMethod == NULL) return;

		patchedOnTick = OnTick(*(unsigned __int64*)(*(unsigned __int64*)OnTickMethod + 0x40));

		status = MH_CreateHook(patchedOnTick, &OnTickPatch, (void**)(&originalOnTick));
		if (status != MH_OK) Sleep(50);
	}

	Logger::LogDebug("OnTick Patched");
}
*/
void Patching::PatchSetSprinting()
{
	MH_STATUS status = MH_UNKNOWN;
	while (status != MH_OK)
	{
		CMinecraft* minecraftInstance = SDK::Minecraft;
		if (minecraftInstance->getInstance() == NULL) return;

		CEntityPlayerSP* localPlayerInstance = minecraftInstance->thePlayer;
		if (localPlayerInstance->getInstance() == NULL) return;
		jclass playerHandler;
		Java::AssignClass("net.minecraft.network.NetworkManager", playerHandler);
		jmethodID SetSprintingMethod = JNIHelper::env->GetMethodID(playerHandler, "func_179290_a", "(Lnet/minecraft/network/Packet;)V");
		if (SetSprintingMethod == NULL) return;

		patchedSetSprinting = SetSprinting(*(unsigned __int64*)(*(unsigned __int64*)SetSprintingMethod + 0x40));

		status = MH_CreateHook(patchedSetSprinting, &SetSprintingPatch, (void**)(&originalSetSprinting));
		if (status != MH_OK) Sleep(50);
	}

	//Logger::Log("SetSprinting Patched");
}


void Patching::ApplyPatches()
{
	Logger::Log("Initializing Hooks...");
	MH_Initialize();
	Logger::Log("Initializing Hooks Done...");

	PatchSetSprinting();
	Logger::Log("Patch...");

	MH_EnableHook(MH_ALL_HOOKS);
}

void Patching::UnapplyPatches()
{
	MH_DisableHook(MH_ALL_HOOKS);

	//MH_Uninitialize();
}