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
#include "menu/jhook.h"
// LUA import
#include "extension/scripting.hpp"
#include "moduleManager/modules/player/disabler.h"

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
	Logger::Init();
	Logger::Log("1/7 Logger Initialized. \n");
	Java::Init();
	Logger::Log("2/7 JVM Initialized. \n");
	SDK::Init();
	Logger::Log("3/7 SDK Initialized. \n");
	Menu::Init();
	Logger::Log("4/7 Menu Initialized. \n");
	//jhook::apply_moveEntityHook();
	Logger::Log("5/7 Hooks Initialized. \n");

	initModule();
	Logger::Log("6/7 Modules Initialized. \n");
	initEvent();
	Logger::Log("7/7 Events Initialized. \n");
	InitUpdateMessage();
	//Logger::Kill();
	//Logger::Init();
	//scripting::luaThing();
	Base::Running = true;

	//Logger::Log("Complete. You may close this window. \n");
	//FreeConsole();
	
	//PlaySoundA("C:\\Windows\\Media\\notify.wav", 0, 0);
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

		HKEY key = nullptr;

		//if (RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Skidware\\Loader\\user", 0, KEY_ALL_ACCESS, &key))
		//{
			//abort();
		//}

		//RegDeleteKey(HKEY_CURRENT_USER, "SOFTWARE\\Skidware\\Loader\\user");
		

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

static void handleUpdate(JNIEnv* env)
{
	MSG msg;
	while (PeekMessage(
		&msg,     // message information
		NULL,     // handle to window
		0,        // first message
		0,        // last message
		PM_REMOVE // removal options
	))
	{
		if (msg.message == WM_QUIT)
			break;
		if (msg.message == WM_KEYDOWN)
		{
			Base::justPressed = true;
			if (msg.wParam == Menu::Keybind)
				Menu::Open = !Menu::Open;
			if (msg.wParam == VK_ESCAPE && Menu::Open)
				Menu::Open = false;
			ModuleManager::getInstance().ProcessKeyEvent(msg.wParam);
			//EventManager::getInstance().call(EventKey(msg.wParam));
		}

		/*UINT value1 = msg.message;
		UINT value2 = msg.wParam;
		UINT value3 = msg.lParam;
		*/


		TranslateMessage(&msg); // ·¢³öWM_CHAR

		
		//(jint)value1, (jlong)value2, (jlong)value3);

		DispatchMessage(&msg);
	}
}

void Base::initConsole() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

int Base::InitUpdateMessage() {
	JNINativeMethod native[] = {
		{const_cast<char*>("nUpdate"), const_cast<char*>("()V"), (void*)(handleUpdate)} };
	jclass clazz{};
	Java::AssignClass("org.lwjgl.opengl.WindowsDisplay", clazz);
	if (!clazz)
	{
		Java::Env->FindClass("org/lwjgl/opengl/WindowsDisplay");
	}
	if (!clazz)
	{
		std::cout << "Unable to find windowsDisplay Class" << std::endl;
		return -1;
	}
	return Java::Env->RegisterNatives(clazz, native, sizeof(native) / sizeof(JNINativeMethod));

}

void Base::initEvent() {
	//EventManager::getInstance().reg(Events::EventUpdate, test);
	//EventManager::getInstance().reg<EventKey>(handleEventKey);
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
		ModuleManager::getInstance().addModule<Disabler>(Disabler::getInstance());
	}

	{
		ModuleManager::getInstance().addModule<Cavefinder>(Cavefinder::getInstance());
		ModuleManager::getInstance().addModule<Esp>(Esp::getInstance());
		ModuleManager::getInstance().addModule<Fulbright>(Fulbright::getInstance());
	}



}


void Base::handleEventKey(int key) {
	ModuleManager::getInstance().ProcessKeyEvent(key);
}

void Base::Kill()
{
	SDK::Minecraft->gameSettings->RestoreFullscreenKey();
	if (Borderless::Enabled)
		Borderless::Restore(Menu::HandleWindow);

	StrayCache::DeleteRefs();
	auto og = GetProcAddress(GetModuleHandle("lwjgl64.dll"), "Java_org_lwjgl_opengl_WindowsDisplay_nUpdate");
	JNINativeMethod native[] = {
		{const_cast<char*>("nUpdate"), const_cast<char*>("()V"), (void*)(og)} };
	std::cout << "0g: " << std::hex << std::uppercase << og << std::endl;
	if (og != nullptr)
	{
		jclass clazz{};
		Java::AssignClass("org.lwjgl.opengl.WindowsDisplay", clazz);
		if (!clazz)
		{
			std::cout << "Unable to find windowsDisplay Class" << std::endl;
			Java::Env->FindClass("org/lwjgl/opengl/WindowsDisplay");
		}
		if (clazz)
		{
			Java::Env->RegisterNatives(clazz, native, sizeof(native) / sizeof(JNINativeMethod));
		}
		else {
			std::cout << "Unable to find windowsDisplay Class 2" << std::endl;
		}

	}
	Logger::Kill();
	//Patcher::Kill();
	//Patching::UnapplyPatches();
	Menu::Kill();

	MH_Uninitialize();
	Java::Kill();
}