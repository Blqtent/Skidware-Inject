#include "menu.h"
#include "../../main.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <ShlObj.h>
#include <fstream>
#include <shellapi.h>

#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"
#include "../../../ext/imgui/imgui_impl_win32.h"
#include "../../../ext/imgui/imgui_impl_opengl2.h"

#include "../util/window/borderless.h"
#include "ImGuiUtils.h"
#include "../moduleManager/modules/visual/esp.h"

#include "../moduleManager/modules/combat/aimAssist.h"
#include "../moduleManager/modules/combat/reach.h"
#include "../moduleManager/modules/combat/antibot.h"
#include "../moduleManager/modules/clicker/leftAutoClicker.h"
#include "../moduleManager/modules/clicker/rightAutoClicker.h"
#include "../moduleManager/modules/player/fastplace.h"
#include "../moduleManager/modules/blatent/killaura.h"
#include "../moduleManager/modules/blatent/longjump.h"
#include "../moduleManager/modules/blatent/speed.h"
#include "../moduleManager/modules/blatent/flight.h"
#include "../moduleManager/modules/blatent/timerHack.h"

//#include "../moduleManager/modules/other/config.h"

#include "../sdk/net/minecraft/client/Minecraft.h"
#include "../util/logger.h"
//#include "../detach.cpp"
#include "../moduleManager/modules/combat/velocity.h"
#include "../moduleManager/modules/player/eagle.h"
#include "../util/window/bind.hpp"
#include "../extension/config.h"
#include "../moduleManager/modules/player/blink.h"
//#include "../moduleManager/modules/player/autotool.h"

#include "../moduleManager/modules/blatent/nofall.h"
#include "../moduleManager/modules/visual/fullbright.h"
#include "../moduleManager/modules/visual/cavefinder.h"


int currentTab = -1;
int currentTab2 = 0;
int currentTab3 = 0;
int currentTab4 = 0;
int currentTab5 = 0;
int currentTab6 = 0;
int currentTab7 = 0;
inline static int style = 0;
inline static const char* styleList[4]{ "Dark", "Light", "Classic", "Gold" };

void set_config(Config* config) {

	config->open();

	// AimAssist
	config->set<bool>("AimAssist", AimAssist::getInstance()->getToggle());
	config->set<bool>("AimAssistAdaptive", AimAssist::getInstance()->adaptive);
	config->set<float>("AimAssistAdaptiveOffset", AimAssist::getInstance()->adaptiveOffset);
	config->set<float>("AimAssistDistance", AimAssist::getInstance()->aimDistance);
	config->set<bool>("AimAssistFeedback", AimAssist::getInstance()->aimAssistFeedback);
	config->set<float>("AimAssistFOV", AimAssist::getInstance()->fov);
	config->set<bool>("AimAssistPitchInfluenced", AimAssist::getInstance()->pitchInfluenced);
	config->set<float>("AimAssistRandomPitch", AimAssist::getInstance()->randomPitch);
	config->set<float>("AimAssistRandomYaw", AimAssist::getInstance()->randomYaw);
	config->set<bool>("AimAssistFOVCircle", AimAssist::getInstance()->fovCircle);
	config->set<bool>("AimAssistVisibilityCheck", AimAssist::getInstance()->visibilityCheck);


	// AutoClicker
	config->set<bool>("LeftClicker", LeftAutoClicker::getInstance()->getToggle());
	config->set<bool>("RightClicker", RightAutoClicker::getInstance()->getToggle());
	config->set<float>("LeftMinCPS", LeftAutoClicker::getInstance()->leftMinCps);
	config->set<float>("LeftMaxCPS", LeftAutoClicker::getInstance()->leftMaxCps);
	config->set<float>("RightMinCPS", RightAutoClicker::getInstance()->rightMinCps);
	config->set<float>("RightMaxCPS", RightAutoClicker::getInstance()->rightMaxCps);
	config->set<bool>("BreakBlocks", LeftAutoClicker::getInstance()->ignoreBlocks);
	config->set<bool>("BlockHit", LeftAutoClicker::getInstance()->blockhit);
	config->set<float>("BlockHitChance", LeftAutoClicker::getInstance()->blockHitChance);

	// ESP
	config->set<bool>("ESP", Esp::getInstance()->getToggle());
	config->set<bool>("ESPBox", Esp::getInstance()->Box);
	config->set<bool>("ESPFilledBox", Esp::getInstance()->FilledBox);
	config->set<float>("ESPFilledBoxOpacity", Esp::getInstance()->FilledBoxOpacity);
	config->set<bool>("ESPHealthbar", Esp::getInstance()->HealthBar);
	config->set<bool>("ESPOutline", Esp::getInstance()->Outline);
	config->set<bool>("ESPTestCircles", Esp::getInstance()->TestCircles);
	config->set<bool>("ESPText", Esp::getInstance()->Text);
	config->set<bool>("ESPTextOutline", Esp::getInstance()->TextOutline);

	// Reach
	config->set<bool>("Reach", Reach::getInstance()->getToggle());
	config->set<bool>("ReachDistance", Reach::getInstance()->ReachDistance);

	// Velocity
	config->set<bool>("Velocity", Velocity::getInstance()->getToggle());
	//config->set<bool>("VelocityOnlyMoving", Velocity::getInstance()->onlyMoving);
	//config->set<float>("VelocityChance", Velocity::getInstance()->Chance);
	config->set<float>("VelocityHorizontal", Velocity::getInstance()->Horizontal);
	config->set<float>("VelocityVertical", Velocity::getInstance()->Vertical);

	// Eagle
	config->set<bool>("Eagle", Eagle::getInstance()->getToggle());

	// FastPlace
	config->set<bool>("FastPlace", Fastplace::getInstance()->getToggle());
	config->set<float>("FastPlaceDelay", Fastplace::getInstance()->delay);

	// Blink
	config->set<bool>("Blink", Blink::getInstance()->getToggle());

	// BHop
	config->set<bool>("BHop", Speed::getInstance()->getToggle());
	config->set<int>("BHopMode", Speed::getInstance()->getMode());
	config->set<float>("BHopSpeed", Speed::getInstance()->speed);

	// NoFall
	config->set<bool>("NoFall", Nofall::getInstance()->getToggle());
	config->set<int>("NoFallMode", Nofall::getInstance()->getMode());
	config->set<float>("NoFallSpeed", Nofall::getInstance()->speed);

	config->close();
}

