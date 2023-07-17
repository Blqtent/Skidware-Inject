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
#include <cmath>
extern ImVec4 clear_col;
void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running) return;
	const char* watermark = "Skidware By Smellon and Blqtent";
	// goofy ahh css
	float margin = 3;
	float font_size = 24;

	ImVec2 screenSize = ImGui::GetWindowSize();
	ImVec2 textSize = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, watermark);
	float posX = screenSize.x - textSize.x - margin;
	float posY = screenSize.y - textSize.y - margin;
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX + 1, posY), ImColor(255,255,255), watermark);
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX - 1, posY), ImColor(255, 255, 255), watermark);
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY + 1), ImColor(255, 255, 255), watermark);
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY - 1), ImColor(255, 255, 255), watermark);

	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY), ImColor(0, 0, 0), watermark);

	Esp::RenderUpdate();
	AimAssist::RenderUpdate();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImDrawList* d = ImGui::GetWindowDrawList();
	d->AddText(Menu::Font, font_size, ImVec2(4, 4), ImColor(0, 0, 200), "Skidware V1.2");
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
	/*
	if (AimAssist::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 4), ImColor(255, 255, 255), "Aimassist");
	if (Esp::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 24), ImColor(255, 255, 255), "ESP");
	if (LeftAutoClicker::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 44), ImColor(255, 255, 255), "LeftClicker");
	if (RightAutoClicker::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 64), ImColor(255, 255, 255), "RightClicker");
	if (Reach::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 84), ImColor(255, 255, 255), "Reach");
	if (Velocity::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 104), ImColor(255, 255, 255), "Velocity");
	if (Eagle::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 124), ImColor(255, 255, 255), "Eagle");
	if (Fastplace::Enabled)
		d->AddText(Menu::Font, font_size, ImVec2(4, 144), ImColor(255, 255, 255), "FastPlace");
	*/
	//Array List
	/*
	ImFont* mainfont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 20);
	ImGui::PushFont(mainfont);
	ImGui::SetNextWindowPos(ImVec2(1640, 0));
	ImGui::SetNextWindowSize(ImVec2(200, 250));
	ImGui::SetNextWindowBgAlpha(0.25f);
	
	bool* info_open = (bool*)0;
	ImGui::Begin("Info", info_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::Text(("Skidware V1.2"));
	ImGui::Separator();
	if (AimAssist::Enabled) {
		ImGui::Text(("Aimassist - " + std::to_string(std::roundf(AimAssist::smooth))).c_str());
	}
	if (Reach::Enabled) {
		ImGui::Text(("Reach - " + std::to_string(std::roundf(Reach::ReachDistance))).c_str());
	}
	if (LeftAutoClicker::Enabled) {
		ImGui::Text("LeftClicker");
	}
	if (RightAutoClicker::Enabled) {
		ImGui::Text("RightClicker");
	}
	if (Esp::Enabled) {
		ImGui::Text("ESP");
	}
	if (Eagle::Enabled) {
		ImGui::Text("Eagle");

	}
	if (Fastplace::Enabled) {
		ImGui::Text(("Fastplace"));

	}
	if (Velocity::Enabled) {
		ImGui::Text("Velocity");

	}
	ImGui::PopFont();
	*/
}