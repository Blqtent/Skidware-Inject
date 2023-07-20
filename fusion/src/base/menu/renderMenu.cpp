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
#include "../moduleManager/modules/player/blink.h"
#include "../moduleManager/modules/blatent/nofall.h"
#include "../../lua/lua.hpp"

int currentTab = -1;
int currentTab2 = 0;
int currentTab3 = 0;
int currentTab4 = 0;
int currentTab5 = 0;
int currentTab6 = 0;
int currentTab7 = 0;
inline static int style = 0;
inline static const char* styleList[4]{ "Dark", "Light", "Classic", "Gold"};

void set_config(Config* config) {

	config->open();

	// AimAssist
	config->set<bool>("AimAssist", AimAssist::Enabled);
	config->set<bool>("AimAssistAdaptive", AimAssist::adaptive);
	config->set<float>("AimAssistAdaptiveOffset", AimAssist::adaptiveOffset);
	config->set<float>("AimAssistDistance", AimAssist::aimDistance);
	config->set<bool>("AimAssistFeedback", AimAssist::aimAssistFeedback);
	config->set<float>("AimAssistFOV", AimAssist::fov);
	config->set<bool>("AimAssistPitchInfluenced", AimAssist::pitchInfluenced);
	config->set<float>("AimAssistRandomPitch", AimAssist::randomPitch);
	config->set<float>("AimAssistRandomYaw", AimAssist::randomYaw);
	config->set<bool>("AimAssistFOVCircle", AimAssist::fovCircle);
	config->set<bool>("AimAssistVisibilityCheck", AimAssist::visibilityCheck);


	// AutoClicker
	config->set<bool>("LeftClicker", LeftAutoClicker::Enabled);
	config->set<bool>("RightClicker", RightAutoClicker::Enabled);
	config->set<float>("LeftMinCPS", LeftAutoClicker::leftMinCps);
	config->set<float>("LeftMaxCPS", LeftAutoClicker::leftMaxCps);
	config->set<float>("RightMinCPS", RightAutoClicker::rightMinCps);
	config->set<float>("RightMaxCPS", RightAutoClicker::rightMaxCps);
	config->set<bool>("BreakBlocks", LeftAutoClicker::ignoreBlocks);
	config->set<bool>("BlockHit", LeftAutoClicker::blockhit);
	config->set<float>("BlockHitChance", LeftAutoClicker::blockHitChance);

	// ESP
	config->set<bool>("ESP", Esp::Enabled);
	config->set<bool>("ESPBox", Esp::Box);
	config->set<bool>("ESPFilledBox", Esp::FilledBox);
	config->set<float>("ESPFilledBoxOpacity", Esp::FilledBoxOpacity);
	config->set<bool>("ESPHealthbar", Esp::HealthBar);
	config->set<bool>("ESPOutline", Esp::Outline);
	config->set<bool>("ESPTestCircles", Esp::TestCircles);
	config->set<bool>("ESPText", Esp::Text);
	config->set<bool>("ESPTextOutline", Esp::TextOutline);

	// Reach
	config->set<bool>("Reach", Reach::Enabled);
	config->set<bool>("ReachDistance", Reach::ReachDistance);

	// Velocity
	config->set<bool>("Velocity", Velocity::Enabled);
	config->set<bool>("VelocityOnlyMoving", Velocity::onlyMoving);
	config->set<float>("VelocityChance", Velocity::Chance);
	config->set<float>("VelocityHorizontal", Velocity::Horizontal);
	config->set<float>("VelocityVertical", Velocity::Vertical);

	// Eagle
	config->set<bool>("Eagle", Eagle::Enabled);

	// FastPlace
	config->set<bool>("FastPlace", Fastplace::Enabled);
	config->set<float>("FastPlaceDelay", Fastplace::delay);

	// Blink
	config->set<bool>("Blink", Blink::Enabled);

	// BHop
	config->set<bool>("BHop", Strafe::Enabled);
	config->set<int>("BHopMode", Strafe::mode);
	config->set<float>("BHopSpeed", Strafe::speed);

	// NoFall
	config->set<bool>("NoFall", Nofall::Enabled);
	config->set<int>("NoFallMode", Nofall::mode);
	config->set<float>("NoFallSpeed", Nofall::speed);

	config->close();
}

