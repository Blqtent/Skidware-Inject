#include "main.hh"
#include <random>
#include "base/security/ObfuscateString.hpp"

std::unique_ptr<Hack> g_Instance;

bool IsBadReadPtr(void* p)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	if (::VirtualQuery(p, &mbi, sizeof(mbi)))
	{
		const DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);

		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

		return b;
	}
	return true;
}

HackState Hack::CleanupJVMTI() const
{
	if (!m_CleanJVMTI)
		return INCOMPLETE;

	const auto jvm = (uintptr_t)GetModuleHandleW(L"jvm.dll");

#pragma region offsets
	const auto isJvm16 = true;

	const auto isCustomJvm8 = false;

	const auto _globally_initialized_offset = isJvm16 ? 0x16 : 0x7;
	const auto always_capabilities_startOffset = isJvm16 ? 0x0 : 0x50;
	const auto always_capabilities_size = isJvm16 ? 0x68 : 0x58;
	const auto ext_functions_offset = (isJvm16 || isCustomJvm8) ? 0x1A : 0x16; // 0x1A feather jvm
	const auto ext_functions_startOffset = isJvm16 ? 0x0 : 0x8;
	constexpr auto ext_functions_size = 0x10; // 8 & 16
	constexpr auto _head_environment_startOffset = 0x8; // 8 & 16
	constexpr auto _head_environment_size = 0x10; // 8 & 16
	const auto JvmtiEventControllerPrivate__initialized_offset = isJvm16 ? 0x10 : 0x8;
	constexpr auto JvmtiEventControllerPrivate__initialized_size = 0x10; // 8 & 16
#pragma endregion

	const auto _initialized = m_Memory->GetAddress(m_Memory->FindPattern(jvm, "80 3D ? ? ? 00 00 0F 85 ? ? ? ? 83 3D ? ? ? ? ? 48 89 58 F8") + 0x2, 0x1);
	const auto _globally_initialized = m_Memory->GetAddress(m_Memory->FindPattern(jvm, "75 16 E8 ? ? ? ? E8 ? ? ? ?") - (_globally_initialized_offset - 0x2), 0x1);
	const auto always_capabilities = m_Memory->GetAddress(m_Memory->FindPattern(jvm, "22 05 ? ? ? ? 41 88 00") + 0x2);
	const auto ext_functions = m_Memory->GetAddress(m_Memory->FindPattern(jvm, "0F 8C ? ? ? ? 8B 00") - (ext_functions_offset - 0x3));

	if (IsBadReadPtr(_initialized) || IsBadReadPtr(_globally_initialized) || IsBadReadPtr(always_capabilities) || IsBadReadPtr(ext_functions))
	{
		return ERR;
	}

	*_initialized = 0;
	*_globally_initialized = 0;

	ZeroMemory(always_capabilities - always_capabilities_startOffset, always_capabilities_size);
	ZeroMemory(ext_functions - ext_functions_startOffset, ext_functions_size);
	ZeroMemory(_globally_initialized - JvmtiEventControllerPrivate__initialized_offset, JvmtiEventControllerPrivate__initialized_size);
	return SUCCESS;
}

void Main::Init()
{
	// Only for release DLL
	/*if (GlobalFindAtom("U2tpZHdhcmUgVjEuMTE") == 0)
	{
		//MessageBoxA(NULL, "Atom", "Skidware", MB_OK | MB_ICONINFORMATION);
		((DWORD(__cdecl*)())nullptr)();

		for (;;)
		{
			exit(0);
			_Exit(0);
			_exit(0);
			quick_exit(0);
			ExitProcess(0);
		}
	}*/
	Base::Init();
	const auto code = g_Instance->CleanupJVMTI();
	if (code == ERR) {
		MessageBox(NULL, "Fatal error", "Skidware", MB_ICONERROR | MB_OK);

		((DWORD(__cdecl*)())nullptr)();

		for (;;)
		{
			exit(0);
			_Exit(0);
			_exit(0);
			quick_exit(0);
			ExitProcess(0);
		}
	}
}

void Main::Kill()
{
	Base::Kill();
	FreeLibraryAndExitThread(Main::HModule, 0);
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Main::HModule = hModule;
		DisableThreadLibraryCalls(hModule);

		HANDLE hThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main::Init), hModule, 0, nullptr);

		if (hThread) CloseHandle(hThread);
	}

	return TRUE;
}