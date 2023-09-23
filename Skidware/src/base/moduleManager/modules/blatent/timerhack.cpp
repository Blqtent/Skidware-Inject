#include "timerhack.h"
#include <Windows.h>
#include "../../../menu/menu.h"
static long timer = 0;

TimerHack::TimerHack() : AbstractModule("Nofall", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}


TimerHack* TimerHack::getInstance() {
	static auto* inst = new TimerHack();
	return inst;
}

void TimerHack::onDisable() {
	SDK::Minecraft->timer->SetTimerSpeed(1.0f);
}

void TimerHack::onEnable() {
	timer = 0;
}



void TimerHack::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;

	if (mode == 0) {
		SDK::Minecraft->timer->SetTimerSpeed(speed);
	}
	else if (mode == 1) {
		if (GetAsyncKeyState(VK_LSHIFT)) {
			SDK::Minecraft->timer->SetTimerSpeed(speed2);
		}
		else {
			SDK::Minecraft->timer->SetTimerSpeed(speed);
		}
	}
	else if (mode == 2 && timer <= boostTicks) {
		SDK::Minecraft->timer->SetTimerSpeed(speed);
		timer++;
		if (timer >= boostTicks)
			this->setToggle(false);
	}
	else if (mode == 3) {
		if (timer % 5 == 0) {
			SDK::Minecraft->timer->SetTimerSpeed(speed);
		}
		else {
			SDK::Minecraft->timer->SetTimerSpeed(0.05);
		}
		timer++;

	}
}

void TimerHack::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Timer", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle Timer", this);
		if (mode == 0 || mode == 3) {
			ImGui::SliderFloat("Speed", &speed, 0.1, 5);
		}
		if (mode == 1) {
			ImGui::SliderFloat("Speed", &speed, 0.0001, 5);
			ImGui::SliderFloat("Speed2", &speed2, 0.1, 5);
		}
		if (mode == 2) {
			ImGui::SliderFloat("Speed", &speed, 0.1, 5);
			ImGui::SliderFloat("Boost Ticks", &boostTicks, 1, 500);
		}
		ImGui::Text("Speed Mode Mode");
		ImGui::Combo("Mode", &mode, modes, 4);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