void read_config(Config* config) {

	// AimAssist
	AimAssist::getInstance()->setToggle( config->get<bool>("AimAssist"));
	AimAssist::getInstance()->adaptive = config->get<bool>("AimAssistAdaptive");
	AimAssist::getInstance()->adaptiveOffset = config->get<float>("AimAssistAdaptiveOffset");
	AimAssist::getInstance()->aimDistance = config->get<float>("AimAssistDistance");
	AimAssist::getInstance()->aimAssistFeedback = config->get<bool>("AimAssistFeedback");
	AimAssist::getInstance()->fov = config->get<float>("AimAssistFOV");
	AimAssist::getInstance()->pitchInfluenced = config->get<float>("AimAssistPitchInfluenced");
	AimAssist::getInstance()->randomPitch = config->get<float>("AimAssistRandomPitch");
	AimAssist::getInstance()->randomYaw = config->get<float>("AimAssistRandomYaw");
	AimAssist::getInstance()->fovCircle = config->get<bool>("AimAssistFOVCircle");
	AimAssist::getInstance()->visibilityCheck = config->get<bool>("AimAssistVisibilityCheck");

	// AutoClicker
	LeftAutoClicker::getInstance()->setToggle(config->get<bool>("LeftClicker"));
	RightAutoClicker::getInstance()->setToggle( config->get<bool>("RightClicker"));
	LeftAutoClicker::getInstance()->leftMinCps = config->get<float>("LeftMinCPS");
	LeftAutoClicker::getInstance()->leftMaxCps = config->get<float>("LeftMaxCPS");
	RightAutoClicker::getInstance()->rightMinCps = config->get<float>("RightMinCPS");
	RightAutoClicker::getInstance()->rightMaxCps = config->get<float>("RightMaxCPS");
	LeftAutoClicker::getInstance()->ignoreBlocks = config->get<float>("BreakBlocks");
	LeftAutoClicker::getInstance()->blockhit = config->get<float>("BlockHit");
	LeftAutoClicker::getInstance()->blockHitChance = config->get<float>("BlockHitChance");

	// ESP
	Esp::getInstance()->setToggle( config->get<bool>("ESP"));
	Esp::getInstance()->Box = config->get<bool>("ESPBox");
	Esp::getInstance()->FilledBox = config->get<bool>("ESPFilledBox");
	Esp::getInstance()->FilledBoxOpacity = config->get<float>("ESPFilledBoxOpacity");
	Esp::getInstance()->HealthBar = config->get<bool>("ESPHealthbar");
	Esp::getInstance()->Outline = config->get<bool>("ESPOutline");
	Esp::getInstance()->TestCircles = config->get<bool>("ESPTestCircles");
	Esp::getInstance()->Text = config->get<bool>("ESPText");
	Esp::getInstance()->TextOutline = config->get<bool>("ESPTextOutline");

	// Reach
	Reach::getInstance()->setToggle( config->get<bool>("Reach"));
	Reach::getInstance()->ReachDistance = config->get<float>("ReachDistance");

	// Velocity
	Velocity::getInstance()->setToggle( config->get<bool>("Velocity"));
	//Velocity::getInstance()->onlyMoving = config->get<bool>("VelocityOnlyMoving");
	//Velocity::getInstance()->Chance = config->get<float>("VelocityChance");
	Velocity::getInstance()->Horizontal = config->get<float>("VelocityHorizontal");
	Velocity::getInstance()->Vertical = config->get<float>("VelocityVertical");

	// Eagle
	Eagle::getInstance()->setToggle( config->get<bool>("Eagle"));

	// FastPlace
	Fastplace::getInstance()->setToggle( config->get<bool>("FastPlace"));
	Fastplace::getInstance()->delay = config->get<float>("FastPlaceDelay");

	// Blink
	Blink::getInstance()->setToggle( config->get<bool>("Blink"));

	// BHop
	Speed::getInstance()->setToggle( config->get<bool>("BHop"));
	Speed::getInstance()->getMode() = config->get<int>("BHopMode");
	Speed::getInstance()->speed = config->get<float>("BHopSpeed");

	//NoFall
	Nofall::getInstance()->setToggle( config->get<bool>("NoFall"));
	Nofall::getInstance()->getMode() = config->get<int>("NoFallMode");
	Nofall::getInstance()->speed = config->get<float>("NoFallSpeed");
}