void read_config(Config* config) {

	// AimAssist
	AimAssist::Enabled = config->get<bool>("AimAssist");
	AimAssist::adaptive = config->get<bool>("AimAssistAdaptive");
	AimAssist::adaptiveOffset = config->get<float>("AimAssistAdaptiveOffset");
	AimAssist::aimDistance = config->get<float>("AimAssistDistance");
	AimAssist::aimAssistFeedback = config->get<bool>("AimAssistFeedback");
	AimAssist::fov = config->get<float>("AimAssistFOV");
	AimAssist::pitchInfluenced = config->get<float>("AimAssistPitchInfluenced");
	AimAssist::randomPitch = config->get<float>("AimAssistRandomPitch");
	AimAssist::randomYaw = config->get<float>("AimAssistRandomYaw");
	AimAssist::fovCircle = config->get<bool>("AimAssistFOVCircle");
	AimAssist::visibilityCheck = config->get<bool>("AimAssistVisibilityCheck");

	// AutoClicker
	LeftAutoClicker::Enabled = config->get<bool>("LeftClicker");
	RightAutoClicker::Enabled = config->get<bool>("RightClicker");
	LeftAutoClicker::leftMinCps = config->get<float>("LeftMinCPS");
	LeftAutoClicker::leftMaxCps = config->get<float>("LeftMaxCPS");
	RightAutoClicker::rightMinCps = config->get<float>("RightMinCPS");
	RightAutoClicker::rightMaxCps = config->get<float>("RightMaxCPS");
	LeftAutoClicker::ignoreBlocks = config->get<float>("BreakBlocks");
	LeftAutoClicker::blockhit = config->get<float>("BlockHit");
	LeftAutoClicker::blockHitChance = config->get<float>("BlockHitChance");

	// ESP
	Esp::Enabled = config->get<bool>("ESP");
	Esp::Box = config->get<bool>("ESPBox");
	Esp::FilledBox = config->get<bool>("ESPFilledBox");
	Esp::FilledBoxOpacity = config->get<float>("ESPFilledBoxOpacity");
	Esp::HealthBar = config->get<bool>("ESPHealthbar");
	Esp::Outline = config->get<bool>("ESPOutline");
	Esp::TestCircles = config->get<bool>("ESPTestCircles");
	Esp::Text = config->get<bool>("ESPText");
	Esp::TextOutline = config->get<bool>("ESPTextOutline");

	// Reach
	Reach::Enabled = config->get<bool>("Reach");
	Reach::ReachDistance = config->get<float>("ReachDistance");

	// Velocity
	Velocity::Enabled = config->get<bool>("Velocity");
	Velocity::onlyMoving = config->get<bool>("VelocityOnlyMoving");
	Velocity::Chance = config->get<float>("VelocityChance");
	Velocity::Horizontal = config->get<float>("VelocityHorizontal");
	Velocity::Vertical = config->get<float>("VelocityVertical");

	// Eagle
	Eagle::Enabled = config->get<bool>("Eagle");

	// FastPlace
	Fastplace::Enabled = config->get<bool>("FastPlace");
	Fastplace::delay = config->get<float>("FastPlaceDelay");

	// Blink
	Blink::Enabled = config->get<bool>("Blink");

	// BHop
	Strafe::Enabled = config->get<bool>("BHop");
	Strafe::mode = config->get<int>("BHopMode");
	Strafe::speed = config->get<float>("BHopSpeed");

	//NoFall
	Nofall::Enabled = config->get<bool>("NoFall");
	Nofall::mode = config->get<int>("NoFallMode");
	Nofall::speed = config->get<float>("NoFallSpeed");
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

			// Creating the skidware folder so we can store LUAs there.
			//CreateSkidwareFolder();

			// Get the list of Lua script files from the desired folder
			/*std::vector<std::string> scriptFiles = ListFilesInFolder("C:\\", "lua");

			// Create a listbox to display the Lua script files
			static int selectedItem = -1;
			ImGui::ListBoxHeader("##script_listbox");
			for (int i = 0; i < scriptFiles.size(); ++i)
			{
				bool isSelected = (selectedItem == i);
				if (ImGui::Selectable(scriptFiles[i].c_str(), isSelected))
				{
					selectedItem = i;
					// Implement the action you want to perform when a script is selected
					// e.g., open or execute the selected script
				}
			}
			ImGui::ListBoxFooter();

			// Load selected script button
			if (ImGui::Button("Load selected", { 160.0f, 25.0f }))
			{
				if (selectedItem >= 0 && selectedItem < scriptFiles.size())
				{
					// In your main function or where you initialize Lua
					lua_State* L = luaL_newstate(); // Create a new Lua state
					luaL_openlibs(L); // Open standard Lua libraries

					//scripting::luaThing(L, scriptFiles[selectedItem]);

					// After you're done with Lua, close the Lua state
					lua_close(L);

					// Clear the Lua stack after executing the script
					//lua_settop(L, 0);
				}
				else
				{
					// Handle the case when no script is selected or the index is out of bounds
					std::cout << "Error: No script selected or invalid index." << std::endl;
				}
			}*/

			ImGui::Text("ESP Colors");
			ImGui::Separator();
			ImGui::ColorEdit4("ESP Box", Esp::BoxColor);
			ImGui::ColorEdit4("ESP Box Outline", Esp::OutlineColor);
			ImGui::ColorEdit4("ESP Filled Box", Esp::FilledBoxColor);
			ImGui::ColorEdit4("ESP Second Filled Box", Esp::SecondFilledBoxColor);
			ImGui::ColorEdit4("ESP Circles", Esp::TestCirclesColor);
			ImGui::ColorEdit4("ESP Text", Esp::TextColor);
			ImGui::ColorEdit4("ESP Text Outline", Esp::TextOutlineColor);
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
