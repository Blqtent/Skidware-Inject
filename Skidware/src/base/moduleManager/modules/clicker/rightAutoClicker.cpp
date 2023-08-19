#include "rightAutoClicker.h"
#include "../../../sdk/sdk.h"
#include "../../../menu/menu.h"
#include "../../../util/logger.h"
#include "../../../menu/menu.h"
#include "../../../eventManager/EventManager.hpp"
#include <chrono>
#include <random>

long rightLastClickTime = 0;
int rightNextCps = 10;

RightAutoClicker::RightAutoClicker() : AbstractModule("RightAutoClicker", Category::CLICKER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

RightAutoClicker* RightAutoClicker::getInstance() {
	static auto* inst = new RightAutoClicker();
	return inst;
}

void RightAutoClicker::onDisable() {
}

void RightAutoClicker::onEnable() {
}



void RightAutoClicker::onUpdate(const EventUpdate e)
{
	if (!getToggle()) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;

	jclass blockClass;
	Java::AssignClass("net.minecraft.item.ItemBlock", blockClass);
	if (SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().getInstance() == NULL) return;
	if (this->blocksOnly && !Java::Env->IsInstanceOf(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().GetItem(), blockClass)) return;

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (rightLastClickTime == 0) rightLastClickTime = milli;
	if ((milli - rightLastClickTime) < (1000 / rightNextCps)) return;

	if (GetAsyncKeyState(VK_RBUTTON) && 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		rightLastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(this->rightMinCps, this->rightMaxCps);
		rightNextCps = distrib(gen);
	}
}

void RightAutoClicker::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("rightautoclicker", ImVec2(450, 130))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(2344, "Toggle Right Auto Clicker", this);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(3280, "Min CPS", &this->rightMinCps, 1, 20);
		Menu::DoSliderStuff(675, "Max CPS", &this->rightMaxCps, 1, 20);
		if (rightMinCps > rightMaxCps) {
			rightMinCps = rightMaxCps;
		}
		Menu::DoToggleButtonStuff(73451, "Blocks Only", &this->blocksOnly);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}