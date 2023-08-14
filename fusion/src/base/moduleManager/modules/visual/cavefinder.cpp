#include "cavefinder.h"
#include "../../../menu/menu.h"



Cavefinder::Cavefinder() : AbstractModule("Cavefinder", Category::VISUAL) {
}

Cavefinder* Cavefinder::getInstance() {
	static auto* inst = new Cavefinder();
	return inst;
}

void Cavefinder::onDisable() {
}

void Cavefinder::onEnable() {
}

void Cavefinder::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Xray", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(3465, "Toggle Xray", this);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

