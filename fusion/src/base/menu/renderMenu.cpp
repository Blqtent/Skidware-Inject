#include "menu.h"
#include "../../main.h"

#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"
#include "../../../ext/imgui/imgui_impl_win32.h"
#include "../../../ext/imgui/imgui_impl_opengl2.h"

#include "../util/window/borderless.h"
#include "ImGuiUtils.h"
#include "../moduleManager/modules/visual/esp.h"
#include "../moduleManager/modules/visual/Fullbright.h"
#include "../moduleManager/modules/combat/aimAssist.h"
#include "../moduleManager/modules/combat/reach.h"
#include "../moduleManager/modules/clicker/leftAutoClicker.h"
#include "../moduleManager/modules/clicker/rightAutoClicker.h"
#include "../moduleManager/modules/player/fastplace.h"
#include "../moduleManager/modules/blatent/killaura.h"
#include "../moduleManager/modules/blatent/Strafe.h"
//#include "../moduleManager/modules/other/config.h"

#include "../sdk/net/minecraft/client/Minecraft.h"
#include "../util/logger.h"
//#include "../detach.cpp"
#include "../moduleManager/modules/combat/velocity.h"
#include "../moduleManager/modules/player/eagle.h"
#include "../util/window/bind.hpp"
#include "../extension/config.h"
#include "../renderLoop.cpp"
#include "../moduleManager/modules/player/blink.h"
#include "../moduleManager/modules/blatent/nofall.h"
int currentTab = -1;
int currentTab2 = 0;
int currentTab3 = 0;
int currentTab4 = 0;
int currentTab5 = 0;
int currentTab6 = 0;
int currentTab7 = 0;
inline static int style = 0;
inline static const char* styleList[4]{ "Dark", "Light", "Classic", "Gold"};
/*

DO NOT COPY & PASTE FUSIONS MENU!

Fusions menu is really not flexible at all, I *highly* discourage copying and pasting from fusions menu.
Although it looks good, it was my (deadshell's) first time making an imgui menu and it was kind of rushed to release fusion.

*/

void set_config(Config* config) {

	config->open();

	config->set<bool>("LeftClicker", LeftAutoClicker::Enabled);
	config->set<bool>("RightClicker", RightAutoClicker::Enabled);
	config->set<float>("LeftMinCPS", LeftAutoClicker::leftMinCps);
	config->set<float>("LeftMaxCPS", LeftAutoClicker::leftMaxCps);
	config->set<float>("RightMinCPS", RightAutoClicker::rightMinCps);
	config->set<float>("RightMaxCPS", RightAutoClicker::rightMaxCps);
	config->set<bool>("BreakBlocks", LeftAutoClicker::ignoreBlocks);
	config->set<bool>("BlockHit", LeftAutoClicker::blockhit);
	config->set<float>("BlockHitChance", LeftAutoClicker::blockHitChance);

	//config->set<bool>
	//Do all your stuff here
	config->close();
}

void read_config(Config* config) {
	LeftAutoClicker::Enabled = config->get<bool>("LeftClicker");
	RightAutoClicker::Enabled = config->get<bool>("RightClicker");
}

