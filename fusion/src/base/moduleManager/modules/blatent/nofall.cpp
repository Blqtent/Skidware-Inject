#include "nofall.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"

static uint64_t timer = GetTickCount64();
void Nofall::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	CTimer* t = SDK::Minecraft->timer;
	JNIEnv* env = Java::Env;
	if (p->isOnGround() && !(p->getHurtTime() > 0)) {
		p->setMotion(Vector3(p->getMotion().x, -11, p->getMotion().z));
	}
}

void Nofall::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Nofall", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle Nofall", &Nofall::Enabled);

		ImGui::Text("Nofall Mode");
		ImGui::Combo("Nofall Mode", &Nofall::mode, Nofall::modes, 1);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}