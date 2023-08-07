#include "longjump.h"
#include "../../../menu/menu.h"

void LongJump::Update()
{
	if (Menu::Open) return;
	if (!CommonData::SanityCheck()) return;
	if (!Enabled) {
		return;
	}
	if (mode == 0) {
		if (SDK::Minecraft->thePlayer->getHurtTime() > 0)
			SDK::Minecraft->thePlayer->set_speed(speed);
	}
}

void LongJump::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Longjump", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(34565464, "Toggle Longjump", &LongJump::Enabled);
		//Menu::DoToggleButtonStuff(124343343, "Antikick", &Flight::antikick);

		ImGui::Text("Longjump Mode");
		ImGui::Combo("Longjump Mode", &LongJump::mode, LongJump::modes, 1);
		Menu::DoSliderStuff(69420666, "Longjump Speed", &LongJump::speed, 0, 5);

		ImGui::EndChild();
	}
	ImGui::PopStyleColor();
}
