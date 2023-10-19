#include "disabler.h"

Disabler::Disabler() : AbstractModule("Disabler", Category::PLAYER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}
Disabler* Disabler::getInstance()
{
	static Disabler* inst = new Disabler();
	return inst;
}

void Disabler::onEnable()
{
	timer = 0;
}

void Disabler::onDisable()
{
	if (CommonData::getInstance()->SanityCheck()) {
		SDK::Minecraft->timer->SetTimerSpeed(1);
	}
}

void Disabler::onUpdate(const EventUpdate e)
{
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (!this->getToggle()) {
		return;
	}
	if (this->getMode() == 0) {
		if (timer > 5000) {
			this->disable();
		}
		else {
			SDK::Minecraft->timer->SetTimerSpeed(0.01);

		}
	}
	timer++;
}

void Disabler::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Dis", ImVec2(450, 150))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(4572424646907, "Toggle Disabler", this);
		ImGui::Text("Disabler Mode");
		ImGui::Combo("Mode", &this->getMode(), modes, 1);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
