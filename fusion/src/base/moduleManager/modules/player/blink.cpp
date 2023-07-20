#include "blink.h"
#include <Windows.h>
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
static ULONGLONG timer;
static bool running;

void Blink::Update()
{
	running = false;
}

void Blink::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Blink", ImVec2(450, 75))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(6890, "Toggle Blink", &Blink::Enabled);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(566578, "Blink Time", &Blink::Milliseonds, 1, 15000);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void Blink::onPacketSend()
{
	if (!Blink::Enabled) {
		return;
	}
	while ((GetAsyncKeyState('H') & 0x8000) && (GetTickCount64() - timer < Blink::Milliseonds * 1000)) {
		Sleep(1);
		running = true;
	}
}

void Blink::RenderUpdate()
{
	if (!running) return;
	ImDrawList* d = ImGui::GetWindowDrawList();
	d->AddText(Menu::Font, 48, ImVec2(800, 800), ImColor(0, 0, 200), "Blinking...");

}