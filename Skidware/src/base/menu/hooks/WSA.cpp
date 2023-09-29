#include "WSA.h"
#include "../menu.h"
#include "../../util/logger.h"
#include "../../../../ext/minhook/minhook.h"
#include "../../moduleManager/modules/player/blink.h"
#include "../../eventManager/EventManager.hpp"
#include "../../eventManager/events/EventPacketSend.h"


int(__stdcall* g_origWSASend)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);

int __stdcall WSASendHook(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	//EventManager::getInstance().call(EventPacketSend((const char*)lpBuffers));
	while (Blink::getInstance()->shouldSpoof) {
		Sleep(1);
	}

	if (Blink::getInstance()->getMode() == 0) {
		while (Blink::getInstance()->getToggle()) {
			Sleep(1);
		}
	}
	else if (Blink::getInstance()->getMode() == 1){
		while (Blink::getInstance()->getToggle() && (GetAsyncKeyState(Blink::getInstance()->getKey()))) {
			Sleep(1);
		}
	}

	else if (Blink::getInstance()->getMode() == 2 && Blink::getInstance()->getToggle() && Blink::getInstance()->timer % (int)Blink::getInstance()->Chance == 0) {
		//while (Blink::getInstance()->getToggle() && !Blink::getInstance()->Time.isElapsed()) {
		Sleep(Blink::getInstance()->Milliseonds);
		//}
	}

	else if (Blink::getInstance()->getMode() == 3 && Blink::getInstance()->getToggle() && Blink::getInstance()->timer % (int)Blink::getInstance()->Chance == 0 && Blink::getInstance()->target.getInstance()) {
		//while (Blink::getInstance()->getToggle() && !Blink::getInstance()->Time.isElapsed()) {
		Sleep(Blink::getInstance()->Milliseonds);
		//}
	}

	return g_origWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

int(__stdcall* g_origWSARecev)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
int __stdcall WSARecevHook(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{

	while (Blink::getInstance()->getToggle()) {

		Sleep(1);
	}
	return g_origWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

void Menu::Hook_WSA() {

	MH_CreateHookApi(L"Ws2_32.dll", "WSASend", WSASendHook, (void**)&g_origWSASend);
	MH_EnableHook(MH_ALL_HOOKS);

}

void Menu::Unhook_WSA() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
} 
