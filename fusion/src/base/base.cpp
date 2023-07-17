#include "base.h"

#include "../main.h"
#include "java/java.h"
#include "util/logger.h"
#include "menu/menu.h"
#include "moduleManager/moduleManager.h"
#include "sdk/sdk.h"
#include "util/window/borderless.h"

#include "../../ext/minhook/minhook.h"

#include <thread>
#include <unordered_map>

const char* GetWindowTitle(HWND hWnd)
{
	char windowTitle[128];
	GetWindowTextA(hWnd, windowTitle, 128);

	return windowTitle;
}

bool IsKeyReleased(int key)
{
	static std::unordered_map<int, bool> keyStates;

	bool currentState = (GetAsyncKeyState(key) & 0x8000) == 0;
	bool prevState = keyStates[key];
	keyStates[key] = currentState;

	return prevState && !currentState;
}

void Base::Init()
{

	MH_Initialize();

	Java::Init();
	SDK::Init();
	Menu::Init();
	ModuleManager::Init();
	//Logger::Init();
	Base::Running = true;
	
	SDK::Minecraft->gameSettings->SetFullscreenKeyToNull();
	while (Base::Running)
	{
		if (IsKeyReleased(VK_F11)) {
			if (Borderless::Enabled)
				Borderless::Restore(Menu::HandleWindow);
			else
				Borderless::Enable(Menu::HandleWindow);
		}

		ModuleManager::UpdateModules();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	Main::Kill();
}	

void Base::Kill()
{

	SDK::Minecraft->gameSettings->RestoreFullscreenKey();
	if (Borderless::Enabled)
		Borderless::Restore(Menu::HandleWindow);

	StrayCache::DeleteRefs();
	Java::Kill();
	Menu::Kill();
	Logger::Kill();

	MH_Uninitialize();
}