#include "Fullbright.h"
#include "../../commonData.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"



void Fullbright::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;

	SDK::Minecraft->gameSettings->SetGamma(100.f);

}
//
void Fullbright::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Fullbright", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(546345785, "Toggle Fullbright", &Fullbright::Enabled);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
