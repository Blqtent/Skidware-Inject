#pragma once

#include <Windows.h>
#include "base/base.h"
#include "auth/auth.hpp"
#include "../ext/jni/jni.h"
#include <unordered_map>
#include "Memory.h"
#include "base/security/ObfuscateString.hpp"

class Main
{
public:
	static void Init();
	static void Kill();

	static inline HMODULE HModule;
};

using namespace KeyAuth;

std::string name = "Skidware"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "BdKeh4OMgS"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "714e58d9f3c9a9cd1b472b1e9c40ccc7c89affa63b311a8c79f19cfb71d085f1"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting

api KeyAuthApp(name, ownerid, secret, version, url);

bool loginFailed = false;
bool isLoggedIn = false;

enum HackState
{
	ERR,
	INCOMPLETE,
	WORKING,
	SUCCESS
};

class Hack
{
public:
	Hack();
	~Hack() = default;

	auto GetInitializationState() const {
		return m_InitializationState;
	}

	HackState CleanupJVMTI() const;
	static HackState m_InitializationState;
private:
	bool m_CleanJVMTI;

	std::unique_ptr<Memory> m_Memory;
};

void __declspec(noinline) InjectionError(const char* message)
{
	/* It would be preferred that users don't bypass errors */

	/* TODO: Ideally, error codes/information should be passed to the UI */
	if (message != NULL)
		MessageBox(NULL, message, "Skidware", MB_ICONERROR | MB_OK);

	/*
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx
		xor esp, esp
		xor ebp, ebp
		jmp esp
	*/

	((DWORD(__cdecl*)())nullptr)();

	/* If they really want to hook, go ahead */
	for (;;)
	{
		exit(0);
		_Exit(0);
		_exit(0);
		quick_exit(0);
		ExitProcess(0);
	}
}