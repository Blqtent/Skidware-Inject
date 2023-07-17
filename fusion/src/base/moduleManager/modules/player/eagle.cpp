#include "eagle.h"
#include "../../commonData.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"

void Eagle::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;

	if (SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1, SDK::Minecraft->thePlayer->GetPos().z)) {
		SDK::Minecraft->thePlayer->setSneak(true);
	}
	else {
		SDK::Minecraft->thePlayer->setSneak(false);
	}
}

void Eagle::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Eagle", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(245309786, "Toggle Eagle", &Eagle::Enabled);
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
