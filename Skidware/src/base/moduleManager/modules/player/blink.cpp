#include "blink.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../commonData.h"
#include <chrono>
Blink::Blink() : AbstractModule("Fakelag", Category::PLAYER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Blink* Blink::getInstance() {
	static auto* inst = new Blink();
	return inst;
}

void Blink::onDisable() {
}

void Blink::onEnable() {
	timer = 0;
}


void Blink::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	Blink::getInstance()->timer++;


}

void Blink::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Blink", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(6890, "Toggle Fakelag", this);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		//Menu::DoToggleButtonStuff(566578, "Fakelag Throttle", &Blink::throttle);
		if (this->getMode() == 2) {
			ImGui::SliderFloat("Backtrack Delay", &this->Milliseonds, 1, 100);
			ImGui::SliderFloat("Chance", &this->Chance, 1, 10);
		}
		ImGui::Combo("Mode", &this->getMode(), this->modes, 3);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void Blink::OnReceiveData()
{

	if (!this->getToggle())
		return;

	while (IsKeyBeingDown(this->getKey()) && (GetTickCount64() - timer < Milliseonds * 1000)) {
		Sleep(1);
	}
}
