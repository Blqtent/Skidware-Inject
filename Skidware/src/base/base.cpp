#include "base.h"

#include "../main.hh"
#include "java/java.h"
#include "util/logger.h"
#include "menu/menu.h"
#include "moduleManager/ModuleManager.h"
#include "sdk/sdk.h"
#include "util/window/borderless.h"

#include "../../ext/minhook/minhook.h"

#include <thread>
#include <unordered_map>
#include "security/security.hpp"
#include "eventManager/events/EventKey.hpp"

#include "moduleManager/modules/blatent/flight.h"
#include "moduleManager/modules/blatent/killaura.h"
#include "moduleManager/modules/blatent/longjump.h"
#include "moduleManager/modules/blatent/nofall.h"
#include "moduleManager/modules/blatent/speed.h"

#include "moduleManager/modules/clicker/leftAutoClicker.h"
#include "moduleManager/modules/clicker/rightAutoClicker.h"

#include "moduleManager/modules/combat/aimAssist.h"
#include "moduleManager/modules/combat/antibot.h"
#include "moduleManager/modules/combat/teams.h"
#include "moduleManager/modules/combat/reach.h"
#include "moduleManager/modules/combat/velocity.h"

#include "moduleManager/modules/player/blink.h"
#include "moduleManager/modules/player/autotool.h"
#include "moduleManager/modules/player/eagle.h"
#include "moduleManager/modules/player/fastplace.h"

#include "moduleManager/modules/visual/cavefinder.h"
#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/visual/fullbright.h"
#include "moduleManager/modules/blatent/timerhack.h"
#include "moduleManager/modules/blatent/tower.h"
#include "moduleManager/modules/blatent/antivoid.h"
#include "moduleManager/modules/blatent/noslow.h"
#include "moduleManager/modules/blatent/criticals.h"
#include "patcher/patcher.h"

// LUA import
#include "extension/scripting.hpp"

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
	//KeyAuthApp.init();
	//KeyAuthApp.checkblack();
	MH_Initialize();
	//Logger::Init();
	//Logger::Log("1/6 Logger Initialized. \n");
	Java::Init();
	//Logger::Log("2/6 JVM Initialized. \n");
	SDK::Init();
	//Logger::Log("3/6 SDK Initialized. \n");
	Menu::Init();
	//Logger::Log("4/6 Menu Initialized. \n");
	//Patcher::Init();
	initModule();
	//Logger::Log("5/6 Modules Initialized. \n");
	initEvent();
	//Logger::Log("6/6 Events Initialized. \n");

	//Logger::Init();
	//scripting::luaThing();
	Base::Running = true;

	//Logger::Log("Complete. You may close this window. \n");
	//FreeConsole();
	
	//PlaySoundA("C:\Windows\Media\notify.wav", 0, 0);
	SDK::Minecraft->gameSettings->SetFullscreenKeyToNull();
	while (Base::Running)
	{
		
		if (IsKeyReleased(VK_F11)) {
			if (Borderless::Enabled)
				Borderless::Restore(Menu::HandleWindow);
			else
				Borderless::Enable(Menu::HandleWindow);
		}

		EventManager::getInstance().call(EventUpdate());

#ifndef _DEBUG
		//HideFromDebugger();
#endif

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		
#ifndef _DEBUG
		//Check();
#endif
	}

	Main::Kill();
}

void Base::initConsole() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

void Base::initEvent() {
	//EventManager::getInstance().reg(Events::EventUpdate, test);
	EventManager::getInstance().reg<EventKey>(handleEventKey);
	//EventManager::getInstance().reg<EventUpdate>(test);
}

void Base::initModule() {
	
	{
		
		ModuleManager::getInstance().addModule<Flight>(Flight::getInstance());
		ModuleManager::getInstance().addModule<Killaura>(Killaura::getInstance());
		ModuleManager::getInstance().addModule<LongJump>(LongJump::getInstance());
		ModuleManager::getInstance().addModule<Nofall>(Nofall::getInstance());
		ModuleManager::getInstance().addModule<Speed>(Speed::getInstance());
		ModuleManager::getInstance().addModule<TimerHack>(TimerHack::getInstance());
		ModuleManager::getInstance().addModule<Tower>(Tower::getInstance());
		ModuleManager::getInstance().addModule<Antivoid>(Antivoid::getInstance());
		ModuleManager::getInstance().addModule<Noslowdown>(Noslowdown::getInstance());
		ModuleManager::getInstance().addModule<Criticals>(Criticals::getInstance());
	}
	
	{
		ModuleManager::getInstance().addModule<LeftAutoClicker>(LeftAutoClicker::getInstance());
		ModuleManager::getInstance().addModule<RightAutoClicker>(RightAutoClicker::getInstance());
	}

	{
		ModuleManager::getInstance().addModule<AimAssist>(AimAssist::getInstance());
		ModuleManager::getInstance().addModule<Antibot>(Antibot::getInstance());
		ModuleManager::getInstance().addModule<Teams>(Teams::getInstance());
		ModuleManager::getInstance().addModule<Reach>(Reach::getInstance());
		ModuleManager::getInstance().addModule<Velocity>(Velocity::getInstance());
	}

	{
		ModuleManager::getInstance().addModule<Blink>(Blink::getInstance());
		ModuleManager::getInstance().addModule<AutoTool>(AutoTool::getInstance());
		ModuleManager::getInstance().addModule<Eagle>(Eagle::getInstance());
		ModuleManager::getInstance().addModule<Fastplace>(Fastplace::getInstance());
	}

	{
		ModuleManager::getInstance().addModule<Cavefinder>(Cavefinder::getInstance());
		ModuleManager::getInstance().addModule<Esp>(Esp::getInstance());
		ModuleManager::getInstance().addModule<Fulbright>(Fulbright::getInstance());
	}



}


void Base::handleEventKey(const EventKey k) {
	ModuleManager::getInstance().ProcessKeyEvent();
}

void Base::Kill()
{
	SDK::Minecraft->gameSettings->RestoreFullscreenKey();
	if (Borderless::Enabled)
		Borderless::Restore(Menu::HandleWindow);

	StrayCache::DeleteRefs();
	Menu::Kill();
	Logger::Kill();
	//Patcher::Kill();

	MH_Uninitialize();
	Java::Kill();
}