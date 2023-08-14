#include "fastplace.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"



Fastplace::Fastplace() : AbstractModule("Fastplace", Category::PLAYER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Fastplace* Fastplace::getInstance() {
	static auto* inst = new Fastplace();
	return inst;
}

void Fastplace::onDisable() {
}

void Fastplace::onEnable() {
}

void Fastplace::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;

	SDK::Minecraft->setRightClickDelayTimer((int)delay);
}

void Fastplace::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("fastplace", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(2134078, "Toggle Fastplace", this);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(124124123, "Delay", &this->delay, 0.f, 6.f);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
