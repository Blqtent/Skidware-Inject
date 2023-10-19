/*
#include "../../../../ext/minhook/minhook.h"
#include "../menu.h"
#include "../../sdk/sdk.h"
#include "../../moduleManager/commonData.h"
typedef void(__cdecl* OnUpdate) (void**, void**, jobject);
OnUpdate originalOnUpdate;
OnUpdate patchedOnUpdate;

template< typename T >
T Hook(const char* name, void* address, void* newfunc)
{
	void* ret = nullptr;

	const auto status = MH_CreateHook(address, newfunc, (LPVOID*)&ret);
	if (status != MH_OK)
	{
		//speak("[hook] Failed to hook %s [%s]", name, MH_StatusToString(status));
		return nullptr;
	}

	//speak("[hook] Hooked %s", name);
	return (T)ret;
}

void OnUpdatePatch(void** p1, void** p2, jobject packet)
{
	Logger::Log("E");
	originalOnUpdate(p1, p2, packet);
}

void Menu::HookUpdate()
{

	MH_STATUS status = MH_UNKNOWN;
	while (status != MH_OK)
	{
		if (JNIHelper::IsForge()) {
			CMinecraft* minecraftInstance = SDK::Minecraft;
			if (minecraftInstance->getClass() == NULL) return;

			jclass playerHandler;
			Java::AssignClass("net.minecraft.network.NetworkManager", playerHandler);
			jmethodID OnUpdateMethod = JNIHelper::env->GetMethodID(playerHandler, "func_179290_a", "(Lnet/minecraft/network/Packet;)V");
			if (OnUpdateMethod == NULL) return;

			patchedOnUpdate = OnUpdate(*(unsigned __int64*)(*(unsigned __int64*)OnUpdateMethod + 0x40));

			status = MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));
			if (status != MH_OK) Sleep(50);
			else return;
		}
		CMinecraft* minecraftInstance = SDK::Minecraft;
		if (minecraftInstance->getClass() == NULL) return;

		jclass playerHandler;
		Java::AssignClass("net.minecraft.network.NetworkManager", playerHandler);
		jmethodID OnUpdateMethod = JNIHelper::env->GetMethodID(playerHandler, "sendPacket", "(Lnet/minecraft/network/Packet;)V");
		if (OnUpdateMethod == NULL) return;

		patchedOnUpdate = OnUpdate(*(unsigned __int64*)(*(unsigned __int64*)OnUpdateMethod + 0x40));

		status = MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));
		if (status != MH_OK) Sleep(50);
	}
}

void Menu::UnhookUpdate() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
}
*/

#include "../../../../ext/minhook/minhook.h"
#include "../menu.h"
#include "../../sdk/sdk.h"
#include "../../moduleManager/commonData.h"
typedef void(__cdecl* OnPacket) (jobject);
OnPacket originalOnUpdate;
OnPacket patchedOnUpdate;
void OnUpdatePatch(jobject packet)
{
	//CommonData::getInstance()->post = true;
	Logger::Log("E");
	originalOnUpdate(packet);
}

void Menu::HookUpdate()
{
	Logger::Log("Hook Update");

	MH_STATUS status = MH_UNKNOWN;
	while (status != MH_OK)
	{
		if (JNIHelper::IsForge()) {
			CMinecraft* minecraftInstance = SDK::Minecraft;
			if (minecraftInstance->getClass() == NULL) return;
			jclass playerHandler;
			Java::AssignClass("net.minecraft.network.NetworkManager", playerHandler);
		
			jmethodID addToSendQueue;

			addToSendQueue = Java::Env->GetMethodID(playerHandler, "func_147297_a", "(Lnet/minecraft/network/Packet;)V");
		
			//if (addToSendQueue == NULL) return;

			patchedOnUpdate = OnPacket(*(unsigned __int64*)(*(unsigned __int64*)addToSendQueue + 0x40));

			status = MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));
			if (status != MH_OK) Sleep(50);
		}
		else {
			CMinecraft* minecraftInstance = SDK::Minecraft;
			if (minecraftInstance->getClass() == NULL) return;
			jclass playerHandler;
			Java::AssignClass("net.minecraft.network.NetworkManager", playerHandler);

			jmethodID addToSendQueue;

			addToSendQueue = Java::Env->GetMethodID(playerHandler, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");
	
			if (addToSendQueue == NULL) return;

			patchedOnUpdate = OnPacket(*(unsigned __int64*)(*(unsigned __int64*)addToSendQueue + 0x40));

			status = MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));
			if (status != MH_OK) Sleep(50);
		}
	}
	MH_EnableHook(MH_ALL_HOOKS);

	Logger::Log("Done");

}

void Menu::UnhookUpdate() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
}