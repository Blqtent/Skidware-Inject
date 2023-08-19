#include "base.h"
#include "sdk/sdk.h"

#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/combat/aimAssist.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"
#include "moduleManager/modules/combat/reach.h"
#include "moduleManager/modules/clicker/leftAutoClicker.h"
#include "moduleManager/modules/clicker/rightAutoClicker.h"
#include "moduleManager/modules/player/eagle.h"
#include "moduleManager/modules/player/fastplace.h"
#include "moduleManager/modules/combat/velocity.h"
#include "moduleManager/modules/blatent/killaura.h"
#include "moduleManager/modules/blatent/flight.h"
#include "moduleManager/modules/blatent/speed.h"
#include "moduleManager/modules/player/blink.h"
#include "moduleManager/modules/visual/cavefinder.h"
#include "moduleManager/modules/visual/fullbright.h"
#include "moduleManager/modules/blatent/nofall.h"
#include "moduleManager/modules/blatent/timerhack.h"
#include <cmath>
#include "moduleManager/modules/player/blink.h"
//#include "extension/scripting.hpp"

#include "menu/menu.h"
#include "moduleManager/modules/combat/antibot.h"
#include "moduleManager/modules/combat/teams.h"
#include "moduleManager/modules/blatent/longjump.h"
#include "moduleManager/ModuleManager.h"
#include "moduleManager/modules/blatent/tower.h"
#include "moduleManager/modules/player/autotool.h"

extern ImVec4 clear_col;
static int y;
void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running) return;
	const char* watermark = "Skidware By Smellon and Blqtent";
	// goofy ahh css
	float margin = 3;
	float font_size = 24;
	int m_iOffset = 0;

	ImVec2 screenSize = ImGui::GetWindowSize();
	ImVec2 textSize = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, watermark);
	float posX = screenSize.x - textSize.x - margin;
	float posY = screenSize.y - textSize.y - margin;
	
	Esp::getInstance()->RenderUpdate();
	AimAssist::getInstance()->RenderUpdate();
	//Blink::getInstance()->RenderUpdate();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImDrawList* d = ImGui::GetWindowDrawList();

	std::string skid;
	/*if (scripting::skidwareText == true) {
		skid = "LUA Test - Skidware V1.2";
	}
	if (scripting::skidwareText == false) {
		skid = "Skidware V1.2";
	}*/

	ImU32 watermarkCol = Menu::watermarkColor;

	d->AddText(Menu::Font, font_size, ImVec2(4, 4), watermarkCol, "Skidware V1.09");

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.IniFilename = NULL; // GET RID OF IMGUI.INI
	
	y = 24;
	/*
	if (Menu::useMCFont) {
		if (AimAssist::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Aimassist");
			y += 20;
		}
		if (Esp::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "ESP");
			y += 20;
		}
		if (LeftAutoClicker::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LeftClicker");
			y += 20;
		}
		if (RightAutoClicker::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "RightClicker");
			y += 20;
		}
		if (Reach::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Reach");
			y += 20;
		}
		if (Velocity::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Velocity");
			y += 20;
		}
		if (Eagle::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Eagle");
			y += 20;
		}
		if (Fastplace::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "FastPlace");
			y += 20;
		}
		if (Cavefinder::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "XRay");
			y += 20;
		}
		if (Antibot::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Antibot");
			y += 20;
		}

		if (Teams::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Teams");
			y += 20;
		}

		if (Killaura::getInstance()->getToggle()) {
			if (Killaura::getInstance()->getMode() == 0) {
				d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Legit");
			}
			else if (Killaura::getInstance()->getMode() == 1) {
				d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Normal");
			}
			y += 20;
		}
		if (TimerHack::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Timer");
			y += 20;
		}
		if (Fulbright::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fulbright");
			y += 20;

		}
		if (Speed::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Speed");
			y += 20;
		}
		if (Nofall::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Nofall");
			y += 20;
		}
		if (Flight::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Flight");
			y += 20;
		}
		if (Tower::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Scaffold");
			y += 20;
		}
>>>>>>> Stashed changes

		if (LongJump::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LongJump");
			y += 20;
		}
		if (Blink::getInstance()->getToggle()) {
			d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fakelag");
			y += 20;
		}
	}
<<<<<<< Updated upstream
	if (Speed::getInstance()->getToggle()) {
		d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Speed");
		y += 20;
	}
	if (Nofall::getInstance()->getToggle()) {
		d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Nofall");
		y += 20;
	}
	if (Flight::getInstance()->getToggle()) {
		d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Flight");
		y += 20;
	}

	if (LongJump::getInstance()->getToggle()) {
		d->AddText(Menu::Minecraft, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LongJump");
		y += 20;
	}

	*/
	//else {
		if (AimAssist::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Aimassist");
			y += 20;
		}
		if (Esp::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "ESP");
			y += 20;
		}
		if (LeftAutoClicker::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LeftClicker");
			y += 20;
		}
		if (RightAutoClicker::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "RightClicker");
			y += 20;
		}
		if (Reach::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Reach");
			y += 20;
		}
		if (Velocity::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Velocity");
			y += 20;
		}
		if (Eagle::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Eagle");
			y += 20;
		}
		if (Fastplace::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "FastPlace");
			y += 20;
		}
		if (AutoTool::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "AutoTool");
			y += 20;
		}
		if (Cavefinder::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "XRay");
			y += 20;
		}
		if (Antibot::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Antibot");
			y += 20;
		}

		if (Teams::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Teams");
			y += 20;
		}

		if (Killaura::getInstance()->getToggle()) {
			if (Killaura::getInstance()->getMode() == 0) {
				d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Legit");
			}
			else if (Killaura::getInstance()->getMode() == 1) {
				d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Normal");

			}
			y += 20;
		}
		if (TimerHack::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Timer");
			y += 20;
		}
		if (Fulbright::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fulbright");
			y += 20;

		}
		if (Speed::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Speed");
			y += 20;
		}
		if (Nofall::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Nofall");
			y += 20;
		}
		if (Flight::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Flight");
			y += 20;
		}
		if (Tower::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Scaffold");
			y += 20;
		}

		if (LongJump::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LongJump");
			y += 20;
		}
		if (Blink::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fakelag");
			y += 20;
		}
	//}
}