void Menu::RenderMenu()
{


	ImGui::SetNextWindowSize(ImVec2(650, 600));
	ImGui::Begin(Menu::Title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImVec2 idk = ImGui::GetWindowSize();
	if (style == 2)
		ImGui::StyleColorsClassic();
	else if (style == 1)
		ImGui::StyleColorsLight();
	else if (style == 0)
		ImGui::StyleColorsDark();
	else if (style == 3)
		ImGuiUtils::styleColorsGold();
		
	int buttonAmount = 6;
	int buttonHeight = 20;
	ImGui::PushID("Start");
	ImGui::Columns(2, "stuff");
	float columnWidth = 110;
	ImGui::SetColumnWidth(0, columnWidth);
	//ImGui::GetWindowDrawList()->AddText(Menu::Font, distTextSize, ImVec2(posX, posY), ImColor();
	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 textSize = Menu::FontBold->CalcTextSizeA(28, FLT_MAX, 0.0f, "SKIDWARE");
	float posX = windowPos.x + (columnWidth / 2) - (textSize.x / 2);
	float posY = windowPos.y + 20;

	Menu::GlitchText("SKIDWARE", ImVec2(posX, posY), style == 1 ? ImColor(0, 0, 0) : ImColor(255, 255, 255));
	ImGui::SetCursorPosY(textSize.y + 30);

	if (Menu::TabButton("Settings", (currentTab == 6 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 6;
	if (Menu::TabButton("Player", (currentTab == 5 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 5;
	if (Menu::TabButton("Blatent", (currentTab == 4 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 4;
	if (Menu::TabButton("Misc", (currentTab == 3 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 3;
	if (Menu::TabButton("Combat", (currentTab == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 1;
	if (Menu::TabButton("AutoClick", (currentTab == 2 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 2;
	if (Menu::TabButton("Visuals", (currentTab == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 0;
	textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, "Bind");

	//ImGui::InvisibleButton("", ImVec2(1, 100));
	ImGui::NextColumn();

	if (ImGui::BeginChild("child_2", { 0, 0 }, false)) {

		ImGui::PushID("menus");

		if (currentTab == 0)
		{
			if (Menu::TabButton("ESP", (currentTab2 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab2 = 0;

			if (currentTab2 == 0) {
				Esp::RenderMenu();
				keybind::key_bind(Esp::bind, 125, 25);

			}

			//Fullbright::RenderMenu();
			//keybind::key_bind(Esp::bind, 150, 50);
			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		if (currentTab == 1)
		{
			if (Menu::TabButton("Aimassist", (currentTab3 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab3 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("Reach", (currentTab3 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab3 = 1;
			ImGui::SameLine();
			if (Menu::TabButton("Velocity", (currentTab3 == 2 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab3 = 2;
			
			if (currentTab3 == 0) {
				AimAssist::RenderMenu();
				keybind::key_bind(AimAssist::bind, 125, 25);

			}
			//
			if (currentTab3 == 1) {
				Reach::RenderMenu();
				keybind::key_bind(Reach::bind, 125, 25);
			}
			//keybind::key_bind(Reach::bind, 150, 50);
			if (currentTab3 == 2) {
				Velocity::RenderMenu();
				keybind::key_bind(Velocity::bind, 125, 25);
			}

			//keybind::key_bind(Velocity::bind, 150, 50);

			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		if (currentTab == 2)
		{
			if (Menu::TabButton("LeftClicker", (currentTab4 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab4 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("RightClicker", (currentTab4 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab4 = 1;
			if (currentTab4 == 0) {
				LeftAutoClicker::RenderMenu();
				keybind::key_bind(LeftAutoClicker::bind, 125, 25);
			}
			if (currentTab4 == 1) {
				RightAutoClicker::RenderMenu();
				keybind::key_bind(RightAutoClicker::bind, 125, 25);
			}
			
			//keybind::key_bind(RightAutoClicker::bind, 150, 50);

			ImGui::InvisibleButton("", ImVec2(1, 100));
		}
		if (currentTab == 3) {
			if (Menu::TabButton("FastPlace", (currentTab5 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab5 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("Eagle", (currentTab5 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab5 = 1;
			if (currentTab5 == 0) {
				Fastplace::RenderMenu();
				keybind::key_bind(Fastplace::bind, 125, 25);
			}

			if (currentTab5 == 1) {
				Eagle::RenderMenu();
				keybind::key_bind(Eagle::bind, 125, 25);
			}
			//keybind::key_bind(Eagle::bind, 150, 50);

			ImGui::InvisibleButton("", ImVec2(1, 100));

		}
		if (currentTab == 5) {
			if (Menu::TabButton("Blink", (currentTab7 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab7 = 0;
			if (currentTab7 == 0) {
				Blink::RenderMenu();
				keybind::key_bind(Blink::bind, 125, 25);
			}

		}
		if (currentTab == 6) {
			Config* cfg = new Config("Main.cfg");
			if (ImGui::Button("Save Config")) {
				set_config(cfg);
			}
			if (ImGui::Button("Load Config")) {
				read_config(cfg);
			}

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 5));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.64, 0.2, 0.2, 0.5));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.74, 0.4, 0.4, 1));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0.4, 0.4, 1));

			if (ImGui::Button("Detach"))
			{
				//Detach();
				Base::Running = false;
			}

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();
			ImGui::PopStyleVar();
			ImGui::Text("GUI Style");
			ImGui::Combo("GUI Style", &style, styleList, 4);

			ImGui::InvisibleButton("", ImVec2(1, 100));

		}
		if (currentTab == 4) {
			if (Menu::TabButton("Killaura", (currentTab6 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("Strafe", (currentTab6 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 1;
			ImGui::SameLine();
			if (Menu::TabButton("Nofall", (currentTab6 == 2 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 2;
			if (currentTab6 == 0) {
				Killaura::RenderMenu();
				keybind::key_bind(Killaura::bind, 125, 25);
			}
			if (currentTab6 == 1) {
				Strafe::RenderMenu();
				keybind::key_bind(Strafe::bind, 125, 25);
			}
			if (currentTab6 == 2) {
				Nofall::RenderMenu();
				keybind::key_bind(Nofall::bind, 125, 25);

			}
			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		ImGui::PopID();

		ImGui::EndChild();
	}
	ImGui::PopID();

	ImGui::End();

	
}
