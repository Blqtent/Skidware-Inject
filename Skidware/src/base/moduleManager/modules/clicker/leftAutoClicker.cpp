#include "leftAutoClicker.h"
#include "../../../sdk/sdk.h"
#include "../../../menu/menu.h"
#include "../../../util/logger.h"
#include "../../../menu/menu.h"

#include <chrono>
#include <random>
#include "../../../eventManager/EventManager.hpp"
#include "../../../util/logger.h"
long lastClickTime = 0;
int nextCps = 10;
int count = 0;
LeftAutoClicker::LeftAutoClicker() : AbstractModule("LeftAutoClicker", Category::CLICKER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}
LeftAutoClicker* LeftAutoClicker::getInstance() {
	static auto* inst = new LeftAutoClicker();
	return inst;
}

void LeftAutoClicker::onDisable() {
}

void LeftAutoClicker::onEnable() {
}



void LeftAutoClicker::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState() && !inInventory) return;



	if (ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock()) return;



	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (lastClickTime == 0) lastClickTime = milli;
	if ((milli - lastClickTime) < (1000 / nextCps)) return;

	if (GetAsyncKeyState(VK_LBUTTON) && 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		
		if (blockhit == true && count == blockHitChance) {
			SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
			SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
			count = 0;
		}
		else if (blockhit == true) {
			
			count++;
		}
		lastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(LeftAutoClicker::leftMinCps , LeftAutoClicker::leftMaxCps);
		nextCps = distrib(gen);

	}
}

void LeftAutoClicker::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("autoclicker", ImVec2(450, 130))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(857834, "Toggle Left Auto Clicker",this);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(3280, "Min CPS", &this->leftMinCps, 1, 20);
		Menu::DoSliderStuff(675, "Max CPS", &this->leftMaxCps, 1, 20);
		if (leftMinCps > leftMaxCps) {
			leftMinCps = leftMaxCps;
		}
		Menu::DoToggleButtonStuff(2136, "Ignore Blocks", &this->ignoreBlocks);
		Menu::DoToggleButtonStuff(13423, "Blockhit", &this->blockhit);
		Menu::DoToggleButtonStuff(135315, "In Inventory", &this->inInventory);
		Menu::DoSliderStuff(342, "Blockhit Chance", &this->blockHitChance, 1, 50);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}