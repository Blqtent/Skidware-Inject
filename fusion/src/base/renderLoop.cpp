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
#include <cmath>
#include "moduleManager/modules/player/blink.h"
//#include "extension/scripting.hpp"

#include "menu/menu.h"
#include "moduleManager/modules/combat/antibot.h"
#include "moduleManager/modules/blatent/longjump.h"

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
	//ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX + 1, posY), ImColor(255,255,255), watermark);
	//ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX - 1, posY), ImColor(255, 255, 255), watermark);
	//ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY + 1), ImColor(255, 255, 255), watermark);
	//ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY - 1), ImColor(255, 255, 255), watermark);

	//ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY), ImColor(0, 0, 0), watermark);

	Esp::RenderUpdate();
	AimAssist::RenderUpdate();
	//Blink::RenderUpdate();
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

	d->AddText(Menu::Font, font_size, ImVec2(4, 4), watermarkCol, "Skidware V1.08");
	//d->AddText(Menu::Font, font_size, ImVec2(4, 20), watermarkCol, ("FPS: " + std::to_string(static_cast<SDK::Minecraft->getDebugFPS())).c_str());

	/*io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	//ImGui::StyleColorsDark();


	ImGuiStyle* Style = &ImGui::GetStyle();
	ImGui::StyleColorsDark();
	ImFont* mainfont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 20);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	Style->WindowRounding = 0;
	Style->WindowBorderSize = 0;

	ImGui::GetStyle().ScrollbarRounding = 5.0f;*/

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.IniFilename = NULL; // GET RID OF IMGUI.INI
	
	y = 24;

	if (AimAssist::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Aimassist");
		y += 20;
	}
	if (Esp::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "ESP");
		y += 20;
	}
	if (LeftAutoClicker::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LeftClicker");
		y += 20;
	}
	if (RightAutoClicker::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "RightClicker");
		y += 20;
	}
	if (Reach::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Reach");
		y += 20;
	}
	if (Velocity::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Velocity");
		y += 20;
	}
	if (Eagle::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Eagle");
		y += 20;
	}
	if (Fastplace::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "FastPlace");
		y += 20;
	}
	if (Cavefinder::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "XRay");
		y += 20;
	}
	if (Antibot::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Antibot");
		y += 20;
	}
	if (Killaura::Enabled) {
		if (Killaura::mode == 0) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Legit");
		}
		else if (Killaura::mode == 1) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Normal");

		}
		y += 20;
	}
	if (Blink::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fakelag");
		y += 20;
	}
	if (Fulbright::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fulbright");
		y += 20;

	}
	if (Speed::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Speed");
		y += 20;
	}
	if (Nofall::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Nofall");
		y += 20;
	}
	if (Flight::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Flight");
		y += 20;
	}
	
	if (LongJump::Enabled) {
		d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LongJump");
		y += 20;
	}
	
}