// Function to list all files in a folder (platform-specific)
std::vector<std::string> ListFilesInFolder(const std::string& folderPath, const std::string& extension)
{
	std::vector<std::string> fileNames;

	std::string searchPath = folderPath + "\\*." + extension;
	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				fileNames.push_back(findData.cFileName);
			}
		} while (FindNextFileA(hFind, &findData) != 0);

		FindClose(hFind);
	}

	return fileNames;
}

void Menu::RenderMenu()
{


	ImGui::SetNextWindowSize(ImVec2(675, 600));
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
	ImVec2 textSize = Menu::FontBold->CalcTextSizeA(28, FLT_MAX, 0.0f, "SKID");
	float posX = windowPos.x + (columnWidth / 2) - (textSize.x / 2);
	float posY = windowPos.y + 20;

	Menu::GlitchText("SKID", ImVec2(posX, posY), style == 1 ? ImColor(0, 0, 0) : ImColor(255, 255, 255));
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
			ImGui::SameLine();
			if (Menu::TabButton("Fullbright", (currentTab2 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab2 = 1;
			ImGui::SameLine();
			if (Menu::TabButton("Xray", (currentTab2 == 2 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab2 = 2;

			if (currentTab2 == 0) {
				Esp::getInstance()->getInstance()->RenderMenu();
				keybind::key_bind(Esp::getInstance()->getInstance()->getKey(), 125, 25);
			}
			
			if (currentTab2 == 1) {
				Fulbright::getInstance()->RenderMenu();
				keybind::key_bind(Fulbright::getInstance()->getKey(), 125, 25);
			}
			
			if (currentTab2 == 2) {
				Cavefinder::getInstance()->RenderMenu();
				keybind::key_bind(Cavefinder::getInstance()->getKey(), 125, 25);

			}
			//Fullbright::getInstance()->RenderMenu();
			//keybind::key_bind(Esp::getInstance()->getInstance()->getKey(), 150, 50);
			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		if (currentTab == 1)
		{
			if (Menu::TabButton("Aimassist", (currentTab3 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab3 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("Reach", (currentTab3 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab3 = 1;
			ImGui::SameLine();
			if (Menu::TabButton("Velocity", (currentTab3 == 2 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab3 = 2;
			ImGui::SameLine();
			if (Menu::TabButton("Antibot", (currentTab3 == 3 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab3 = 3;

			if (currentTab3 == 0) {
				AimAssist::getInstance()->RenderMenu();
				keybind::key_bind(AimAssist::getInstance()->getKey(), 125, 25);
			}
			
			if (currentTab3 == 1) {
				Reach::getInstance()->RenderMenu();
				keybind::key_bind(Reach::getInstance()->getKey(), 125, 25);
			}
			//keybind::key_bind(Reach::getInstance()->getKey(), 150, 50);
			if (currentTab3 == 2) {
				Velocity::getInstance()->RenderMenu();
				keybind::key_bind(Velocity::getInstance()->getKey(), 125, 25);
			}
			if (currentTab3 == 3) {
				Antibot::getInstance()->RenderMenu();
				keybind::key_bind(Antibot::getInstance()->getKey(), 125, 25);
			}

			//keybind::key_bind(Velocity::getInstance()->getKey(), 150, 50);

			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		if (currentTab == 2)
		{
			if (Menu::TabButton("LeftClicker", (currentTab4 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab4 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("RightClicker", (currentTab4 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab4 = 1;
			if (currentTab4 == 0) {
				LeftAutoClicker::getInstance()->RenderMenu();
				keybind::key_bind(LeftAutoClicker::getInstance()->getKey(), 125, 25);
			}
			if (currentTab4 == 1) {
				RightAutoClicker::getInstance()->RenderMenu();
				keybind::key_bind(RightAutoClicker::getInstance()->getKey(), 125, 25);
			}
			//keybind::key_bind(RightAutoClicker::getInstance()->getKey(), 150, 50);

			ImGui::InvisibleButton("", ImVec2(1, 100));
		}
		if (currentTab == 3) {
			if (Menu::TabButton("FastPlace", (currentTab5 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab5 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("Eagle", (currentTab5 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab5 = 1;
			if (currentTab5 == 0) {
				Fastplace::getInstance()->RenderMenu();
				keybind::key_bind(Fastplace::getInstance()->getKey(), 125, 25);
			}

			if (currentTab5 == 1) {
				Eagle::getInstance()->RenderMenu();
				keybind::key_bind(Eagle::getInstance()->getKey(), 125, 25);
			}
			//keybind::key_bind(Eagle::getInstance()->getKey(), 150, 50);

			ImGui::InvisibleButton("", ImVec2(1, 100));

		}
		if (currentTab == 5) {
			if (Menu::TabButton("Fakelag", (currentTab7 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab7 = 0;
			//ImGui::SameLine();
			//if (Menu::TabButton("Autotool", (currentTab7 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab7 = 1;

			if (currentTab7 == 0) {
				Blink::getInstance()->RenderMenu();
				keybind::key_bind(Blink::getInstance()->getKey(), 125, 25);
			}
			/*else if (currentTab7 == 1) {
				AutoTool::getInstance()->RenderMenu();
				keybind::key_bind(AutoTool::getInstance()->getKey(), 125, 25);
			}*/
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

		

			ImGui::Text("ESP Colors");
			ImGui::Separator();
			ImGui::ColorEdit4("ESP Box", Esp::getInstance()->BoxColor);
			ImGui::ColorEdit4("ESP Box Outline", Esp::getInstance()->OutlineColor);
			ImGui::ColorEdit4("ESP Filled Box", Esp::getInstance()->FilledBoxColor);
			ImGui::ColorEdit4("ESP Second Filled Box", Esp::getInstance()->SecondFilledBoxColor);
			ImGui::ColorEdit4("ESP Circles", Esp::getInstance()->TestCirclesColor);
			ImGui::ColorEdit4("ESP Text", Esp::getInstance()->TextColor);
			ImGui::ColorEdit4("ESP Text Outline", Esp::getInstance()->TextOutlineColor);
			ImGui::Separator();
			ImGui::Text("Menu Colors");
			ImGui::Separator();
			ImGui::Combo("GUI Style", &style, styleList, 4);
			ImGui::ColorEdit4("Watermark", (float*)&watermarkColor);
			ImGui::Separator();

			ImGui::InvisibleButton("", ImVec2(1, 100));

		}
		if (currentTab == 4) {
			if (Menu::TabButton("Killaura", (currentTab6 == 0 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 0;
			ImGui::SameLine();
			if (Menu::TabButton("Speed", (currentTab6 == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 1;
			ImGui::SameLine();
			if (Menu::TabButton("Nofall", (currentTab6 == 2 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 2;
			ImGui::SameLine();
			if (Menu::TabButton("Flight", (currentTab6 == 3 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 3;
			//ImGui::SameLine();
			if (Menu::TabButton("LongJump", (currentTab6 == 4 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 4;
			ImGui::SameLine();
			if (Menu::TabButton("Timer", (currentTab6 == 5 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab6 = 5;
			
			
			if (currentTab6 == 0) {
				Killaura::getInstance()->RenderMenu();
				keybind::key_bind(Killaura::getInstance()->getKey(), 125, 25);
			}
			if (currentTab6 == 1) {
				Speed::getInstance()->RenderMenu();
				keybind::key_bind(Speed::getInstance()->getKey(), 125, 25);
			}
			if (currentTab6 == 2) {
				Nofall::getInstance()->RenderMenu();
				keybind::key_bind(Nofall::getInstance()->getKey(), 125, 25);

			}
			if (currentTab6 == 3) {
				Flight::getInstance()->RenderMenu();
				keybind::key_bind(Flight::getInstance()->getKey(), 125, 25);

			}
			if (currentTab6 == 4) {
				LongJump::getInstance()->RenderMenu();
				keybind::key_bind(LongJump::getInstance()->getKey(), 125, 25);

			}
			if (currentTab6 == 5) {
				TimerHack::getInstance()->RenderMenu();

				keybind::key_bind(TimerHack::getInstance()->getKey(), 125, 25);

			}
			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		ImGui::PopID();

		ImGui::EndChild();
	}
	ImGui::PopID();

	ImGui::End();


}