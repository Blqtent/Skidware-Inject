#include "Teams.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"


Teams::Teams() : AbstractModule("Teams", Category::COMBAT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Teams* Teams::getInstance() {
	static auto* inst = new Teams();
	return inst;
}

void Teams::onDisable() {
}

void Teams::onUpdate(const EventUpdate e) {
}

void Teams::onEnable() {
}

void Teams::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("Teams", ImVec2(450, 130))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(233233, "Toggle Teams", this);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}
