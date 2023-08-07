#include "velocity.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"
int counter;
void Velocity::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;
	//if (Menu::Open) return;
	if (mode == 0) {
		if (thePlayer->getHurtTime() > 7) {
			Vector3 motion = thePlayer->getMotion();
			motion.x = motion.x * Velocity::Horizontal;
			motion.y = motion.y * Velocity::Vertical;
			motion.z = motion.z * Velocity::Horizontal;


			thePlayer->setMotion(motion);
		}
	}
	else if (mode == 1) {
		if (thePlayer->getHurtTime() > 9 && thePlayer->isOnGround() && counter++ % 2 == 0) {
			POINT pos_cursor;
			GetCursorPos(&pos_cursor);
			thePlayer->jump();
		}
	}
	else if (mode == 2) {
		if (thePlayer->getHurtTime() > 5) {
			thePlayer->setOnGround(true);
		}
	}

}

void Velocity::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("velocity", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(2134078, "Toggle Velocity", &Velocity::Enabled);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(248913712347, "Horizontal", &Velocity::Horizontal, 0.f, 1.f);
		Menu::DoSliderStuff(2489137, "Vertical", &Velocity::Vertical, 0.f, 1.f);
		ImGui::Combo("Mode", &Velocity::mode, Velocity::modes, 3);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
