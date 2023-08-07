#include "antibot.h"
#include "../../../menu/menu.h"


void Antibot::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("Antib", ImVec2(450, 130))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(696969, "Toggle Antibot", &Antibot::Enabled);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}
