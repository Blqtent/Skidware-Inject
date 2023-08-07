#include "blink.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../commonData.h"


void Blink::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;

	const bool isBindPress = GetAsyncKeyState(bind) & 0x8000;

	if (!isBindPress || (timer != NULL && GetTickCount64() - timer > Milliseonds * 1000))
	{
		timer = NULL;
	}

	if (!isBindPress)
		wasActive = false;

	if (timer == 0 && !wasActive && isBindPress) {
		timer = GetTickCount64();
		wasActive = true;
	}

	if (timer == NULL)
		return;
}

void Blink::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Blink", ImVec2(450, 75))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(6890, "Toggle Fakelag", &Blink::Enabled);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		//Menu::DoToggleButtonStuff(566578, "Fakelag Throttle", &Blink::throttle);
		Menu::DoSliderStuff(566578, "Fakelag Delay", &Blink::Milliseonds, 1, 10000);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void Blink::OnReceiveData()
{

	if (!Enabled)
		return;

	while (GetAsyncKeyState(bind) & 0x8000 && (GetTickCount64() - timer < Milliseonds * 1000)) {
		Sleep(1);
	}
}