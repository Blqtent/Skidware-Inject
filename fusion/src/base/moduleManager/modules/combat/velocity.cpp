#include "velocity.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"

void Velocity::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	//if (Menu::Open) return;
	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;
	if (thePlayer->getHurtTime() > 7) {
		Vector3 motion = thePlayer->getMotion();
		

		motion.x = motion.x * Velocity::Horizontal;
		motion.y = motion.y * Velocity::Vertical;
		motion.z = motion.z * Velocity::Horizontal;


		thePlayer->setMotion(motion);
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

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
