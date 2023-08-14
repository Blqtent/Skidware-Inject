#include "fullbright.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"

Fulbright::Fulbright() : AbstractModule("Fulbright", Category::VISUAL) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Fulbright* Fulbright::getInstance() {
	static auto* inst = new Fulbright();
	return inst;
}

void Fulbright::onDisable() {
}

void Fulbright::onEnable() {
}

void Fulbright::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	SDK::Minecraft->gameSettings->SetGamma(100.f);
}

void Fulbright::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Fullbright", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(568, "Toggle Fullbright", this);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

