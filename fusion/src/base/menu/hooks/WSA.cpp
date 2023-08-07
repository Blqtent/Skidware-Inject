#include "WSA.h"

#include "../menu.h"
#include "../../util/logger.h"
#include "../../../../ext/minhook/minhook.h"
#include "../../moduleManager/modules/player/blink.h"

//if (Blink::throttle && (GetTickCount64() - timer > Blink::Milliseonds)) {
	//timer = GetTickCount64();

	//return g_origWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
//}
int(__stdcall* g_origWSASend)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
int __stdcall WSASendHook(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	/*
	if (!Blink::Enabled)
		return g_origWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);;

	while (GetAsyncKeyState(Blink::bind) & 0x8000 && (GetTickCount64() - Blink::timer < Blink::Milliseonds * 1000)) {
		Sleep(1);
	}
	*/
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