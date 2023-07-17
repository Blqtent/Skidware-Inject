#include "fastplace.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"

void Fastplace::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;

	SDK::Minecraft->setRightClickDelayTimer((int)delay);
}

void Fastplace::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("fastplace", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(2134078, "Toggle Fastplace", &Fastplace::Enabled);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(124124123, "Delay", &Fastplace::delay, 0.f, 6.f);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
